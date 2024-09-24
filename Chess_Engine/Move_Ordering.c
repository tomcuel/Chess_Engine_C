#include "Move_Ordering.h"


void order_moves(bool is_captures_only, move* valid_moves, int nb_moves, bit_board* bitboards, int nb_bitboards, Log* log, Game_Settings* game_settings){

    // creating an array to store the values of the moves
    int* values = (int*)malloc(nb_moves*sizeof(int));
    // looking for malloc errors
    if(values == NULL){
        printf("Error in order_moves : malloc error\n");
        exit(1);
    }

    // sorting the moves by their value, depending on some parameters
    for (int i = 0; i < nb_moves; i++){

        // we first initialize the value of the move to 0
        values[i] = 0;

        // getting the differents informations about the move
        int from = get_from_square(valid_moves[i]);
        int to = get_to_square(valid_moves[i]);
        int flag = get_flag(valid_moves[i]);

        // looking if the move is a capture
        bool is_capture_happening = will_capture(game_settings->color_of_player_that_is_playing, bitboards, nb_bitboards, to);
        if (flag == En_Passant_Flag){
            is_capture_happening = true;
        }

        // capturing a piece is a good move, but it's better to capture a piece that is worth more than the piece that is moving
        if (is_capture_happening){
            int capture_delta = get_value_of_piece(get_type_of_piece(bitboards, nb_bitboards, from)) - get_value_of_piece(get_type_of_piece(bitboards, nb_bitboards, to));
            // looking if the oppenent can recapture the piece
            int recapture_possible = is_case_threatened(1-game_settings->color_of_player_that_is_playing, to, bitboards, nb_bitboards, log);
            // if the opponent can recapture the piece, we don't want to capture it
            if (recapture_possible){
                // if the opponent can recapture the piece, we want to capture it only if it's worth more than the piece that is moving
                // if the piece that is moving is worth more than the piece that is being captured, we don't want to capture it
                values[i] += (capture_delta > 0) ? 200 : -200; 
            }
            // if the opponent can't recapture the piece, we want to capture it
            else{
                values[i] += capture_delta + 200; // 200 is a bonus for capturing a piece
            }
        }
        // those evaluations of the moves are not useful if we only want to order the captures
        if (!is_captures_only){
            // promoting a pawn is a good move
            // it first need to be a pawn of the good color that is moving (not taken care of in the valid_moves array, but only in is legal move)
            // when a capture is happening, the promotion is not as good of a move
            if (is_promotion_flag(flag) && !is_capture_happening){
                    values[i] += 10000;
            }
            // castling is a good move
            // it first need to be a king of the good color that is moving (not taken care of in the valid_moves array, but only in is legal move)
            if (flag == Castle_Flag){
                values[i] += 10000;
            }
            // moving a piece is not a good move if the square is attacked by an opponent piece
            if(is_case_threatened(game_settings->color_of_player_that_is_playing, to, bitboards, nb_bitboards, log)){
                values[i] -= 25;
            }
        }
        // moving a piece is not a good move if the square is attacked by an opponent pawn
        if (is_square_attacked_by_opponent_pawn(game_settings->color_of_player_that_is_playing, bitboards, nb_bitboards, to)){
            values[i] -= 50;
        }
        // if the ennemy king is threatened, it's likely that the move is a good move
        if (is_case_threatened(1-game_settings->color_of_player_that_is_playing, get_king_index(bitboards, 1-game_settings->color_of_player_that_is_playing), bitboards, nb_bitboards, log)){
            values[i] += 1000;
        }

    }

    // sorting the moves by their score
    quick_sort(values, valid_moves, nb_moves);

    // freeing the values array
    free(values);

}


bool is_square_attacked_by_opponent_pawn(int color_of_player_that_is_playing, bit_board* bitboards, int nb_bitboards, int square){

    // if the player is white, we check if the square is attacked by a black pawn
    if (color_of_player_that_is_playing == WHITE){
        // the black pawn could be on the left and one square up (square + 7), but we need to check if the square is not on the left border of the board
        if (square + 7 < NUMBER_SQUARES && get_file(square) != 0 && (bitboards[PAWN_BLACK] & (1ULL << (square + 7)))){
            return true;
        }
        // the black pawn could be on the right and one square up (square + 9), but we need to check if the square is not on the right border of the board
        if (square + 9 < NUMBER_SQUARES && get_file(square) != 7 && (bitboards[PAWN_BLACK] & (1ULL << (square + 9)))){
            return true;
        }
    }
    // if the player is black, we check if the square is attacked by a white pawn
    else if (color_of_player_that_is_playing == BLACK){
        // the white pawn could be on the left and one square down (square - 9), but we need to check if the square is not on the left border of the board
        if (square - 9 >= 0 && get_file(square) != 0 && (bitboards[PAWN_WHITE] & (1ULL << (square - 9)))){
            return true;
        }
        // the white pawn could be on the right and one square down (square - 7), but we need to check if the square is not on the right border of the board
        if (square - 7 >= 0 && get_file(square) != 7 && (bitboards[PAWN_WHITE] & (1ULL << (square - 7)))){
            return true;
        }
    }

    // default return value
    return false;

}


void quick_sort(int* values, move* valid_moves, int nb_moves){
    
    for (int i = 0; i < nb_moves; i++){
        for (int j = i+1; j < nb_moves; j++){
            // if the value at the i index is lower than the value at the j index, we swap the two values
            if (values[i] < values[j]){
                // swapping the values
                int temp_value = values[i];
                values[i] = values[j];
                values[j] = temp_value;

                // swapping the moves
                move temp_move = valid_moves[i];
                valid_moves[i] = valid_moves[j];
                valid_moves[j] = temp_move;
            }
        }
    }

}

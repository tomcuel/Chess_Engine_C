#include "Board.h"


Captured_Pieces_and_Score* create_captured_pieces_and_score(int max_number_of_pieces){
    // Allocating memory for the captured pieces and the score
    Captured_Pieces_and_Score* captured_pieces_and_score = (Captured_Pieces_and_Score*)malloc(sizeof(Captured_Pieces_and_Score));
    // Checking if the malloc failed
    if (captured_pieces_and_score == NULL){
        printf("Error: malloc failed in captured_pieces_and_score\n");
        return NULL;
    }

    // Allocating memory for the white captured pieces
    captured_pieces_and_score->white_capture_pieces = (int*)malloc(max_number_of_pieces * sizeof(int));
    // Checking if the malloc failed
    if (captured_pieces_and_score->white_capture_pieces == NULL){
        printf("Error: malloc failed in white_capture_pieces\n");
        return NULL;
    }

    // Allocating memory for the black captured pieces
    captured_pieces_and_score->black_capture_pieces = (int*)malloc(max_number_of_pieces * sizeof(int));
    // Checking if the malloc failed
    if (captured_pieces_and_score->black_capture_pieces == NULL){
        printf("Error: malloc failed in black_capture_pieces\n");
        return NULL;
    }

    // initializing the captured pieces and the score
    captured_pieces_and_score->max_number_of_pieces_per_color = max_number_of_pieces;
    captured_pieces_and_score->number_of_white_captured_pieces = 0;
    captured_pieces_and_score->number_of_black_captured_pieces = 0;
    captured_pieces_and_score->players_that_is_winning = Undetermined;
    captured_pieces_and_score->score = 0;

    // initializing the captured pieces to NOTHING
    for (int i = 0; i < max_number_of_pieces; i++){
        captured_pieces_and_score->white_capture_pieces[i] = NOTHING;
        captured_pieces_and_score->black_capture_pieces[i] = NOTHING;
    }

    // return the captured pieces and the score
    return captured_pieces_and_score;
}


void reset_captured_pieces_and_score(Captured_Pieces_and_Score* captured_pieces_and_score){
    // initializing the captured pieces and the score
    captured_pieces_and_score->number_of_white_captured_pieces = 0;
    captured_pieces_and_score->number_of_black_captured_pieces = 0;
    captured_pieces_and_score->players_that_is_winning = Undetermined;
    captured_pieces_and_score->score = 0;

    // initializing the captured pieces to NOTHING
    for (int i = 0; i < captured_pieces_and_score->max_number_of_pieces_per_color; i++){
        captured_pieces_and_score->white_capture_pieces[i] = NOTHING;
        captured_pieces_and_score->black_capture_pieces[i] = NOTHING;
    }
}


Captured_Pieces_and_Score* copy_captured_pieces_and_score(Captured_Pieces_and_Score* captured_pieces_and_score){
    // Allocating memory for the copy captured pieces and the score
    Captured_Pieces_and_Score* copy_captured_pieces_and_score = (Captured_Pieces_and_Score*)malloc(sizeof(Captured_Pieces_and_Score));
    // Checking if the malloc failed
    if (copy_captured_pieces_and_score == NULL){
        printf("Error: malloc failed in copy_captured_pieces_and_score\n");
        return NULL;
    }

    // Allocating memory for the white captured pieces
    copy_captured_pieces_and_score->white_capture_pieces = (int*)malloc(captured_pieces_and_score->max_number_of_pieces_per_color * sizeof(int));
    // Checking if the malloc failed
    if (copy_captured_pieces_and_score->white_capture_pieces == NULL){
        printf("Error: malloc failed in white_capture_pieces\n");
        return NULL;
    }

    // Allocating memory for the black captured pieces
    copy_captured_pieces_and_score->black_capture_pieces = (int*)malloc(captured_pieces_and_score->max_number_of_pieces_per_color * sizeof(int));
    // Checking if the malloc failed
    if (copy_captured_pieces_and_score->black_capture_pieces == NULL){
        printf("Error: malloc failed in black_capture_pieces\n");
        return NULL;
    }

    // copying the captured pieces and the score
    copy_captured_pieces_and_score->max_number_of_pieces_per_color = captured_pieces_and_score->max_number_of_pieces_per_color;
    copy_captured_pieces_and_score->number_of_white_captured_pieces = captured_pieces_and_score->number_of_white_captured_pieces;
    copy_captured_pieces_and_score->number_of_black_captured_pieces = captured_pieces_and_score->number_of_black_captured_pieces;
    copy_captured_pieces_and_score->players_that_is_winning = captured_pieces_and_score->players_that_is_winning;
    copy_captured_pieces_and_score->score = captured_pieces_and_score->score;

    // copying the captured pieces
    for (int i = 0; i < captured_pieces_and_score->max_number_of_pieces_per_color; i++){
        copy_captured_pieces_and_score->white_capture_pieces[i] = captured_pieces_and_score->white_capture_pieces[i];
        copy_captured_pieces_and_score->black_capture_pieces[i] = captured_pieces_and_score->black_capture_pieces[i];
    }

    // return the copy captured pieces and the score
    return copy_captured_pieces_and_score;
}


void destroy_captured_pieces_and_score(Captured_Pieces_and_Score* captured_pieces_and_score){
    // if the captured pieces and the score is not NULL (malloc error), we can free it
    if (captured_pieces_and_score != NULL){
        // if the white captured pieces is not NULL (malloc error), we can free it
        if (captured_pieces_and_score->white_capture_pieces != NULL){
            free(captured_pieces_and_score->white_capture_pieces);
        }
        // if the black captured pieces is not NULL (malloc error), we can free it
        if (captured_pieces_and_score->black_capture_pieces != NULL){
            free(captured_pieces_and_score->black_capture_pieces);
        }
        free(captured_pieces_and_score);
    }
}


int get_value_of_piece(int piece){
    // return the value of the piece
    if (piece == PAWN_WHITE || piece == PAWN_BLACK){
        return PAWN_VALUE;
    }
    if (piece == KNIGHT_WHITE || piece == KNIGHT_BLACK){
        return KNIGHT_VALUE;
    }
    if (piece == BISHOP_WHITE || piece == BISHOP_BLACK){
        return BISHOP_VALUE;
    }
    if (piece == ROOK_WHITE || piece == ROOK_BLACK){
        return ROOK_VALUE;
    }
    if (piece == QUEEN_WHITE || piece == QUEEN_BLACK){
        return QUEEN_VALUE;
    }
    if (piece == KING_WHITE || piece == KING_BLACK){
        return KING_VALUE;
    }
    return 0;
}


bit_board* init_bitboards(){
    // Allocating memory for the bitboards array
    bit_board* bitboards_array = (bit_board*)malloc(NUMBER_OF_BIBOARD * sizeof(bit_board));
    // Checking if the malloc failed
    if (bitboards_array == NULL){
        printf("Error: malloc failed in bitboards_array\n");
        return NULL;
    }

    // initializing the bitboards
    // the white pieces
    bitboards_array[PAWN_WHITE] = 0x000000000000FF00ULL;
    bitboards_array[KNIGHT_WHITE] = 0x0000000000000042ULL;
    bitboards_array[BISHOP_WHITE] = 0x0000000000000024ULL;
    bitboards_array[ROOK_WHITE] = 0x0000000000000081ULL;
    bitboards_array[QUEEN_WHITE] = 0x0000000000000008ULL;
    bitboards_array[KING_WHITE] = 0x0000000000000010ULL;
    bitboards_array[WHITE_PIECES] = 0x000000000000FFFFULL;
    // the black pieces
    bitboards_array[PAWN_BLACK] = 0x00FF000000000000ULL;
    bitboards_array[KNIGHT_BLACK] = 0x4200000000000000ULL;
    bitboards_array[BISHOP_BLACK] = 0x2400000000000000ULL;
    bitboards_array[ROOK_BLACK] = 0x8100000000000000ULL;
    bitboards_array[QUEEN_BLACK] = 0x0800000000000000ULL;
    bitboards_array[KING_BLACK] = 0x1000000000000000ULL;
    bitboards_array[BLACK_PIECES] = 0xFFFF000000000000ULL;

    // return the bitboards array
    return bitboards_array;
}


void reset_bitboards(bit_board* bitboards_array){
    // initializing again the bitboards
    // the white pieces
    bitboards_array[PAWN_WHITE] = 0x000000000000FF00ULL;
    bitboards_array[KNIGHT_WHITE] = 0x0000000000000042ULL;
    bitboards_array[BISHOP_WHITE] = 0x0000000000000024ULL;
    bitboards_array[ROOK_WHITE] = 0x0000000000000081ULL;
    bitboards_array[QUEEN_WHITE] = 0x0000000000000008ULL;
    bitboards_array[KING_WHITE] = 0x0000000000000010ULL;
    bitboards_array[WHITE_PIECES] = 0x000000000000FFFFULL;
    // the black pieces
    bitboards_array[PAWN_BLACK] = 0x00FF000000000000ULL;
    bitboards_array[KNIGHT_BLACK] = 0x4200000000000000ULL;
    bitboards_array[BISHOP_BLACK] = 0x2400000000000000ULL;
    bitboards_array[ROOK_BLACK] = 0x8100000000000000ULL;
    bitboards_array[QUEEN_BLACK] = 0x0800000000000000ULL;
    bitboards_array[KING_BLACK] = 0x1000000000000000ULL;
    bitboards_array[BLACK_PIECES] = 0xFFFF000000000000ULL;
}


bit_board* create_a_copy_of_bitboards(bit_board* bitboards_array){
    // Allocating memory for the copy bitboards array
    bit_board* copy_bitboards_array = (bit_board*)malloc(NUMBER_OF_BIBOARD * sizeof(bit_board));
    // Checking if the malloc failed
    if (copy_bitboards_array == NULL){
        printf("Error: malloc failed in copy_bitboards_array\n");
        return NULL;
    }

    // copying the bitboards
    for (int i = 0; i < NUMBER_OF_BIBOARD; i++){
        copy_bitboards_array[i] = bitboards_array[i];
    }

    // return the copy bitboards array
    return copy_bitboards_array;
}


void copy_bitboards_in_bitboards(bit_board* bitboards_array, bit_board* copy_bitboards_array){
    // copying the bitboards
    for (int i = 0; i < NUMBER_OF_BIBOARD; i++){
        bitboards_array[i] = copy_bitboards_array[i];
    }
}


void destroy_bitboards(bit_board* bitboards_array){
    // if the bitboards array is not NULL (malloc error), we can free it
    if (bitboards_array != NULL){
        free(bitboards_array);
    }
}


void move_piece(bit_board* moving_piece_bitboard, int color_that_is_playing, bit_board* bitboards, int from, int to) {
    
    *moving_piece_bitboard &= ~(1ULL << from);
    *moving_piece_bitboard |= (1ULL << to);

    if (color_that_is_playing == WHITE){
        bitboards[WHITE_PIECES] &= ~(1ULL << from);
        bitboards[WHITE_PIECES] |= (1ULL << to);
    }
    else if (color_that_is_playing == BLACK){
        bitboards[BLACK_PIECES] &= ~(1ULL << from);
        bitboards[BLACK_PIECES] |= (1ULL << to);
    }

}


void clear_piece(bit_board* bitboard, int to, int color){
    
    if (color == WHITE){
        for (int i=0; i<number_of_bitboards_per_color; i++){
            bitboard[i] &= ~(1ULL << to);
        }
    }
    else if (color == BLACK){
        for (int i=0; i<number_of_bitboards_per_color; i++){
            bitboard[7+i] &= ~(1ULL << to);
        }
    }

}


void move_rook_during_castle(bit_board* bitboards, int from, int to){
    
    if (from == 4 && to == 6){
        bitboards[ROOK_WHITE] &= ~(1ULL << 7);
        bitboards[ROOK_WHITE] |= (1ULL << 5);
        bitboards[WHITE_PIECES] &= ~(1ULL << 7);
        bitboards[WHITE_PIECES] |= (1ULL << 5);
    }
    else if (from == 4 && to == 2){
        bitboards[ROOK_WHITE] &= ~(1ULL << 0);
        bitboards[ROOK_WHITE] |= (1ULL << 3);
        bitboards[WHITE_PIECES] &= ~(1ULL << 0);
        bitboards[WHITE_PIECES] |= (1ULL << 3);
    }
    else if (from == 60 && to == 62){
        bitboards[ROOK_BLACK] &= ~(1ULL << 63);
        bitboards[ROOK_BLACK] |= (1ULL << 61);
        bitboards[BLACK_PIECES] &= ~(1ULL << 63);
        bitboards[BLACK_PIECES] |= (1ULL << 61);
    }
    else if (from == 60 && to == 58){
        bitboards[ROOK_BLACK] &= ~(1ULL << 56);
        bitboards[ROOK_BLACK] |= (1ULL << 59);
        bitboards[BLACK_PIECES] &= ~(1ULL << 56);
        bitboards[BLACK_PIECES] |= (1ULL << 59);
    }

}


void clear_piece_during_en_passant(bit_board* bitboards, int color, int to){

    if (color == WHITE){
        // we remove the pawn that is taken at the to-8 position
        bitboards[PAWN_BLACK] &= ~(1ULL << (to-8));
        bitboards[BLACK_PIECES] &= ~(1ULL << (to-8));
    }
    else if (color == BLACK){
        // we remove the pawn that is taken at the to+8 position
        bitboards[PAWN_WHITE] &= ~(1ULL << (to+8));
        bitboards[WHITE_PIECES] &= ~(1ULL << (to+8));
    }
}

 
void make_move(Game_Settings* game_settings, bit_board* bitboards, int nb_bitboards, int from, int to, int flag, int type_move_legal_attacking){

    // we now make the move 
    move_piece(&bitboards[type_move_legal_attacking], game_settings->color_of_player_that_is_playing, bitboards, from, to);
    // if there is a castle, we need to create the rook move linked to it 
    if (flag == Castle_Flag){
        move_rook_during_castle(bitboards, from, to);
    }
    // we now clear the piece that has been taken for the opposite player
    clear_piece(bitboards, to, 1-game_settings->color_of_player_that_is_playing);
    // if there is an en passant, we need to clear the piece that has been taken
    if (flag == En_Passant_Flag){
        clear_piece_during_en_passant(bitboards, game_settings->color_of_player_that_is_playing, to);
    }

}


void update_score(Captured_Pieces_and_Score* captured_pieces_and_score){

    // updating the score
    int score = 0;
    for (int i = 0; i < captured_pieces_and_score->number_of_white_captured_pieces; i++){
        score += get_value_of_piece(captured_pieces_and_score->white_capture_pieces[i]);
    }
    for (int i = 0; i < captured_pieces_and_score->number_of_black_captured_pieces; i++){
        score -= get_value_of_piece(captured_pieces_and_score->black_capture_pieces[i]);
    }
    // a positive score means that more white pieces have been taken, a negative score means that more black pieces have been taken
    if (score > 0){
        captured_pieces_and_score->players_that_is_winning = BLACK;
        captured_pieces_and_score->score = score / 100; // we divide the score by 100 to have a more readable score (as in the real chess game, not as the AI score)
    }
    else if (score < 0){
        captured_pieces_and_score->players_that_is_winning = WHITE;
        captured_pieces_and_score->score = -score / 100; // we divide the score by 100 to have a more readable score (as in the real chess game, not as the AI score)
    }
    else {
        captured_pieces_and_score->players_that_is_winning = Undetermined;
        captured_pieces_and_score->score = 0;
    }

}


void update_captured_piece_and_score(int piece_taken_typen, Captured_Pieces_and_Score* captured_pieces_and_score){

    // if the piece captured is a white piece
    if (piece_taken_typen >= PAWN_WHITE && piece_taken_typen <= KING_WHITE){
        // we add the piece to the white captured pieces
        captured_pieces_and_score->white_capture_pieces[captured_pieces_and_score->number_of_white_captured_pieces] = piece_taken_typen;
        // we increment the number of white captured pieces
        captured_pieces_and_score->number_of_white_captured_pieces++;
    }
    // if the piece captured is a black piece 
    else if (piece_taken_typen >= PAWN_BLACK && piece_taken_typen <= KING_BLACK){
        // we add the piece to the black captured pieces
        captured_pieces_and_score->black_capture_pieces[captured_pieces_and_score->number_of_black_captured_pieces] = piece_taken_typen;
        // we increment the number of black captured pieces
        captured_pieces_and_score->number_of_black_captured_pieces++;
        // we increment the score depending on who is winning
    }

    // udpatin the score after the piece has been taken
    update_score(captured_pieces_and_score);

}


void update_log(Log* chess_log, move move_value, int piece_taken_type){

    Log_Element* log_element = create_move_element();

    log_element->move_value = move_value;
    log_element->captured_piece_type = piece_taken_type;

    // we add the move to the log
    add_move_to_log(chess_log, log_element);
    destroy_move_element(log_element);

}


void update_log_and_captured_piece_and_score(Log* chess_log, Captured_Pieces_and_Score* captured_pieces_and_score, move move_value, int piece_taken_type){
    
    // we update the log
    update_log(chess_log, move_value, piece_taken_type);

    // we now update the captured piece and the score
    update_captured_piece_and_score(piece_taken_type, captured_pieces_and_score);

}


void update_castle_in_log(Log* chess_log, int from, int to, int color_that_played_the_move){
    // function only used when the castle has been done

    // if a short castle has been done by white
    if (from == 4 && to == 6 && color_that_played_the_move == WHITE){
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, White_King_Moved_Flag);
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, White_Rook_H_Moved_Flag);
    }
    // if a long castle has been done by white
    else if (from == 4 && to == 2 && color_that_played_the_move == WHITE){
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, White_King_Moved_Flag);
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, White_Rook_A_Moved_Flag);
    }
    // if a short castle has been done by black
    else if (from == 60 && to == 62 && color_that_played_the_move == BLACK){
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, Black_King_Moved_Flag);
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, Black_Rook_H_Moved_Flag);
    }
    // if a long castle has been done by black
    else if (from == 60 && to == 58 && color_that_played_the_move == BLACK){
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, Black_King_Moved_Flag);
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, Black_Rook_A_Moved_Flag);
    }

}


void update_piece_movement_for_castle_in_log(Log* chess_log, bit_board* bitboards){

    // looking if the white rook H has moved (is not at the initial position)
    if (!(bitboards[ROOK_WHITE] & (1ULL << 7))){
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, White_Rook_H_Moved_Flag);
    }
    // looking if the white rook A has moved (is not at the initial position)
    if (!(bitboards[ROOK_WHITE] & (1ULL << 0))){
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, White_Rook_A_Moved_Flag);
    }
    // looking if the black rook H has moved (is not at the initial position)
    if (!(bitboards[ROOK_BLACK] & (1ULL << 63))){
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, Black_Rook_H_Moved_Flag);
    }
    // looking if the black rook A has moved (is not at the initial position)
    if (!(bitboards[ROOK_BLACK] & (1ULL << 56))){
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, Black_Rook_A_Moved_Flag);
    }
    // looking if the white king has moved (is not at the initial position)
    if (!(bitboards[KING_WHITE] & (1ULL << 4))){
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, White_King_Moved_Flag);
    }
    // looking if the black king has moved (is not at the initial position)
    if (!(bitboards[KING_BLACK] & (1ULL << 60))){
        set_castling_flag(&chess_log->moves[chess_log->actual_size-1]->castling_rights, Black_King_Moved_Flag);
    }

}


void update_castle_state_in_log(Log* chess_log, bit_board* bitboards, int nb_bitboards, int from, int to, int flag, int color_of_player_that_will_play_next){

    // if there is no move in the log, we can't update the castle state
    if (chess_log->actual_size == 0){
        return;
    }

    // we copy the castle rights of the previous move that we will modify later
    if (chess_log->actual_size != 1){
        chess_log->moves[chess_log->actual_size-1]->castling_rights = chess_log->moves[chess_log->actual_size-2]->castling_rights;
    }

    if (flag == Castle_Flag){
        // needs for the castle to update the first part of the log
        update_castle_in_log(chess_log, from, to, 1-color_of_player_that_will_play_next);
    }

    // after a move, we need to udpate the parameters of the game, to tell if a piece useful for the castle has moved
    update_piece_movement_for_castle_in_log(chess_log, bitboards);

}


void undo_last_move(Log* chess_log, Bitboards_Log* bitboard_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score, Game_Settings* game_settings){

    // if there is no move in the log, we can't undo a move
    if (chess_log->actual_size == 0 || bitboard_log->actual_size == 0){
        return;
    }


    // getting the information of the last move
    int from = get_from_square(chess_log->moves[chess_log->actual_size-1]->move_value);
    int to = get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value);
    int flag = get_flag(chess_log->moves[chess_log->actual_size-1]->move_value);
    int moved_piece_type = get_type_of_piece(bitboards, NUMBER_OF_BIBOARD, to);
    // if there has been a promotion, we need to remove the piece that has been promoted, so we change back the type to a pawn
    if (is_promotion_flag(flag)){
        bitboards[moved_piece_type] &= ~(1ULL << to);
        if (game_settings->color_of_player_that_is_playing == WHITE){
            moved_piece_type = PAWN_BLACK;
        }
        else if (game_settings->color_of_player_that_is_playing == BLACK){
            moved_piece_type = PAWN_WHITE;
        }
    }
    int captured_piece_type = chess_log->moves[chess_log->actual_size-1]->captured_piece_type;
    // making the move in the opposite way
    move_piece(&bitboards[moved_piece_type], 1-game_settings->color_of_player_that_is_playing, bitboards, to, from);
    // if there has been a capture, we need to put back the piece that has been taken (normal capture or en passant)
    if (captured_piece_type != NOTHING){
        // since the move has been made, we return the piece of the player that is playing now, so the on that was not playing before
        if (flag == En_Passant_Flag){
            // we put back the pawn that has been taken
            if (game_settings->color_of_player_that_is_playing == WHITE){
                bitboards[PAWN_WHITE] |= (1ULL << (to+8));
                bitboards[WHITE_PIECES] |= (1ULL << (to+8));
            }
            else if (game_settings->color_of_player_that_is_playing == BLACK){
                bitboards[PAWN_BLACK] |= (1ULL << (to-8));
                bitboards[BLACK_PIECES] |= (1ULL << (to-8));
            }
        }
        else {
            // we put back the piece that has been taken
            bitboards[captured_piece_type] |= (1ULL << to);

            if (game_settings->color_of_player_that_is_playing == WHITE){
                bitboards[WHITE_PIECES] |= (1ULL << to);
            }
            else if (game_settings->color_of_player_that_is_playing == BLACK){
                bitboards[BLACK_PIECES] |= (1ULL << to);
            }
        }
    }
    // if there has been a castle, we need to undo the castle that has been done
    if (flag == Castle_Flag){
        // putting back the rook that has been moved
        if (from == 4 && to == 6){
            bitboards[ROOK_WHITE] &= ~(1ULL << 5);
            bitboards[ROOK_WHITE] |= (1ULL << 7);
            bitboards[WHITE_PIECES] &= ~(1ULL << 5);
            bitboards[WHITE_PIECES] |= (1ULL << 7);
        }
        else if (from == 4 && to == 2){
            bitboards[ROOK_WHITE] &= ~(1ULL << 3);
            bitboards[ROOK_WHITE] |= (1ULL << 0);
            bitboards[WHITE_PIECES] &= ~(1ULL << 3);
            bitboards[WHITE_PIECES] |= (1ULL << 0);
        }
        else if (from == 60 && to == 62){
            bitboards[ROOK_BLACK] &= ~(1ULL << 61);
            bitboards[ROOK_BLACK] |= (1ULL << 63);
            bitboards[BLACK_PIECES] &= ~(1ULL << 61);
            bitboards[BLACK_PIECES] |= (1ULL << 63);
        }
        else if (from == 60 && to == 58){
            bitboards[ROOK_BLACK] &= ~(1ULL << 59);
            bitboards[ROOK_BLACK] |= (1ULL << 56);
            bitboards[BLACK_PIECES] &= ~(1ULL << 59);
            bitboards[BLACK_PIECES] |= (1ULL << 56);
        }
    }


    // if there has been a capture, we need to retire the piece that has been taken in the captured pieces and the score
    int piece_type = get_type_of_piece(bitboards, NUMBER_OF_BIBOARD, get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
    // if a piece has been taken
    if (piece_type != NOTHING){
        // if the piece taken is a white piece
        if (piece_type >= PAWN_WHITE && piece_type <= KING_WHITE){
            // we decrement the number of white captured pieces (it's as if the piece has been counted for the score and the captured pieces)
            captured_pieces_and_score->number_of_white_captured_pieces--;
        }
        // if the piece taken is a black piece
        else if (piece_type >= PAWN_BLACK && piece_type <= KING_BLACK){
            // we decrement the number of black captured pieces (it's as if the piece has been counted for the score and the captured pieces)
            captured_pieces_and_score->number_of_black_captured_pieces--;
        }
    }
    // calculating the score again
    update_score(captured_pieces_and_score);

    // we remove the last move from the log
    remove_last_move_from_log(chess_log);
    remove_last_bitboards_from_log(bitboard_log);
    // if there has been a castle, we need to undo the castle that has been done in the log parameters, it's done when we suppress the last element of the log

    // changing the player that is playing
    change_player_that_is_playing(game_settings);

}


bool are_bitboards_equal(bit_board* bitboards1, bit_board* bitboards2, int nb_bitboards){

    for (int i=0; i<nb_bitboards; i++){
        if (bitboards1[i] != bitboards2[i]){
            return false;
        }
    }

    return true;

}


bool is_draw_forced_by_3_repetition_of_position_rule(Bitboards_Log* bitboard_log, int nb_bitboards){

    // if the actual size of the log is less than 3, we can't have a draw by 3 repetition of position
    if (bitboard_log->actual_size < 3){
        return false;
    }

    // we need to look at each board we have gone through and see if the same position was repeated 3 times
    for (int i=0; i<bitboard_log->actual_size-2; i++){
        for (int j=i+1; j<bitboard_log->actual_size-1; j++){
            for (int k=j+1; k<bitboard_log->actual_size; k++){
                if (are_bitboards_equal(bitboard_log->bitboards[i], bitboard_log->bitboards[j], nb_bitboards) && are_bitboards_equal(bitboard_log->bitboards[j], bitboard_log->bitboards[k], nb_bitboards)){
                    return true;
                }
            }
        }
    }

    // if the same position was repeated 3 times, then we return true
    return false;

}


bool is_draw_forced_by_50_moves_rule(Log* chess_log, Bitboards_Log* bitboard_log){

    // if the actual size of the log is less than 100 (1 move for each player is a move for the rule)
    if (bitboard_log->actual_size < 100 || chess_log->actual_size < 100){
        return false;
    }

    // if the last 50 moves have been made without any pawn move or any capture, then the game is a draw
    for (int i=bitboard_log->actual_size-100; i<bitboard_log->actual_size; i++){
        if (chess_log->moves[i]->captured_piece_type != NOTHING || (bitboard_log->bitboards[i][PAWN_WHITE] & (1ULL << get_from_square(chess_log->moves[i]->move_value))) || (bitboard_log->bitboards[i][PAWN_BLACK] & (1ULL << get_from_square(chess_log->moves[i]->move_value)))){
            return false;
        }
    }

    // if the last 50 moves have been made without any pawn move or any capture, then the game is a draw
    return true;

}


bool is_draw_forced_by_insuffisant_material(bit_board* bitboards, int nb_bitboards){

    // there is no draw if there still are pawns
    if (__builtin_popcountll(bitboards[PAWN_WHITE]) > 0 || __builtin_popcountll(bitboards[PAWN_BLACK]) > 0){
        return false;
    }

    // there is no draw if there still are rooks or queens
    if (__builtin_popcountll(bitboards[ROOK_WHITE]) > 0 || __builtin_popcountll(bitboards[ROOK_BLACK]) > 0 || __builtin_popcountll(bitboards[QUEEN_WHITE]) > 0 || __builtin_popcountll(bitboards[QUEEN_BLACK]) > 0){
        return false;
    }

    // Counting the number of minor pieces for each player
    // for the white player
    int nb_white_knights = __builtin_popcountll(bitboards[KNIGHT_WHITE]);
    int nb_white_bishops = __builtin_popcountll(bitboards[BISHOP_WHITE]);
    int nb_white_minor_pieces = nb_white_knights + nb_white_bishops;
    // for the black player
    int nb_black_knights = __builtin_popcountll(bitboards[KNIGHT_BLACK]);
    int nb_black_bishops = __builtin_popcountll(bitboards[BISHOP_BLACK]);
    int nb_black_minor_pieces = nb_black_knights + nb_black_bishops;
    // the total number of minor pieces
    int nb_minor_pieces = nb_white_minor_pieces + nb_black_minor_pieces;

    // a lone king vs king with not more than one minor piece is a draw
    if (nb_minor_pieces <= 1){
        return true;
    }
    // bishop vs bishop of the same color is a draw
    if (nb_minor_pieces == 2 && nb_white_bishops == 1 && nb_black_bishops == 1){

        bool bishop_white_on_white_square = false;
        int white_bishop_square = __builtin_ctzll(bitboards[BISHOP_WHITE]);
        if ((get_rank(white_bishop_square) + get_file(white_bishop_square)) % 2 == 0){
            bishop_white_on_white_square = true;
        }

        bool bishop_black_on_white_square = false;
        int black_bishop_square = __builtin_ctzll(bitboards[BISHOP_BLACK]);
        if ((get_rank(black_bishop_square) + get_file(black_bishop_square)) % 2 == 0){
            bishop_black_on_white_square = true;
        }

        return bishop_white_on_white_square == bishop_black_on_white_square;
    }

    // default return value, if no insuffisant material is found, the game is not a draw by insuffisant material
    // (the problem is too complex to fully implement it, so we just check some trivial cases)
    return false;
}


int is_draw_forced_by_rules(Log* chess_log, Bitboards_Log* bitboard_log, bit_board* bitboards, int nb_bitboards){

    // if the game is a draw by 3 repetition of position
    if (is_draw_forced_by_3_repetition_of_position_rule(bitboard_log, nb_bitboards)){
        return DRAW_BY_3_RULES;
    }

    // if the game is a draw by 50 moves without any pawn move or any capture
    if (is_draw_forced_by_50_moves_rule(chess_log, bitboard_log)){
        return DRAW_BY_50_RULES;
    }

    // if the game is a draw by insufficient material
    if (is_draw_forced_by_insuffisant_material(bitboards, nb_bitboards)){
        return DRAW_BY_INSUFFICIENT_MATERIAL;
    }

    // here we don't consider the draw by insufficient material because it is too complex to implement and not really useful for the game
    return NO_DRAW;

}

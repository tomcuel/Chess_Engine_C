#include "Search.h"


void run_iterative_deepening(int ms_time_of_search, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score, move* selected_move, TT* transposition_tables){

    printf("iterative deepening with transposition tables and search extensions\n");
    // setting the variables for the iterative deepening
    move best_move = 0;
    int best_score = 0;
    move best_move_this_iteration = 0;
    int best_score_this_iteration = INT_MIN;

    // choosing the think time of the AI (will be dealed in another way later), but currently it's only for testing
    int think_time_limit = INT_MAX; // for the depth 1 search so it's not stopped
    int start_time = (int)SDL_GetTicks();
    bool is_search_canceled = false;

    // running the depth 1 search without time restriction
    int depth_1_score = Search(1, 0, NEGATIVE_INFINITY, POSITIVE_INFINITY, 0, &best_move, &best_score, &is_search_canceled, think_time_limit, start_time, game_settings, chess_log, bitboards, nb_bitboards, transposition_tables);
    printf("score : %d for move from %d to %d for depth 1\n", depth_1_score, get_from_square(best_move), get_to_square(best_move));
    int time_passed = (int)SDL_GetTicks() - start_time;

    // putting back the time limit for the iterative deepening
    think_time_limit = ms_time_of_search; // for the depth 2 search and more (3 seconds)

    // if the depth 1 already took too much time, we need to stop the search since depth 2 will take more time
    if (time_passed > think_time_limit){
        is_search_canceled = true;
    }

    // running the iterative deepening (depth one is already done in the make play function)
    for (int search_depth = 2; search_depth < MAX_DEPTH_ITERATIVE_DEEPENING; search_depth++){

        // making the search for the best move for this AI level
        int score = Search(search_depth, 0, NEGATIVE_INFINITY, POSITIVE_INFINITY, 0, &best_move_this_iteration, &best_score_this_iteration, &is_search_canceled, think_time_limit, start_time, game_settings, chess_log, bitboards, nb_bitboards, transposition_tables);
        printf("score : %d for move from %d to %d for depth %d\n", score, get_from_square(best_move_this_iteration), get_to_square(best_move_this_iteration), search_depth);

        // if the search has been canceled, we need to stop the iterative deepening search
        if (is_search_canceled){ 
            break; // stop the search when the move score is 0 or best_move_this_iteration is 0 but without having to verify it here
        }
        // otherwise, we need to update the best move found since it's sure that we have found a move
        else {
            best_move = best_move_this_iteration;
            best_score = best_score_this_iteration;
            best_move_this_iteration = 0;
            best_score_this_iteration = INT_MIN;

            if (abs(best_score) > IMMEDIATE_MATE_SCORE - 1000){
                break; // stop the search when the move score make a mate since there is not need to look further
            }
        }

    }

    // udpating the selected move if it's not null
    if (!is_move_null(best_move)){
        *selected_move = best_move;
        printf("best score : %d for move from %d to %d\n", best_score, get_from_square(best_move), get_to_square(best_move));
        printf("\n");
    }
}


int Search(int ply_remaining, int ply_from_root, int alpha, int beta, int nb_extensions, move* best_move_this_iteration, int* best_score_this_iteration, bool* is_search_canceled, int think_time_limit, int start_time, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, TT* transposition_tables){

    // before making the search, we need to check if the time left to think is not over
    if ((int)SDL_GetTicks() - start_time > think_time_limit){
        *is_search_canceled = true;
        return 0;
    }

    // if the search is canceled, we need to stop the search
    if (*is_search_canceled){
        return 0;
    }

    // making some cut off to continue the alpha beta pruning 
    if (ply_from_root > 0){
        alpha = max(alpha, -IMMEDIATE_MATE_SCORE + ply_from_root);
        beta = min(beta, IMMEDIATE_MATE_SCORE - ply_from_root);
        // cut off if necessary
        if (alpha >= beta){
            return alpha;
        }
    }

    // looking if we have already evaluated this position in the transposition tables
    bit_board hashed_zobrist_key = 0;
    if (chess_log->actual_size > 0){
        hashed_zobrist_key = get_zobrist_key(bitboards, game_settings->color_of_player_that_is_playing, chess_log->moves[chess_log->actual_size-1]->castling_rights, chess_log->moves[chess_log->actual_size-1]->move_value);
        int TT_value = lookup_for_evaluation_in_TT(hashed_zobrist_key, transposition_tables, ply_remaining, ply_from_root, alpha, beta);
        if (TT_value != FAILED_LOOKUP){
            if (ply_from_root == 0){
                *best_move_this_iteration = transposition_tables->entries[get_index_zobrist_in_TT(hashed_zobrist_key, transposition_tables)].move;
                *best_score_this_iteration = transposition_tables->entries[get_index_zobrist_in_TT(hashed_zobrist_key, transposition_tables)].value;
            }
            return TT_value;
        }
    }

    if (ply_remaining == 0){
        // making the search for the captures happening afterwards (the quiescence search)
        return Quiescience_Search(alpha, beta, is_search_canceled, think_time_limit, start_time, game_settings, chess_log, bitboards, nb_bitboards);
    }

    // generating all the possible moves for the AI at this point and ordering them to make the search faster, because we will search the best moves first
    int nb_moves = 0; 
    move* valid_moves = generate_all_possible_moves(&nb_moves, chess_log, game_settings, bitboards, nb_bitboards);
    // if there are no moves, we need to check if the king is in check, if it is, we return the worst score possible since it's a mate, else we return 0 since it's a draw
    if (nb_moves == 0){
        if (is_check(game_settings->color_of_player_that_is_playing, bitboards, nb_bitboards, chess_log) == CHECK && get_king_index(bitboards, game_settings->color_of_player_that_is_playing) != -1){
            free(valid_moves);
            return -MAX_IA_SCORE;
        }
        free(valid_moves);
        return 0;
    }

    // adding some variables for the transposition tables
    int cut_flag = ALPHA_CUT;
    move best_move_in_this_position = 0;

    // ordering the moves to make the search faster
    order_moves(false, valid_moves, nb_moves, bitboards, nb_bitboards, chess_log, game_settings);
    // searching for the best move by evaluating the position after each move
    for (int i = 0; i < nb_moves; i++){

        int valid_move_from = get_from_square(valid_moves[i]);
        int valid_move_to = get_to_square(valid_moves[i]);
        int flag = get_flag(valid_moves[i]);

        // getting if a capture will happen, used later 
        bool is_capture_happening = will_capture(game_settings->color_of_player_that_is_playing, bitboards, nb_bitboards, valid_move_to);
        if (flag == En_Passant_Flag){
            is_capture_happening = true;
        }

        // making the move first
        make_move_AI(game_settings, chess_log, bitboards, nb_bitboards, valid_moves[i]);

        // Extend the depth of the search in certain interesting cases
        int extension = 0;
        if (extension < MAX_NUMBER_OF_EXTENSIONS){

            // getting some information to know if we need to extend the search
            int targeted_rank = get_rank(valid_move_to);
            int moved_piece_type = get_type_of_piece(bitboards, nb_bitboards, valid_move_from);

            // a check is interesting to look further
            if (is_check(game_settings->color_of_player_that_is_playing, bitboards, nb_bitboards, chess_log) == CHECK){
                extension = 1;
            }
            // it's also interesting to look further if a promotion is near
            else if ((moved_piece_type == PAWN_WHITE || moved_piece_type == PAWN_BLACK) && (targeted_rank == 1 || targeted_rank == 6)){
                extension = 1;
            }

        }

        bool need_full_search = true;
        int eval = 0;

        // Reduce the depth of the search for moves later in the move list as these are less likely to be good (assuming our move ordering isn't terrible)
        if (extension == 0 && ply_remaining >= 3 && i >= 3 && !is_capture_happening){
            // here is our reduced depth
            int reduced_depth = 1;
            // calculating the evaluation of the position at the reduced depth
            eval = -Search(ply_remaining-1-reduced_depth, ply_from_root+1, -alpha - 1, -alpha, nb_extensions, best_move_this_iteration, best_score_this_iteration, is_search_canceled, think_time_limit, start_time, game_settings, chess_log, bitboards, nb_bitboards, transposition_tables);
            // If the evaluation is better than expected, we'd better to a full-depth search to get a more accurate evaluation
			need_full_search = (eval > alpha);
        }
    
        // Perform a full-depth search
        if (need_full_search){
            // calculating the evaluation of the position at the full depth (extended by the interesting cases)
            eval = -Search(ply_remaining-1+extension, ply_from_root+1, -beta, -alpha, nb_extensions+extension, best_move_this_iteration, best_score_this_iteration, is_search_canceled, think_time_limit, start_time, game_settings, chess_log, bitboards, nb_bitboards, transposition_tables);
        }

        // undoing the move to make the search and not modify the game state
        undo_last_move_AI(chess_log, bitboards, nb_bitboards, game_settings);

        // if the search is canceled, during the search at depth-1, we need to stop the search
        if (*is_search_canceled){
            free(valid_moves);
            return 0;
        }
        
        // pruning the search if the score is better than the beta value
        if (eval >= beta){
            store_evaluation_in_TT(hashed_zobrist_key, transposition_tables, ply_remaining, beta, BETA_CUT, valid_moves[i]);
            return beta;
        }
        // updating the alpha value if the score is better than the current alpha value
        if (eval > alpha){
            alpha = eval;

            // udpating the transposition tables variables
            cut_flag = EXACT;
            best_move_in_this_position = valid_moves[i];
            
            // if we're at the first depth (the root here), we need to update the selected move, it's the best move found yet
            if (ply_from_root == 0){
                *best_move_this_iteration = valid_moves[i];
                *best_score_this_iteration = eval;
            }
        }

    }

    // storing the evaluation in the transposition tables
    store_evaluation_in_TT(hashed_zobrist_key, transposition_tables, ply_remaining, alpha, cut_flag, best_move_in_this_position);

    // returning the lower bound of the score if nothing better has been found
    free(valid_moves);
    return alpha;

}


int Quiescience_Search(int alpha, int beta, bool* is_search_canceled, int think_time_limit, int start_time, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards){

    // before making the search, we need to check if the time left to think is not over
    if ((int)SDL_GetTicks() - start_time > think_time_limit){
        *is_search_canceled = true;
        return 0;
    }

    // if the search is canceled, we need to stop the search
    if (*is_search_canceled){
        return 0;
    }

    // evaluating the position
    int evaluation = evaluate(game_settings, bitboards, nb_bitboards);
    // pruning the search if the evaluation is better than the beta value
    if (evaluation >= beta){
       return beta;
    }
    // updating the alpha value if the evaluation is better than the current alpha value
    if (evaluation > alpha){
        alpha = evaluation;
    }

    // since we're dealing with captures, we need to check if the king is still on the board, if not, we return the worst score possible since it's a mate
    if (get_king_index(bitboards, game_settings->color_of_player_that_is_playing) == -1){
        return -MAX_IA_SCORE;
    }

    // generating all the possible moves that captures for the AI at this point and ordering them to make the search faster, because we will search the best moves first
    int nb_moves = 0; 
    move* valid_moves = generate_all_possible_moves_that_capture(&nb_moves, chess_log, game_settings, bitboards, nb_bitboards);
    // if there is no capture left, we return the evaluation
    if (nb_moves == 0){
        free(valid_moves);
        return evaluation;
    }

    // ordering the moves to make the search faster (we only order the captures)
    order_moves(true, valid_moves, nb_moves, bitboards, nb_bitboards, chess_log, game_settings);
    // searching for the best move by evaluating the position after each move
    for (int i = 0; i < nb_moves; i++){

        // making the move, getting the score of the position after the move (updating the evaluation), and undoing the move
        make_move_AI(game_settings, chess_log, bitboards, nb_bitboards, valid_moves[i]);
        evaluation = -Quiescience_Search(-beta, -alpha, is_search_canceled, think_time_limit, start_time, game_settings, chess_log, bitboards, nb_bitboards);
        undo_last_move_AI(chess_log, bitboards, nb_bitboards, game_settings);
        
        // if the search is canceled, during the search at depth-1, we need to stop the search
        if (*is_search_canceled){
            free(valid_moves);
            return 0;
        }
        
        // pruning the search if the evaluation is better than the beta value
        if (evaluation >= beta){
            free(valid_moves);
            return beta;
        }
        // updating the alpha value if the evaluation is better than the current alpha value
        if (evaluation > alpha){
            alpha = evaluation;
        }

    }

    // returning the lower bound of the score if nothing better has been found
    free(valid_moves);
    return alpha;

}

#ifndef __AI_H___
#define __AI_H___


#include "SDL2/SDL.h"


#include "Board.h"
#include "Constants.h"
#include "Evaluation.h"
#include "Log.h"
#include "Move_Generator.h"
#include "Move_Ordering.h"
#include "Moves_Treatment.h"
#include "Search.h"
#include "Settings.h"
#include "Transposition_Table.h"


/////////////////////////////////////////////////////////////////////////////////////
// AI summary
// This part of the code assemble all the functions that are related to the AI testings to create a function that make the AI play
// It also contains the principal function to make the AI play on top of all the search testing functions
/**
 * A summary of the supported function is given below:
 * 
 * make_AI_play : Function to make the AI play (also the final level of the AI entirely)
 * 
 * Random_Int : Function to generate a random integer between min and max
 * make_AI_random_capture_play : Function to make the AI play randomly if a capture isn't possible (level EASY)
 * 
 * Alpha_Beta_LVL2_Search_Valid_Moves : Function to make search for the best evaluation of a move with the alpha-beta pruning with the simple evaluation of the position
 * make_AI_alpha_beta_play : Function to make the AI play with the first level of the alpha-beta pruning, with a simple evaluation of the position
 * 
 * Alpha_Beta_LVL3_Search_Capture_Moves : Function to search for the best evaluation of a move with the alpha-beta pruning with the simple evaluation of the position, only for the captures without depth restriction
 * Alpha_Beta_LVL3_Search_Moves : Function to make search for the best evaluation of a move with the alpha-beta pruning with the simple evaluation of the position, but with an extended search for the captures after the depth is reached
 * make_AI_alpha_beta_play_quiescence_search : Function to make the AI play with the alpha-beta pruning, with an extended search for the captures after the depth is reached
 * 
 * Alpha_Beta_LVL4_Search_Capture_Moves_eval_up : Function to search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, only for the captures without depth restriction
 * Alpha_Beta_LVL4_Search_Moves_eval_up : Function to make search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, but with an extended search for the captures after the depth is reached
 * make_AI_alpha_beta_play_quiescence_search_eval_up : Function to make the AI play with the alpha-beta pruning, with an extended search for the captures after the depth is reached
 * 
 * test_iterative_deepening : Function to make search for the move by using the iterative deepening method for a given time of search
 * Alpha_Beta_LVL5_Search_Capture_Moves_iterative_deepening : Function to search for the best evaluation of a move with the alpha-beta pruning with the simple evaluation of the position, only for the captures without depth restriction, some time constraint were added
 * Alpha_Beta_LVL5_Search_Moves_iterative_deepening : Function to make search for the best evaluation of a move with the alpha-beta pruning with the simple evaluation of the position, but with an extended search for the captures after the depth is reached, some time constraint were added
 * make_AI_alpha_beta_play_iterative_deepening : Function to make the AI play with the alpha-beta pruning, with an extended search for the captures after the depth is reached, some time constraint were added
 * 
 * test_iterative_deepening_transposition_tables : Function to make search for the move by using the iterative deepening method for a given time of search with the transposition tables to fasten the search
 * Alpha_Beta_LVL6_Search_Moves_transposition_tables : Function to make search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, but with an extended search for the captures after the depth is reached with the transposition tables to fasten the search
 * make_AI_alpha_beta_play_transposition_tables : Function to make the AI play with the alpha-beta pruning by using iterative deepening, with an extended search for the captures after the depth is reached, some time constraint were added
 * 
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the AI play (also the final level of the AI entirely)
/**
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards_log : the log of the bitboards of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the captured pieces and the score of the game
 * @param level_of_AI : the level of the AI (EASY, MEDIUM, HARD, …)
 * @param transposition_tables : the transposition tables of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void make_AI_play(Game_Settings* game_settings, Log* chess_log, Bitboards_Log* bitboards_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score, int level_of_AI, TT* transposition_tables);


/////////////////////////////////////////////////////////////////////////////////////
// Function to generate a random integer between min and max
/**
 * @param min : the minimum value
 * @param max : the maximum value
**/
/////////////////////////////////////////////////////////////////////////////////////
int Random_Int(int min, int max);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the AI play randomly if a capture isn't possible (level EASY)
/**
 * @param game_settings : the settings of the game 
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the captured pieces and the score of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void make_AI_random_capture_play(Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make search for the best evaluation of a move with the alpha-beta pruning with the simple evaluation of the position
/**
 * @param depth : the depth we currently are in the alpha-beta pruning search
 * @param lvl2_depth : the depth we need to reach in the alpha-beta pruning search
 * @param alpha : the alpha value
 * @param beta : the beta value
 * @param selected_move : the selected move (from and to, and the flag)
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @return the score of the best evaluation of a move
**/
/////////////////////////////////////////////////////////////////////////////////////
int Alpha_Beta_LVL2_Search_Valid_Moves(int depth, int lvl2_depth, int alpha, int beta, move* selected_move, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards);

/////////////////////////////////////////////////////////////////////////////////////
// Function to make the AI play with the first level of the alpha-beta pruning, with a simple evaluation of the position
/**
 * @param lvl2_depth : the depth of the alpha-beta pruning
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the captured pieces and the score of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void make_AI_alpha_beta_play(int lvl2_depth, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to search for the best evaluation of a move with the alpha-beta pruning with the simple evaluation of the position, only for the captures without depth restriction
/**
 * @param alpha : the alpha value
 * @param beta : the beta value
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @return the score of the best evaluation of a move
**/
/////////////////////////////////////////////////////////////////////////////////////
int Alpha_Beta_LVL3_Search_Capture_Moves(int alpha, int beta, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make search for the best evaluation of a move with the alpha-beta pruning with the simple evaluation of the position, but with an extended search for the captures after the depth is reached
/**
 * @param depth : the depth we currently are in the alpha-beta pruning search
 * @param lvl3_depth : the depth we need to reach in the alpha-beta pruning search
 * @param alpha : the alpha value
 * @param beta : the beta value
 * @param selected_move : the selected move (from and to, and the flag)
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @return the score of the best evaluation of a move
**/
/////////////////////////////////////////////////////////////////////////////////////
int Alpha_Beta_LVL3_Search_Moves(int depth, int lvl3_depth, int alpha, int beta, move* selected_move, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the AI play with the alpha-beta pruning, with an extended search for the captures after the depth is reached
/**
 * @param lvl3_depth : the depth of the alpha-beta pruning
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the captured pieces and the score of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void make_AI_alpha_beta_play_quiescence_search(int lvl3_depth, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, only for the captures without depth restriction
/**
 * @param alpha : the alpha value
 * @param beta : the beta value
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @return the score of the best evaluation of a move
**/
/////////////////////////////////////////////////////////////////////////////////////
int Alpha_Beta_LVL4_Search_Capture_Moves_eval_up(int alpha, int beta, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, but with an extended search for the captures after the depth is reached
/**
 * @param depth : the depth we currently are in the alpha-beta pruning search
 * @param lvl4_depth : the depth we need to reach in the alpha-beta pruning search
 * @param alpha : the alpha value
 * @param beta : the beta value
 * @param selected_move : the selected move (from and to, and the flag)
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @return the score of the best evaluation of a move
**/
/////////////////////////////////////////////////////////////////////////////////////
int Alpha_Beta_LVL4_Search_Moves_eval_up(int depth, int lvl4_depth, int alpha, int beta, move* selected_move, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the AI play with the alpha-beta pruning, with an extended search for the captures after the depth is reached
/**
 * @param lvl4_depth : the depth of the alpha-beta pruning
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the captured pieces and the score of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void make_AI_alpha_beta_play_quiescence_search_eval_up(int lvl4_depth, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make search for the move by using the iterative deepening method for a given time of search
/**
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the captured pieces and the score of the game
 * @param selected_move : the selected move (to be modified by the function)
**/
/////////////////////////////////////////////////////////////////////////////////////
void test_iterative_deepening(Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score, move* selected_move);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, only for the captures without depth restriction
// some conditions of time for the iterative deepening were added
/**
 * @param alpha : the alpha value
 * @param beta : the beta value
 * @param is_search_canceled : a boolean to know if the search is canceled
 * @param think_time_limit : the time limit for the search
 * @param start_time : the time when the search started
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @return the score of the best evaluation of a move
**/
/////////////////////////////////////////////////////////////////////////////////////
int Alpha_Beta_LVL5_Search_Capture_Moves_iterative_deepening(int alpha, int beta, bool* is_search_canceled, int think_time_limit, int start_time, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, but with an extended search for the captures after the depth is reached
// some conditions of time for the iterative deepening were added
/**
 * @param ply_remaining : the number of ply remaining to reach the depth we need to reach in the alpha-beta pruning search 
 * @param ply_from_root : the number of ply from the root of the search (depth currently reached)
 * @param alpha : the alpha value
 * @param beta : the beta value
 * @param best_move_this_iteration : the best move found in this iteration
 * @param best_score_this_iteration : the best score found in this iteration
 * @param is_search_canceled : a boolean to know if the search is canceled
 * @param think_time_limit : the time limit for the search
 * @param start_time : the time when the search started
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @return the score of the best evaluation of a move
**/
/////////////////////////////////////////////////////////////////////////////////////
int Alpha_Beta_LVL5_Search_Moves_iterative_deepening(int ply_remaining, int ply_from_root, int alpha, int beta, move* best_move_this_iteration, int* best_score_this_iteration, bool* is_search_canceled, int think_time_limit, int start_time, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the AI play with the alpha-beta pruning by using iterative deepening, with an extended search for the captures after the depth is reached, some time constraint were added
/**
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the captured pieces and the score of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void make_AI_alpha_beta_play_iterative_deepening(Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make search for the move by using the iterative deepening method for a given time of search with the transposition tables to fasten the search
/**
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the captured pieces and the score of the game
 * @param selected_move : the selected move (to be modified by the function)
 * @param transposition_tables : the transposition tables of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void test_iterative_deepening_transposition_tables(Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score, move* selected_move, TT* transposition_tables);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, but with an extended search for the captures after the depth is reached with the transposition tables to fasten the search
// some conditions of time for the iterative deepening were added
/**
 * @param ply_remaining : the number of ply remaining to reach the depth we need to reach in the alpha-beta pruning search 
 * @param ply_from_root : the number of ply from the root of the search (depth currently reached)
 * @param alpha : the alpha value
 * @param beta : the beta value
 * @param best_move_this_iteration : the best move found in this iteration
 * @param best_score_this_iteration : the best score found in this iteration
 * @param is_search_canceled : a boolean to know if the search is canceled
 * @param think_time_limit : the time limit for the search
 * @param start_time : the time when the search started
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param transposition_tables : the transposition tables of the game
 * @return the score of the best evaluation of a move
**/
/////////////////////////////////////////////////////////////////////////////////////
int Alpha_Beta_LVL6_Search_Moves_transposition_tables(int ply_remaining, int ply_from_root, int alpha, int beta, move* best_move_this_iteration, int* best_score_this_iteration, bool* is_search_canceled, int think_time_limit, int start_time, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, TT* transposition_tables);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the AI play with the alpha-beta pruning by using iterative deepening, with an extended search for the captures after the depth is reached, some time constraint were added
/**
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the captured pieces and the score of the game
 * @param transposition_tables : the transposition tables of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void make_AI_alpha_beta_play_transposition_tables(Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score, TT* transposition_tables);










#endif /* __AI_H__ */
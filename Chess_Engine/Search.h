#ifndef __SEARCH_H__
#define __SEARCH_H__


#include "Constants.h"
#include "Evaluation.h"
#include "Move_Generator.h"
#include "Move_Ordering.h"
#include "Transposition_Table.h"


/////////////////////////////////////////////////////////////////////////////////////
// Search summary
// This module is responsible for the search algorithms of the AI, to find the best move to play (iterative deepening, alpha-beta pruning, quiescence search)$
/**
 * A summary of the supported functions is given below:
 * 
 * run_iterative_deepening : Function to make search for the move by using the iterative deepening method for a given time of search
 * Search : Function to make search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, considering depth extensions for critical moves, but with an extended search for the captures after the depth is reached with the transposition tables to fasten the search
 * Quiescience_Search : Function to make search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, only for the captures without depth restriction
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to make search for the move by using the iterative deepening method for a given time of search
/**
 * @param ms_time_of_search : the time of search in milliseconds (usually 5s to be fast but not too uch so it can think)
 * @param game_settings : the settings of the game
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the captured pieces and the score of the game
 * @param selected_move : the selected move (to be modified by the function)
 * @param transposition_tables : the transposition tables of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void run_iterative_deepening(int ms_time_of_search, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score, move* selected_move, TT* transposition_tables);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make search for the best evaluation of a move with the alpha-beta pruning with a more complex evaluation of the position, considering depth extensions for critical moves, but with an extended search for the captures after the depth is reached with the transposition tables to fasten the search
// some conditions of time for the iterative deepening were added
/**
 * @param ply_remaining : the number of ply remaining to reach the depth we need to reach in the alpha-beta pruning search 
 * @param ply_from_root : the number of ply from the root of the search (depth currently reached)
 * @param alpha : the alpha value
 * @param beta : the beta value
 * @param nb_extensions : the number of extensions to add to the search
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
int Search(int ply_remaining, int ply_from_root, int alpha, int beta, int nb_extensions, move* best_move_this_iteration, int* best_score_this_iteration, bool* is_search_canceled, int think_time_limit, int start_time, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards, TT* transposition_tables);


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
int Quiescience_Search(int alpha, int beta, bool* is_search_canceled, int think_time_limit, int start_time, Game_Settings* game_settings, Log* chess_log, bit_board* bitboards, int nb_bitboards);


#endif /* __SEARCH_H__ */
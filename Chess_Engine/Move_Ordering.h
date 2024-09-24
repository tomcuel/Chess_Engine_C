#ifndef __MOVE_ORDERING_H__
#define __MOVE_ORDERING_H__


#include "Board.h"
#include "Constants.h"
#include "Log.h"
#include "Moves_Treatment.h"
#include "Settings.h"
#include "Utility.h"


/////////////////////////////////////////////////////////////////////////////////////
// Move_Ordering summary
// This part of the code is responsible for ordering the moves to improve the alpha-beta pruning, by ordering the moves that are most likely to be the best moves first.
/**
 * A summary of the supported function is given below:
 * 
 * order_moves : Function to order the moves
 * is_square_attacked_by_opponent_pawn : Function to check if a square is attacked by an opponent pawn
 * quick_sort : Function to sort the moves by their value
 * 
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to order the moves
/**
 * @param is_captures_only : if we want to order only the captures (less time consuming)
 * @param valid_moves : the valid moves to order
 * @param nb_moves : the number of valid moves
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param log : the log of the game
 * @param game_settings : the settings of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void order_moves(bool is_captures_only, move* valid_moves, int nb_moves, bit_board* bitboards, int nb_bitboards, Log* log, Game_Settings* game_settings);


/////////////////////////////////////////////////////////////////////////////////////
// Function to check if a square is attacked by an opponent pawn
/**
 * @param color_of_player_that_is_playing : the color of the player that is playing
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param square : the square to check
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_square_attacked_by_opponent_pawn(int color_of_player_that_is_playing, bit_board* bitboards, int nb_bitboards, int square);


/////////////////////////////////////////////////////////////////////////////////////
// Function to sort the moves by their value
/**
 * @param values : the values of the moves
 * @param valid_moves : the valid moves to order
 * @param nb_moves : the number of valid moves
**/
/////////////////////////////////////////////////////////////////////////////////////
void quick_sort(int* values, move* valid_moves, int nb_moves);


#endif /* __MOVE_ORDERING_H__ */
#ifndef __MOVE_GENERATOR_H__
#define __MOVE_GENERATOR_H__


#include "Board.h"
#include "Constants.h"
#include "Log.h"
#include "Moves_Treatment.h"
#include "Settings.h"


/////////////////////////////////////////////////////////////////////////////////////
// Move_Generator summary
// This module is used to generate all the possible moves, the state of the game and the IA making and undoing moves function
// it's also use a function to get the check state of the game
/**
 * A summary of the supported functions is given below:
 * 
 * are_they_possible_moves : Function to check if there is a possible move for the player
 * get_check_state : Function to get the check state of the game
 * 
 * generate_all_possible_moves : Function to generate all the possible moves for the player (here we care if we are on check after the move)
 * generate_all_moves : Function to generate all the possible moves for the player (here we don't care if we are on check after the move)
 * generate_all_possible_moves_that_capture : Function to generate all the possible moves that capture a piece for the player (here we care if we are on check after the move)
 * generate_all_moves_that_capture : Function to generate all the possible moves that capture a piece for the player (here we don't care if we are on check after the move)
 *
 * make_move_AI : Function to make a move by supposing that the move can be done (will be used in search algorithms of the AI)
 * undo_last_move_AI : Function to undo the last move done by the AI (without the captured pieces and the score as we don't care about them in the search algorithms, as stated in the make_move_AI function)
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to check if there is a possible move for the player
/** 
 * @param log : The log of the game
 * @param game_settings : The settings of the game
 * @param bitboards : The bitboards of the game
 * @param nb_bitboards : The number of bitboards
**/
/////////////////////////////////////////////////////////////////////////////////////
bool are_they_possible_moves(Log* log, Game_Settings* game_settings, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the check state of the game
/**
 * @param color : the color of the player that is playing
 * @param bitboards : the bitboards of the game
 * @param nb_bitboard : the number of bitboards
 * @param log : the log of the game
 * @param game_settings : the settings of the game
 * @return the check state of the game (NO_CHECK, CHECK, CHECK_MATE, DRAW)
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_check_state(int color, bit_board* bitboards, int nb_bitboard, Log* log, Game_Settings* game_settings);


/////////////////////////////////////////////////////////////////////////////////////
// Function to generate all the possible moves for the player (here we care if we are on check after the move)
/** 
 * @param nb_moves : The number of valid moves, will be modified by the function, as a pointer
 * @param log : The log of the game
 * @param game_settings : The settings of the game
 * @param bitboards : The bitboards of the game
 * @param nb_bitboards : The number of bitboards
 * @return an array of moves (containing the from and to square of the move, but also the flags of the move)
**/
/////////////////////////////////////////////////////////////////////////////////////
move* generate_all_possible_moves(int* nb_moves, Log* log, Game_Settings* game_settings, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to generate all the possible moves for the player (here we don't care if we are on check after the move)
/** 
 * @param nb_moves : The number of valid moves, will be modified by the function, as a pointer
 * @param log : The log of the game
 * @param game_settings : The settings of the game
 * @param bitboards : The bitboards of the game
 * @param nb_bitboards : The number of bitboards
 * @return an array of moves (containing the from and to square of the move, but also the flags of the move)
**/
/////////////////////////////////////////////////////////////////////////////////////
move* generate_all_moves(int* nb_moves, Log* log, Game_Settings* game_settings, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to generate all the possible moves that capture a piece for the player (here we care if we are on check after the move)
/** 
 * @param nb_moves : The number of valid moves, will be modified by the function, as a pointer
 * @param log : The log of the game
 * @param game_settings : The settings of the game
 * @param bitboards : The bitboards of the game
 * @param nb_bitboards : The number of bitboards
 * @return an array of moves (containing the from and to square of the move, but also the flags of the move)
**/
/////////////////////////////////////////////////////////////////////////////////////
move* generate_all_possible_moves_that_capture(int* nb_moves, Log* log, Game_Settings* game_settings, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to generate all the possible moves that capture a piece for the player (here we don't care if we are on check after the move)
/** 
 * @param nb_moves : The number of valid moves, will be modified by the function, as a pointer
 * @param log : The log of the game
 * @param game_settings : The settings of the game
 * @param bitboards : The bitboards of the game
 * @param nb_bitboards : The number of bitboards
 * @return an array of moves (containing the from and to square of the move, but also the flags of the move)
**/
/////////////////////////////////////////////////////////////////////////////////////
move* generate_all_moves_that_capture(int* nb_moves, Log* log, Game_Settings* game_settings, bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make a move by supposing that the move can be done (will be used in search algorithms of the AI)
// we don't use the captured pieces and the score because we don't care about them in the search algorithms, it's just to simulate the move and the captured pieces and score is only used to show information to the player
/** 
 * @param game_settings : The settings of the game
 * @param log : The log of the game
 * @param bitboards : The bitboards of the game
 * @param nb_bitboards : The number of bitboards
 * @param move_value : The move to do (containing the from and to square of the move, but also the flags of the move, useful so we don't have to calculate them again)
**/
/////////////////////////////////////////////////////////////////////////////////////
void make_move_AI(Game_Settings* game_settings, Log* log, bit_board* bitboards, int nb_bitboards, move move_value);


/////////////////////////////////////////////////////////////////////////////////////
// Function to undo the last move done by the AI (without the captured pieces and the score as we don't care about them in the search algorithms, as stated in the make_move_AI function)
/** 
 * @param chess_log : The log of the game
 * @param bitboards : The bitboards of the game
 * @param nb_bitboards : The number of bitboards
 * @param game_settings : The settings of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void undo_last_move_AI(Log* chess_log, bit_board* bitboards, int nb_bitboards, Game_Settings* game_settings);


#endif /* __MOVE_GENERATOR_H__ */
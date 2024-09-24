#ifndef __DOWNLOAD_LOG_H__
#define __DOWNLOAD_LOG_H__


#include "Board.h"
#include "Constants.h"
#include "Log.h"
#include "Move_Generator.h"
#include "Settings.h"


/////////////////////////////////////////////////////////////////////////////////////
// Download Log summary
// This part of the code assemble all the functions that are related to download the game status in a file, and open a game depending on the file
/**
 * A summary of the supported function is given below:
 * 
 * download_log : Function to download the log and the game settings in a file
 * open_file_and_setup_chess_game : Function to open the file and update the chessboard to the state of the log and the game settings
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to download the log and the game settings in a file
/**
 * @param log : the log of the game
 * @param bitboard_log : the log of the bitboards of the game
 * @param game_settings : the settings of the game
 * save in a file named "game_log.txt"
**/
/////////////////////////////////////////////////////////////////////////////////////
void download_log(Log* log, Bitboards_Log* bitboard_log, Game_Settings* game_settings);


/////////////////////////////////////////////////////////////////////////////////////
// Function to open the file and update the chessboard to the state of the log and the game settings
/**
 * @param has_opened : boolean to know if the file has been opened
 * @param log : the log of the game
 * @param game_settings : the settings of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param bitboards_log : the log of the bitboards of the game
 * @param captured_pieces_and_score : the captured pieces and the score of the game
 * open the file named "game_log.txt"
**/
/////////////////////////////////////////////////////////////////////////////////////
void open_file_and_setup_chess_game(bool* has_opened, Log* log, Game_Settings* game_settings, bit_board* bitboards, int nb_bitboards, Bitboards_Log* bitboards_log, Captured_Pieces_and_Score* captured_pieces_and_score);


#endif /* __DOWNLOAD_LOG_H__ */
#ifndef __LOG_H__
#define __LOG_H__


#include "Constants.h"


/////////////////////////////////////////////////////////////////////////////////////
// Log summary 
// This module is responsible for creating the log of the game, whats happening after each move, and the log of the bitboards of the game
/** 
 * Two Structures are defined in this module:
 * Move_Element : Represents an element of the log
 * Log : Represents the log of the game
 * 
 * A summary of the supported functions is given below:
 * 
 * create_move_element : Function to create an element of the log
 * create_a_copy_of_move_element : Function to create a copy of an element of the log
 * destroy_move_element : Function to destroy an element of the log
 * 
 * create_log : Function to create the log of the game
 * create_a_copy_of_log : Function to create a copy of the log of the game
 * reset_log : Function to reset the log of the game
 * destroy_log : Function to destroy the log of the game
 * add_move_to_log : Function to add a move to the log at the last index
 * remove_last_move_from_log : Function to remove the last move of the log
 * 
 * create_bitboards_log : Function to create the log of the bitboards of the game
 * create_a_copy_of_bitboards_log : Function to create a copy of the log of the bitboards of the game
 * destroy_bitboards_log : Function to destroy the log of the bitboards of the game
 * reset_bitboards_log : Function to reset the log of the bitboards of the game
 * add_bitboards_to_log : Function to add a move to the log of the bitboards of the game at the last index
 * remove_last_bitboards_from_log : Function to remove the last move of the log of the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents an element of the log
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Log_Element {
    // moves informations 
    move move_value; // the move value : 0-5 bits for the from index, 6-11 bits for the to index, 12-15 bits for the flags (en passant, castle, pawn two up, promotions)
    int captured_piece_type; // the type of the captured piece (PAWN_WHITe, … , KING_BLACK, NOTHING)

    // Castling rights combined into a single 6-bit integer (out of the 8 of the uint8_t)
    // it does take care of the piece movement for the castling with some flags to know which piece has moved or not and update them (the 2 kings and the 4 rooks)
    castling_rights_flags castling_rights; // Using only the lower 6 bits

} Log_Element;


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents the log of the game
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Log {
    Log_Element** moves; // The moves of the game
    int actual_size; // The actual size of the log
    int max_size; // The maximum size of the log
} Log;


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents the log of the bitboards of the game
// to be able to tell about the draw rules
// it's separated from the log of the game because we need to know the position of the pieces and we don't want to copy the bitboards each time and lose time, since it's not used in the AI search
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Bitboards_Log {
    bit_board** bitboards; // An array of the set of bitboards representing the position of the pieces
    int actual_size; // The actual size of the log
    int max_size; // The maximum size of the log
} Bitboards_Log;


/////////////////////////////////////////////////////////////////////////////////////
// Function to create an element of the log
/**
 * @return the element of the log
**/
/////////////////////////////////////////////////////////////////////////////////////
Log_Element* create_move_element();


/////////////////////////////////////////////////////////////////////////////////////
// Function to create a copy of an element of the log
/**
 * @param move_element : the element of the log to copy
 * @return the copy of the element of the log
**/
/////////////////////////////////////////////////////////////////////////////////////
Log_Element* create_a_copy_of_move_element(Log_Element* move_element);


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy an element of the log
/**
 * @param move_element : the element of the log to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void destroy_move_element(Log_Element* move_element);


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the log of the game
/**
 * @param max_size : the maximum size of the log
 * @return the log of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
Log* create_log(int max_size);


/////////////////////////////////////////////////////////////////////////////////////
// Function to create a copy of the log of the game
/**
 * @param log : the log of the game to copy
 * @return the copy of the log of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
Log* create_a_copy_of_log(Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to reset the log of the game
/**
 * @param log : the log of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void reset_log(Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy the log of the game
/**
 * @param log : the log of the game to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void destroy_log(Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add a move to the log at the last index
/**
 * @param log : the log of the game
 * @param move_element : the move to add
**/
/////////////////////////////////////////////////////////////////////////////////////
void add_move_to_log(Log* log, Log_Element* move_element);


/////////////////////////////////////////////////////////////////////////////////////
// Function to remove the last move of the log
/**
 * @param log : the log of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void remove_last_move_from_log(Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the log of the bitboards of the game
/**
 * @return the log of the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
Bitboards_Log* create_bitboards_log(int max_size);


/////////////////////////////////////////////////////////////////////////////////////
// Function to create a copy of the log of the bitboards of the game
/**
 * @param bitboards_log : the log of the bitboards of the game to copy
 * @return the copy of the log of the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
Bitboards_Log* create_a_copy_of_bitboards_log(Bitboards_Log* bitboards_log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy the log of the bitboards of the game
/**
 * @param bitboards_log : the log of the bitboards of the game to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void destroy_bitboards_log(Bitboards_Log* bitboards_log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to reset the log of the bitboards of the game
/**
 * @param bitboards_log : the log of the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void reset_bitboards_log(Bitboards_Log* bitboards_log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add a bitboard set to the log
/**
 * @param bitboards_log : the log of the bitboards of the game
 * @param bitboards : the bitboards to add
**/
/////////////////////////////////////////////////////////////////////////////////////
void add_bitboards_to_log(Bitboards_Log* bitboards_log, bit_board* bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to remove the last bitboards of the log
/**
 * @param bitboards_log : the log of the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void remove_last_bitboards_from_log(Bitboards_Log* bitboards_log);


#endif /* __LOG_H__ */
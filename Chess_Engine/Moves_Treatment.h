#ifndef __MOVES_TREATMENT_H__
#define __MOVES_TREATMENT_H__


#include "Constants.h"
#include "Log.h"
#include "Utility.h"


/////////////////////////////////////////////////////////////////////////////////
// Board summary
// This module is responsible for creating the board of the game, the bitboards, and the captured pieces and the score, as well as treatming how the make_move and undo_function change the different structures
/**
 * A summary of the supported functions is given below:
 * 
 * get_move_value_without_flag : Function to get the move value without the flag
 * get_move_value : Function to get the move value with the flag
 * add_flag_to_move : Function to add a flag to a move value
 * is_move_null : Function to see if a move is null (used in the AI to know if the move is valid)
 * are_same_move : Function to see if two moves are the same
 * get_from_square : Function to get the from square of a move value
 * get_to_square : Function to get the flag of a move value
 * get_flag : Function to get the flag of a move value
 * is_promotion_flag : Function to see if a move is a promotion move
 * get_type_of_promoted_piece : Function to get the type of the promoted piece
 * set_castling_flag : Function to set a specific castling flag
 * is_castling_flag_set : Function to check if a specific castling flag is set
 * 
 * is_legal_pawn_move : Function to see if a move is legal for a pawn
 * is_legal_knight_move : Function to see if a move is legal for a knight
 * is_legal_bishop_move : Function to see if a move is legal for a bishop
 * is_legal_rook_move : Function to see if a move is legal for a rook
 * is_legal_queen_move : Function to see if a move is legal for a queen
 * is_legal_king_move : Function to see if a move is legal for a king
 * is_legal_move : Function to see if a move is legal for a piece by giving the type of the piece that created the legal move
 * get_king_index : Function to get the index of the king in the bitboard array for a color
 * is_case_threatened : Function to see if a case of a certain color is threatened
 * is_check : Function to see if there is a check for a certain color
 * is_castle_possible : Function to see if a castle move is possible
 * is_promotion_possible : Function to see if a promotion move is possible
 * is_en_passant_possible : Function to see if an en passant move is possible
 * has_pawn_moved_two_squares : Function to see if a pawn has moved two squares during the last move
**/
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the move value without the flag
/**
 * @param from : The square from which the piece is moving
 * @param to : The square to which the piece is moving
 * @return the move value without the flag
**/
/////////////////////////////////////////////////////////////////////////////////////
move get_move_value_without_flag(int from, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the move value with the flag
/**
 * @param from : The square from which the piece is moving
 * @param to : The square to which the piece is moving
 * @param flag : The flag of the move
 * @return the move value with the flag
**/
/////////////////////////////////////////////////////////////////////////////////////
move get_move_value(int from, int to, int flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add a flag to a move value
/**
 * @param move_value : The move value
 * @param flag : The flag to add
**/
/////////////////////////////////////////////////////////////////////////////////////
void add_flag_to_move(move* move_value, int flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function see if a move is null (used in the AI to know if the move is valid)
/**
 * @param move_value : The move value
 * @return true if the move is null, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_move_null(move move_value);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if two moves are the same
/**
 * @param move_a : The first move
 * @param move_b : The second move
 * @return true if the moves are the same, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool are_same_move(move move_a, move move_b);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the from square of a move value
/**
 * @param move_value : The move value
 * @return the from square of the move
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_from_square(move move_value);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the flag of a move value
/**
 * @param move_value : The move value
 * @return the flag of the move
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_to_square(move move_value);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the flag of a move value
/**
 * @param move_value : The move value
 * @return the flag of the move
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_flag(move move_value);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a move is a promotion move
/**
 * @param move_flag : The flag of the move
 * @return true if the move is a promotion move, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_promotion_flag(int move_flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the type of the promoted piece
/**
 * @param move_flag : The flag of the move
 * @param color : The color of the promoted piece
 * @return the type of the promoted piece
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_type_of_promoted_piece(int move_flag, int color);


/////////////////////////////////////////////////////////////////////////////////////
// Function to set a specific castling flag
/**
 * @param castling_rights : The castling rights to modify
 * @param flag : The flag to set
**/
/////////////////////////////////////////////////////////////////////////////////////
void set_castling_flag(castling_rights_flags* castling_rights, castling_rights_flags flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to check if a specific castling flag is set
/**
 * @param castling_rights : The castling rights to check
 * @param flag : The flag to check
 * @return true if the flag is set, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_castling_flag_set(castling_rights_flags castling_rights, castling_rights_flags flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a move is legal for a pawn
/**
 * @param color : The color of the pawn
 * @param friendly_pawn_board : The bitboard of the friendly pawns
 * @param friendly_fullboard : The bitboard of the friendly pieces
 * @param enemy_board : The bitboard of the enemy pieces
 * @param from : The square from which the pawn is moving
 * @param to : The square to which the pawn is moving
 * @param from_rank : The rank of the square from which the pawn is moving
 * @param rank_diff : The difference of rank between the square from which the pawn is moving and the square to which the pawn is moving
 * @param file_diff : The difference of file between the square from which the pawn is moving and the square to which the pawn is moving
 * @param flag : The flag of the move (we look here if it's the en passant one)
 * @return 1 if the move is legal, 0 otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_legal_pawn_move(int color, bit_board friendly_pawn_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int from_rank, int rank_diff, int file_diff, int flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a move is legal for a knight
/**
 * @param color : The color of the knight
 * @param friendly_knight_board : The bitboard of the friendly knights
 * @param friendly_fullboard : The bitboard of the friendly pieces
 * @param enemy_board : The bitboard of the enemy pieces
 * @param from : The square from which the knight is moving
 * @param to : The square to which the knight is moving
 * @param rank_diff : The difference of rank between the square from which the knight is moving and the square to which the knight is moving
 * @param file_diff : The difference of file between the square from which the knight is moving and the square to which the knight is moving
 * @return 1 if the move is legal, 0 otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_legal_knight_move(int color, bit_board friendly_knight_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int rank_diff, int file_diff);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a move is legal for a bishop
/**
 * @param color : The color of the bishop
 * @param friendly_bishop_board : The bitboard of the friendly bishops
 * @param friendly_fullboard : The bitboard of the friendly pieces
 * @param enemy_board : The bitboard of the enemy pieces
 * @param from : The square from which the bishop is moving
 * @param to : The square to which the bishop is moving
 * @param from_rank : The rank of the square from which the bishop is moving
 * @param from_file : The file of the square from which the bishop is moving
 * @param to_rank : The rank of the square to which the bishop is moving
 * @param to_file : The file of the square to which the bishop is moving
 * @param rank_diff : The difference of rank between the square from which the bishop is moving and the square to which the bishop is moving
 * @param file_diff : The difference of file between the square from which the bishop is moving and the square to which the bishop is moving
 * @return 1 if the move is legal, 0 otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_legal_bishop_move(int color, bit_board friendly_bishop_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int from_rank, int from_file, int to_rank, int to_file, int rank_diff, int file_diff);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a move is legal for a rook
/**
 * @param color : The color of the rook
 * @param friendly_rook_board : The bitboard of the friendly rooks
 * @param friendly_fullboard : The bitboard of the friendly pieces
 * @param enemy_board : The bitboard of the enemy pieces
 * @param from : The square from which the rook is moving
 * @param to : The square to which the rook is moving
 * @param from_rank : The rank of the square from which the rook is moving
 * @param from_file : The file of the square from which the rook is moving
 * @param to_rank : The rank of the square to which the rook is moving
 * @param to_file : The file of the square to which the rook is moving
 * @param rank_diff : The difference of rank between the square from which the rook is moving and the square to which the rook is moving
 * @param file_diff : The difference of file between the square from which the rook is moving and the square to which the rook is moving
 * @return 1 if the move is legal, 0 otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_legal_rook_move(int color, bit_board friendly_rook_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int from_rank, int from_file, int to_rank, int to_file, int rank_diff, int file_diff);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a move is legal for a queen (the queen is a mix between a rook and a bishop)
/**
 * @param color : The color of the queen
 * @param friendly_queen_board : The bitboard of the friendly queens
 * @param friendly_fullboard : The bitboard of the friendly pieces
 * @param enemy_board : The bitboard of the enemy pieces
 * @param from : The square from which the queen is moving
 * @param to : The square to which the queen is moving
 * @param from_rank : The rank of the square from which the queen is moving
 * @param from_file : The file of the square from which the queen is moving
 * @param to_rank : The rank of the square to which the queen is moving
 * @param to_file : The file of the square to which the queen is moving
 * @param rank_diff : The difference of rank between the square from which the queen is moving and the square to which the queen is moving
 * @param file_diff : The difference of file between the square from which the queen is moving and the square to which the queen is moving
 * @return 1 if the move is legal, 0 otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_legal_queen_move(int color, bit_board friendly_queen_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int from_rank, int from_file, int to_rank, int to_file, int rank_diff, int file_diff);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a move is legal for a king
/**
 * @param color : The color of the king
 * @param friendly_king_board : The bitboard of the friendly kings
 * @param friendly_fullboard : The bitboard of the friendly pieces
 * @param enemy_board : The bitboard of the enemy pieces
 * @param from : The square from which the king is moving
 * @param to : The square to which the king is moving
 * @param rank_diff : The difference of rank between the square from which the king is moving and the square to which the king is moving
 * @param file_diff : The difference of file between the square from which the king is moving and the square to which the king is moving
 * @param flag : The flag of the move (we look here if it's the castling one)
 * @return 1 if the move is legal, 0 otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_legal_king_move(int color, bit_board friendly_king_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int rank_diff, int file_diff, int flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a move is legal for a piece by giving the type of the piece that created the legal move
/**
 * @param attacking_color : The color of the piece that is attacking
 * @param bitboards : The array of bitboards
 * @param nb_bitboard : The number of bitboards
 * @param from : The square from which the piece is moving
 * @param to : The square to which the piece is moving
 * @param flag : The flag of the move
 * @return the type of the piece that is involved in the legal move (NOTHING if it is not a legal move)
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_legal_move(int attacking_color, bit_board* bitboards, int from, int to, int flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the index of the king in the bitboard array for a color
/**
 * @param bitboards : The array of bitboards
 * @param color : The color of the king
 * @return the index of the king in the bitboard array
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_king_index(bit_board* bitboards, int color);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a case of a certain color is threatened
/**
 * @param color : The color of the case
 * @param case_index : The index of the case
 * @param bitboards : The array of bitboards
 * @param nb_bitboard : The number of bitboards
 * @param log : The log of the game
 * @return true if the case is threatened, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_case_threatened(int color, int case_index, bit_board* bitboards, int nb_bitboard, Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if there is a check for a certain color
/**
 * @param color : The color of the king
 * @param bitboards : The array of bitboards
 * @param nb_bitboard : The number of bitboards
 * @param log : The log of the game
 * @return 1 if there is a check, 0 otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_check(int color, bit_board* bitboards, int nb_bitboard, Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a castle move is possible
/**
 * @param color : The color of the king
 * @param bitboards : The array of bitboards
 * @param nb_bitboard : The number of bitboards
 * @param from : The square from which the king is moving
 * @param to : The square to which the king is moving
 * @param log : The log of the game
 * @return true if the castle is possible, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_castle_possible(int color, bit_board* bitboards, int nb_bitboard, int from, int to, Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a promotion move is possible
/**
 * @param color : The color of the pawn
 * @param bitboards : The array of bitboards
 * @param nb_bitboard : The number of bitboards
 * @param from : The square from which the pawn is moving
 * @param to : The square to which the pawn is moving
 * @return true if the promotion is possible, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_promotion_possible(int color, bit_board* bitboards, int nb_bitboard, int from, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if an en passant move is possible
/**
 * @param color : The color of the pawn
 * @param bitboards : The array of bitboards
 * @param nb_bitboard : The number of bitboards
 * @param from : The square from which the pawn is moving
 * @param to : The square to which the pawn is moving
 * @param log : The log of the game
 * @return true if the en passant is possible, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_en_passant_possible(int color, bit_board* bitboards, int nb_bitboard, int from, int to, Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a pawn has moved two squares during the last move
/**
 * @param color : The color of the pawn
 * @param bitboards : The array of bitboards
 * @param nb_bitboard : The number of bitboards
 * @param from : The square from which the pawn is moving
 * @param to : The square to which the pawn is moving
 * @return true if the pawn has moved two squares, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool has_pawn_moved_two_squares(int color, bit_board* bitboards, int nb_bitboard, int from, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if a capture will be done
/**
 * @param color : the color of the player that is playing
 * @param bitboards : the bitboards of the game
 * @param nb_bitboard : the number of bitboards
 * @param to : the position where the piece is moving
 * @return true if a capture will be done, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool will_capture(int color, bit_board* bitboards, int nb_bitboard, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the type of the piece at this position 
/**
 * @param bitboards : the bitboards of the game
 * @param nb_bitboard : the number of bitboards
 * @param position_index : the position of the piece
 * @return the type of the piece at this position
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_type_of_piece(bit_board* bitboards, int nb_bitboard, int position_index);


#endif /* __MOVES_TREATMENT_H__ */
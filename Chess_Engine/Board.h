#ifndef __BOARD_H__
#define __BOARD_H__


#include "Constants.h"
#include "Log.h"
#include "Moves_Treatment.h"
#include "Settings.h"


/////////////////////////////////////////////////////////////////////////////////////
// Board summary
// This module is responsible for creating the bitboards, and the captured pieces and the score, as well as treating how the make_move and undo_function change the different structures for a human player
/**
 * Captured_Pieces_and_Score is a structure that represents the captured pieces and the score
 * 
 * A summary of the supported functions is given below:
 * 
 * create_captured_pieces_and_score : Function to create the structure that represents the captured pieces and the score
 * reset_captured_pieces_and_score : Function to reset the captured pieces and the score
 * copy_captured_pieces_and_score : Function to add a piece to the captured pieces and the score
 * destroy_captured_pieces_and_score : Function to free the memory of the captured pieces and the score
 * get_value_of_piece : Function to get the value of a piece
 * 
 * init_bitboards : Function to create the bitboards of the game 
 * reset_bitboards : Function to reset the bitboards of the game to the initial position
 * create_a_copy_of_bitboards : Function to create a copy of the bitboards of the game
 * copy_bitboards_in_bitboards : Function to copy the bitboards of the game in another bitboards
 * destroy_bitboards : Function to free the memory of the bitboards of the game
 * 
 * move_piece : Function to make a move on the board
 * clear_piece : Function to clear a piece on the board
 * move_rook_during_castle : Function to make the move of the rook during a castle (that we know is happening)
 * clear_piece_during_en_passant : Function to clear the piece during an en passant since it's not the same as a normal capture
 * make_move : Function to make a move on the board (uses all the previous functions to make the move)
 * 
 * update_score : Function to calculate the score and update it in the structure that represents the captured pieces and the score
 * update_captured_piece_and_score : Function to update the captured piece and the score
 * update_log : Function to update the log (after a move has been done we need to update the general information of the log)
 * update_log_and_captured_piece_and_score : Function to update the log and the captured piece and the score at once
 * 
 * update_castle_in_log : Function to update the castle in the log
 * update_piece_movement_for_castle_in_log : Function to update the piece movement for castle in the log
 * update_castle_state_in_log : Function to update the castle state in the log
 * 
 * undo_last_move : Function to undo the last move (update all the structures to the previous state)
 * 
 * are_bitboards_equal : Function to know if two chess positions are equal
 * is_draw_forced_by_3_repetition_of_position_rule : Function to know if a draw is forced by the 3 repetition of position rule (we can't have the same position 3 times during a game, if we have it's a draw)
 * is_draw_forced_by_50_moves_rule : Function to know if a draw is forced by the 50 moves rule (if we have 50 moves without any capture or pawn move, it's a draw)
 * is_draw_forced_by_insuffisant_material : Function to know if a draw is forced by insuffisant material
 * is_draw_forced_by_rules : Function to know if a draw is forced by any of the previous draw rules and return the type of the draw
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents the captured pieces and the score
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Captured_Pieces_and_Score {
    int max_number_of_pieces_per_color; // The maximum number of pieces that can be captured per color

    int* white_capture_pieces; // The pieces that have been captured by the black player
    int number_of_white_captured_pieces; // The number of pieces that have been captured by the black player

    int* black_capture_pieces; // The pieces that have been captured by the white player
    int number_of_black_captured_pieces; // The number of pieces that have been captured by the white player

    int players_that_is_winning; // The player that is winning White_Player, Black_Player (or Draw for 0 as score)
    int score; // The score of the player that is winning
} Captured_Pieces_and_Score;


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the structure that represents the captured pieces and the score
/**
 * @param max_number_of_pieces : the maximum number of pieces that can be captured per color
 * @return the structure that represents the captured pieces and the score
**/
Captured_Pieces_and_Score* create_captured_pieces_and_score(int max_number_of_pieces);


/////////////////////////////////////////////////////////////////////////////////////
// Function to reset the captured pieces and the score
/**
 * @param Captured_Pieces_and_Score : the structure that represents the captured pieces and the score
**/
/////////////////////////////////////////////////////////////////////////////////////
void reset_captured_pieces_and_score(Captured_Pieces_and_Score* Captured_Pieces_and_Score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add a piece to the captured pieces and the score
/**
 * @param Captured_Pieces_and_Score : the structure that represents the captured pieces and the score
 * @return the structure that represents the captured pieces and the score that has been copied
**/
/////////////////////////////////////////////////////////////////////////////////////
Captured_Pieces_and_Score* copy_captured_pieces_and_score(Captured_Pieces_and_Score* Captured_Pieces_and_Score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to free the memory of the captured pieces and the score
/**
 * @param Captured_Pieces_and_Score : the structure that represents the captured pieces and the score
**/
/////////////////////////////////////////////////////////////////////////////////////
void destroy_captured_pieces_and_score(Captured_Pieces_and_Score* captured_piece_and_score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the value of a piece
/**
 * @param piece_type : the type of the piece (PAWN_WHITE, KNIGHT_WHITE, BISHOP_WHITE, ROOK_WHITE, QUEEN_WHITE, KING_WHITE, PAWN_BLACK, KNIGHT_BLACK, BISHOP_BLACK, ROOK_BLACK, QUEEN_BLACK, KING_BLACK, NOTHING)
 * @return the value of the piece
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_value_of_piece(int piece_type);


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the bitboards of the game
/**
 * @return the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
bit_board* init_bitboards();


/////////////////////////////////////////////////////////////////////////////////////
// Function to reset the bitboards of the game to the initial position
/**
 * @param bitboards_array : the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void reset_bitboards(bit_board* bitboards_array);


/////////////////////////////////////////////////////////////////////////////////////
// Function to create a copy of the bitboards of the game
/**
 * @param bitboards_array : the bitboards of the game
 * @return the copy of the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
bit_board* create_a_copy_of_bitboards(bit_board* bitboards_array);


/////////////////////////////////////////////////////////////////////////////////////
// Function to copy the bitboards of the game in another bitboards
/**
 * @param bitboards_array : the bitboards of the game
 * @param copy_bitboards_array : the copy of the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void copy_bitboards_in_bitboards(bit_board* bitboards_array, bit_board* copy_bitboards_array);


/////////////////////////////////////////////////////////////////////////////////////
// Function to free the memory of the bitboards of the game
/**
 * @param bitboards_array : the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void destroy_bitboards(bit_board* bitboards_array);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make a move on the board (it make the move by changing the piece of position "from" to position "to", but also all the pieces of the same color)
/**
 * @param moving_piece_bitboard : the bitboard of the piece that is moving
 * @param color_that_is_playing : the color that is playing (WHITE_PLAYER, BLACK_PLAYER)
 * @param bitboards : the bitboards of the game
 * @param from : the position of the piece that is moving
 * @param to : the position where the piece is moving
**/
/////////////////////////////////////////////////////////////////////////////////////
void move_piece(bit_board* moving_piece_bitboard, int color_that_is_playing, bit_board* bitboards, int from, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to clear a piece on the board (it clear the piece of position "to", but also all the pieces of the opposite color of the one playing)
/**
 * @param bitboard : the bitboard of the piece that is moving
 * @param to : the position where the piece is moving
 * @param color : the color of the piece that is moving
**/
/////////////////////////////////////////////////////////////////////////////////////
void clear_piece(bit_board* bitboard, int to, int color);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the move of the rook during a castle (that we know is happening)
/**
 * @param bitboards : the bitboards of the game
 * @param from : the position of the piece that is moving
 * @param to : the position where the piece is moving
**/
/////////////////////////////////////////////////////////////////////////////////////
void move_rook_during_castle(bit_board* bitboards, int from, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to clear the piece during an en passant since it's not the same as a normal capture
/**
 * @param bitboards : the bitboards of the game
 * @param color : the color of the piece that is moving
 * @param to : the position where the piece is moving
**/
/////////////////////////////////////////////////////////////////////////////////////
void clear_piece_during_en_passant(bit_board* bitboards, int color, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make a move on the board (uses all the previous functions to make the move)
/**
 * @param game_settings : the settings of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param move_value : the move that is going to be done (with the start square, the target square and the flags)
 * @param type_move_legal_attacking : the type of the piece that is moving, supposing the move is legal here (PAWN_WHITE, KNIGHT_WHITE, BISHOP_WHITE, ROOK_WHITE, QUEEN_WHITE, KING_WHITE, PAWN_BLACK, KNIGHT_BLACK, BISHOP_BLACK, ROOK_BLACK, QUEEN_BLACK, KING_BLACK)
**/
/////////////////////////////////////////////////////////////////////////////////////
void make_move(Game_Settings* game_settings, bit_board* bitboards, int nb_bitboards, int from, int to, int flag, int type_move_legal_attacking);


/////////////////////////////////////////////////////////////////////////////////////
// Function to calculate the score and update it in the structure that represents the captured pieces and the score
/**
 * @param captured_pieces_and_score : the structure that represents the captured pieces and the score
**/
/////////////////////////////////////////////////////////////////////////////////////
void update_score(Captured_Pieces_and_Score* captured_pieces_and_score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to update the captured piece and the score
/**
 * @param piece_taken_typen : the type of the piece that has been taken
 * @param captured_pieces_and_score : the structure that represents the captured pieces and the score
**/
/////////////////////////////////////////////////////////////////////////////////////
void update_captured_piece_and_score(int piece_taken_typen, Captured_Pieces_and_Score* captured_pieces_and_score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to update the log (after a move has been done we need to update the general information of the log)
/**
 * @param chess_log : the log of the game
 * @param move_value : the move that is going to be done (with the start square, the target square and the flags)
 * @param piece_taken_type : the type of the piece that has been taken
**/
/////////////////////////////////////////////////////////////////////////////////////
void update_log(Log* chess_log, move move_value, int piece_taken_type);


/////////////////////////////////////////////////////////////////////////////////////
// Function to update the log and the captured piece and the score at once
/**
 * @param chess_log : the log of the game
 * @param captured_pieces_and_score : the structure that represents the captured pieces and the score
 * @param move_value : the move that is going to be done (with the start square, the target square and the flags)
 * @param piece_taken_type : the type of the piece that has been taken
**/
/////////////////////////////////////////////////////////////////////////////////////
void update_log_and_captured_piece_and_score(Log* chess_log, Captured_Pieces_and_Score* captured_pieces_and_score, move move_value, int piece_taken_type);


/////////////////////////////////////////////////////////////////////////////////////
// Function to update the castle in the log (after a castle has been done we need to update the general information of the log)
/**
 * @param chess_log : the log of the game
 * @param from : the position of the piece that is moving
 * @param to : the position where the piece is moving
 * @param color_that_played_the_move : the color that played the move
**/
/////////////////////////////////////////////////////////////////////////////////////
void update_castle_in_log(Log* chess_log, int from, int to, int color_that_played_the_move);


/////////////////////////////////////////////////////////////////////////////////////
// Function to update the piece movement of some piece useful to know if we can castle
/**
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void update_piece_movement_for_castle_in_log(Log* chess_log, bit_board* bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to update the castle state in the log
/**
 * @param chess_log : the log of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param from : the position of the piece that is moving
 * @param to : the position where the piece is moving
 * @param flag : the flag of the move
 * @param color_of_player_that_will_play_next : the color of the player that will play next
**/
/////////////////////////////////////////////////////////////////////////////////////
void update_castle_state_in_log(Log* chess_log, bit_board* bitboards, int nb_bitboards, int from, int to, int flag, int color_of_player_that_will_play_next);


/////////////////////////////////////////////////////////////////////////////////////
// Function to undo the last move (update all the structures to the previous state)
/**
 * @param chess_log : the log of the game
 * @param bitboard_log : the log of the bitboards of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param captured_pieces_and_score : the structure that represents the captured pieces and the score
 * @param game_settings : the settings of the game
**/
/////////////////////////////////////////////////////////////////////////////////////
void undo_last_move(Log* chess_log, Bitboards_Log* bitboard_log, bit_board* bitboards, int nb_bitboards, Captured_Pieces_and_Score* captured_pieces_and_score, Game_Settings* game_settings);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if two chess positions are equal
/**
 * @param bitboards1 : the first bitboards
 * @param bitboards2 : the second bitboards
 * @param nb_bitboards : the number of bitboards
 * @return true if the two bitboards are equal, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool are_bitboards_equal(bit_board* bitboards1, bit_board* bitboards2, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if a draw is forced by the 3 repetition of position rule (we can't have the same position 3 times during a game, if we have it's a draw)
/**
 * @param bitboard_log : the log of the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @return true if a draw is forced by the 3 repetition of position rule, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_draw_forced_by_3_repetition_of_position_rule(Bitboards_Log* bitboard_log, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if a draw is forced by the 50 moves rule (if we have 50 moves without any capture or pawn move, it's a draw)
/**
 * @param chess_log : the log of the game
 * @param bitboard_log : the log of the bitboards of the game
 * @return true if a draw is forced by the 50 moves rule, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_draw_forced_by_50_moves_rule(Log* chess_log, Bitboards_Log* bitboard_log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if a draw is forced by insuffisant material 
// (if we have only the two kings on the board, it's a draw for example)
// (the problem is too complex to fully implement it, so we just check some trivial cases)
/**
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @return true if a draw is forced by insuffisant material, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_draw_forced_by_insuffisant_material(bit_board* bitboards, int nb_bitboards);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if a draw is forced by any of the previous draw rules and return the type of the draw
/**
 * @param chess_log : the log of the game
 * @param bitboard_log : the log of the bitboards of the game
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @return DRAW_BY_3_RULES if a draw is forced by the 3 repetition of position rule, DRAW_BY_50_RULES if a draw is forced by the 50 moves rule, NO_DRAW otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_draw_forced_by_rules(Log* chess_log, Bitboards_Log* bitboard_log, bit_board* bitboards, int nb_bitboards);


#endif /* __BOARD_H__ */
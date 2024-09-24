#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"


#include "Board.h"
#include "Constants.h"
#include "Log.h"
#include "Move_Generator.h"
#include "Moves_Treatment.h"
#include "Settings.h"
#include "Utility.h"


/////////////////////////////////////////////////////////////////////////////////////
// Graphics summary 
// This part of the code is used to show the game graphics depending on which we're in
/**
 * Button is a structure that represents the buttons (the area to click on and the activity state) in the game
 * 
 * A summary of the supported functions is given below:
 * 
 * create_buttons : Function to create the array of buttons and initialize them also, since no special initialization needs to be done
 * reset_buttons_state : Function to reset the buttons state to UNACTIVE
 * destroy_buttons : Function to destroy the array of buttons
 * 
 * show_load_menu : to show the menu rendering (depending on which menu we are)
 * show_chess_board : Function to show the chess board
 * show_trajectory : Function to draw the possible place where a piece can go to
 * show_captured_pieces : Function to show the captured pieces of the players
 * show_score : Function to show the score of the game next to the captured pieces on the winning side
 * show_updated_timer : to show the timer, remaining for each player
 * add_move_in_log_render : to add a move on the render log part of the screen
 * show_log : to show the log of the moves
 * show_menu_button_in_game : to show the menu / parameters button during the game
 * show_confirmation_menu : to show the confirmation menu (only if a buttons is clicked)
 * show_victory_menu : to show the victory menu
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Button is a structure that represents the buttons (the area to click on and the activity state) in the game
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Button{
    SDL_Rect rect; // the rectangle of the button
    int state; // the state of the button : UNACTIVE or ACTIVE
    // the type will be given by the position in the enum of buttons
    // for example Buttons[5] correspond to the button "NEXT_BUTTON_GAME_CHOICE" since in the enum NEXT_BUTTON_GAME_CHOICE=5
} Button;


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the array of buttons and initialize them also, since no special initialization needs to be done 
/**
 * @param number_of_buttons : the number of buttons, ie the size of the array
 * @return Button** : a pointer to the array of buttons created
**/
/////////////////////////////////////////////////////////////////////////////////////
Button** create_buttons(int number_of_buttons);


/////////////////////////////////////////////////////////////////////////////////////
// Function to reset the buttons state to UNACTIVE
/**
 * @param Buttons : the array of Buttons
**/
/////////////////////////////////////////////////////////////////////////////////////
void reset_buttons_state(Button** Buttons);


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy the array of buttons
/**
 * @param number_of_buttons : the number of buttons, ie the size of the array
 * @param Buttons : the array of Buttons
**/
/////////////////////////////////////////////////////////////////////////////////////
void destroy_buttons(int number_of_buttons, Button** Buttons);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the menu rendering (clearing it and showing it)
// not all the buttons will be shown, only the ones that are needed, depending on the menu_type and if the button is used for a menu or for the game
// the state in the button will be used to show the button in a different color if it is active or not (we have different pictures)
/**
 * @param renderer : the renderer to show the menu
 * @param menu_type : the menu_type to show : GAMEMPLAY_CHOICE, DIFFICULTY_CHOICE, TIME_CHOICE
 * @param Buttons : the buttons to show
 * @param is_clicked : to know if a click has already been made
 * @param draw_red_boundary_move : the red boundary to draw around a piece when it's selected to make a move
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_load_menu(SDL_Renderer* renderer, int menu_type, Button** Buttons, bool is_clicked, SDL_Rect draw_red_boundary_move);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the chess board
/**
 * @param renderer : the renderer to show the chess board
 * @param bitboards : an array of bitboards to represent the board
 * @param number_of_bitboards : the number of bitboards
 * @param log : the log of the moves
 * @param game_settings : the game settings
 * @param is_clicked : to know if a click has already been made
 * @param draw_red_boundary_move : the red boundary to draw around a piece when it's selected to make a move (it can and will also be useful for the in game buttons)
 * @param is_reversed : if the board is reversed or not
 * @param selected_piece_index : the index of the selected piece
 * @param piece_movement_rect : the rectangle of the piece movement
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_chess_board(SDL_Renderer *renderer, bit_board* bitboards, int number_of_bitboards, Log* log, Game_Settings* game_settings, bool is_clicked, SDL_Rect draw_red_boundary_move, bool is_reversed, int selected_piece_index, SDL_Rect piece_movement_rect);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the possible place where a piece can go to 
/**
 * @param renderer : the renderer to show the trajectory
 * @param bitboards : all the bitboards of the game
 * @param nb_bitboards_per_color : the number of bit boards per color (not including the all pieces one)
 * @param game_settings : the game settings
 * @param log : the log of the moves
 * @param is_clicked : to know if a click has already been made
 * @param is_click_on_board : if the board is clicked
 * @param selected_piece_index : the index of the selected piece
 * @param is_reversed : if the board is reversed or not
 * @param color_playing : the color of the player playing
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_trajectory(SDL_Renderer* renderer, bit_board* bitboards, int nb_bitboards, Game_Settings* game_settings, Log* log, bool is_cliked, bool is_click_on_board, int selected_piece_index, bool is_reversed, int color_playing);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the captured pieces of the players
// One for the player 1 and one for the player 2, on the top of the screen for the white captured pieces and on the bottom for the black captured pieces
/**
 * @param renderer : the renderer to show the captured pieces
 * @param captured_pieces_and_score : the captured pieces to show
 * @param is_reversed : if the board is reversed or not
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_captured_pieces(SDL_Renderer* renderer, Captured_Pieces_and_Score* captured_pieces_and_score, bool is_reversed);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the score of the game next to the captured pieces on the winning side
/**
 * @param renderer : the renderer to show the score
 * @param captured_pieces_and_score : the captured pieces to show
 * @param is_reversed : if the board is reversed or not
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_score(SDL_Renderer* renderer, Captured_Pieces_and_Score* captured_pieces_and_score, bool is_reversed);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the timer, remaining for each player
// It will not be inplemented in the first version of the game, but it will be implemented in the second version
// Since we don't have ttf, it might need time to do it (either by showing it pixel by pixel or by using the terminal)
/**
 * @param renderer : the renderer to show the timer
 * @param time_player_white : the time remaining for the white player 
 * @param time_player_black : the time remaining for the black player 
 * @param player_playing : the player playing (WHITE_PLAYER or BLACK_PLAYER)
 * @param is_reversed : if the board is reversed or not
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_updated_timer(SDL_Renderer* renderer, int time_player_white, int time_player_black, int player_playing, bool is_reversed);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add a move on the render log part of the screen 
/**
 * @param renderer : the renderer to show the log
 * @param log_index : the index of the log to show
 * @param log : the log to show
 * @param bitboard_log : the bitboards log of the game
 * @param game_settings : the game settings
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param color_playing : the color of the move
 * @param font_size : the font size of the text
 * @param sdl_color : the color of the text
 * @param middle_x : the middle x of the screen
 * @param middle_y : the middle y of the screen
**/
/////////////////////////////////////////////////////////////////////////////////////
void add_move_in_log_render(SDL_Renderer* renderer, int log_index, Log* log, Bitboards_Log* bitboard_log, Game_Settings* game_settings, bit_board* bitboards, int nb_bitboards, int color_playing, int font_size, SDL_Color sdl_color, int middle_x, int middle_y);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the log of the moves
/**
 * @param renderer : the renderer to show the log
 * @param log : the log to show
 * @param bitboard_log : the bitboards log of the game
 * @param game_settings : the game settings
 * @param bitboards : the bitboards of the game
 * @param nb_bitboards : the number of bitboards
 * @param is_pawn_promotion_happening : if the pawn promotion is happening then we can't show the log since we need to show the promotion menu
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_log(SDL_Renderer* renderer, Log* log, Bitboards_Log* bitboard_log, Game_Settings* game_settings, bit_board* bitboards, int nb_bitboards, bool is_pawn_promotion_happening);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the menu / parameters button during the game 
/**
 * @param renderer : the renderer to show the menu button
 * @param Buttons : the buttons to show
 * @param is_pawn_promotion_happening : if the pawn promotion is happening : will show different buttons in this case
 * @param color_promoted_pawn : the color of the promoted pawn
 * @param is_game_paused : if the game is paused or not
 * @param game_mode : to know the game mode (useful if it's the IAvsIA mode to show the pause button)
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_menu_button_in_game(SDL_Renderer* renderer, Button** Buttons, bool is_pawn_promotion_happening, int color_promoted_pawn, bool is_game_paused, int game_mode);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the confirmation menu (only if a buttons is clicked)
/**
 * @param renderer : the renderer to show the confirmation menu
 * @param buttons : the buttons to show
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_confirmation_menu(SDL_Renderer* renderer, Button** buttons);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the victory menu
/**
 * @param renderer : the renderer to show the victory menu
 * @param buttons : the buttons to show
 * @param game_settings : the game settings
 * @param is_clicked : to know if a click has already been made
 * @param draw_red_boundary_move : the red boundary to draw around a piece when it's selected to make a move
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_victory_menu(SDL_Renderer* renderer, Button** buttons, Game_Settings* game_settings, bool is_clicked, SDL_Rect draw_red_boundary_move);


#endif /* __GRAPHICS_H__ */
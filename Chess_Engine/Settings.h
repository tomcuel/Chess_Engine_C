#ifndef __SETTINGS_H__
#define __SETTINGS_H__


#include "Constants.h"


/////////////////////////////////////////////////////////////////////////////////////
// Game Settings summary
/**
 * Game_Settings is a structure that represents the game settings.
 * 
 * A summary of the supported function is given below:
 * 
 * create_game_settings : Function to create the game settings and its default values
 * reset_game_settings : Function to reset the game settings
 * create_a_copy_of_game_settings : Function to create a copy of the game settings
 * destroy_game_settings : Function to destroy the game settings
 * change_player_that_is_playing : Function to change the player that is playing
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents the game settings
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Game_Settings {
    int game_mode; // The game mode (PLAYER_VS_PLAYER, PLAYER_VS_AI, AI_VS_AI)
    int white_player_type; // If the white player is an AI (HUMAN, AI)
    int black_player_type; // If the black player is an AI (HUMAN, AI)
    int white_AI_difficulty; // The difficulty of the white AI (NONE, EASY, MEDIUM, HARD)
    int black_AI_difficulty; // The difficulty of the black AI (NONE, EASY, MEDIUM, HARD)
    int player_that_is_playing; // The player that is playing (White_Player or Black_Player)
    int color_of_player_that_is_playing; // The color of the player that is playing (WHITE, BLACK)
    int loosing_player; // The player that is loosing (Undetermined, White_Player, Black_Player or Draw)

    int time_mode; // The time mode of the game (SHORT_BLITZ, LONG_BLITZ, SHORT, MODERATE, LONG)
    float time_at_start; // The time at the start of the game
    float blitz_time; // The time for the blitz mode (how much we add to a player's time after each move)
    float white_time_remaining; // The time remaining for the white player
    float black_time_remaining; // The time remaining for the black player

    bool has_match_started; // If the match has started (true) or not (false)
    bool is_game_on_pause; // If the game is on pause (true) or not (false), for the IAvsIA mode
    bool is_pawn_promotion_happening; // If a pawn promotion is happening (true) or not (false), to avoid to move the pieces during the promotion
    int color_of_pawn_promotion; // The color of the pawn promotion (NO_COLOR, WHITE, BLACK)
    bool is_board_reversed; // If the board is reversed (true) or not (false)
} Game_Settings;


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the game settings and its default values
/**
 * @return the game settings
**/
/////////////////////////////////////////////////////////////////////////////////////
Game_Settings* create_game_settings();


/////////////////////////////////////////////////////////////////////////////////////
// Function to reset the game settings
/**
 * @param game_settings : the game settings to reset
**/
/////////////////////////////////////////////////////////////////////////////////////
void reset_game_settings(Game_Settings* game_settings);


/////////////////////////////////////////////////////////////////////////////////////
// Function to create a copy of the game settings
/**
 * @param game_settings : the game settings to copy
 * @return the copy of the game settings
**/
/////////////////////////////////////////////////////////////////////////////////////
Game_Settings* create_a_copy_of_game_settings(Game_Settings* game_settings);


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy the game settings
/**
 * @param game_settings : the game settings to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void destroy_game_settings(Game_Settings* game_settings);


/////////////////////////////////////////////////////////////////////////////////////
// Function to change the player that is playing
/**
 * @param game_settings : the game settings
**/
/////////////////////////////////////////////////////////////////////////////////////
void change_player_that_is_playing(Game_Settings* game_settings);


#endif /* __SETTINGS_H__ */
#include "Settings.h"


Game_Settings* create_game_settings(){
    Game_Settings* game_settings = (Game_Settings*)malloc(sizeof(Game_Settings));
    // looking for malloc errors
    if (game_settings == NULL){
        printf("Error: memory allocation failed in Create_Game_Settings\n");
        return NULL;
    }

    // setting the default values
    game_settings->game_mode = PLAYER_VS_PLAYER;
    game_settings->white_player_type = HUMAN;
    game_settings->black_player_type = HUMAN;
    game_settings->white_AI_difficulty = NONE;
    game_settings->black_AI_difficulty = NONE;
    game_settings->player_that_is_playing = White_Player;
    game_settings->color_of_player_that_is_playing = WHITE;
    game_settings->loosing_player = Undetermined;
    game_settings->time_mode = SHORT;
    game_settings->time_at_start = 0;
    game_settings->blitz_time = 0;
    game_settings->white_time_remaining = 10*60;
    game_settings->black_time_remaining = 10*60;
    game_settings->has_match_started = false;
    game_settings->is_game_on_pause = false;
    game_settings->is_pawn_promotion_happening = false;
    game_settings->color_of_pawn_promotion = NO_COLOR;
    game_settings->is_board_reversed = false;

    // returning the game settings
    return game_settings;
}


void reset_game_settings(Game_Settings* game_settings){
    // setting the default values
    game_settings->game_mode = PLAYER_VS_PLAYER;
    game_settings->white_player_type = HUMAN;
    game_settings->black_player_type = HUMAN;
    game_settings->white_AI_difficulty = NONE;
    game_settings->black_AI_difficulty = NONE;
    game_settings->player_that_is_playing = White_Player;
    game_settings->color_of_player_that_is_playing = WHITE;
    game_settings->loosing_player = Undetermined;
    game_settings->time_mode = SHORT;
    game_settings->time_at_start = 0;
    game_settings->blitz_time = 0;
    game_settings->white_time_remaining = 10*60;
    game_settings->black_time_remaining = 10*60;
    game_settings->has_match_started = false;
    game_settings->is_game_on_pause = false;
    game_settings->is_pawn_promotion_happening = false;
    game_settings->color_of_pawn_promotion = NO_COLOR;
    game_settings->is_board_reversed = false;
}


Game_Settings* create_a_copy_of_game_settings(Game_Settings* game_settings){
    Game_Settings* game_settings_copy = (Game_Settings*)malloc(sizeof(Game_Settings));
    // looking for malloc errors
    if (game_settings_copy == NULL){
        printf("Error: memory allocation failed in Create_Game_Settings\n");
        return NULL;
    }

    // copying the values
    game_settings_copy->game_mode = game_settings->game_mode;
    game_settings_copy->white_player_type = game_settings->white_player_type;
    game_settings_copy->black_player_type = game_settings->black_player_type;
    game_settings_copy->white_AI_difficulty = game_settings->white_AI_difficulty;
    game_settings_copy->black_AI_difficulty = game_settings->black_AI_difficulty;
    game_settings_copy->player_that_is_playing = game_settings->player_that_is_playing;
    game_settings_copy->color_of_player_that_is_playing = game_settings->color_of_player_that_is_playing;
    game_settings_copy->loosing_player = game_settings->loosing_player;
    game_settings_copy->time_mode = game_settings->time_mode;
    game_settings_copy->time_at_start = game_settings->time_at_start;
    game_settings_copy->blitz_time = game_settings->blitz_time;
    game_settings_copy->white_time_remaining = game_settings->white_time_remaining;
    game_settings_copy->black_time_remaining = game_settings->black_time_remaining;
    game_settings_copy->has_match_started = game_settings->has_match_started;
    game_settings_copy->is_game_on_pause = game_settings->is_game_on_pause;
    game_settings_copy->is_pawn_promotion_happening = game_settings->is_pawn_promotion_happening;
    game_settings_copy->color_of_pawn_promotion = game_settings->color_of_pawn_promotion;
    game_settings_copy->is_board_reversed = game_settings->is_board_reversed;

    // returning the copy
    return game_settings_copy;
}


void destroy_game_settings(Game_Settings* game_settings){
    // if no malloc error, we can free the memory
    if (game_settings != NULL){
        free(game_settings);
    }
}


void change_player_that_is_playing(Game_Settings* game_settings){

    if (game_settings == NULL){
        printf("Error: game_settings is NULL in Change_Player_that_is_Playing\n");
        return;
    }

    // changing the player that is playing
    if (game_settings->player_that_is_playing == White_Player && game_settings->color_of_player_that_is_playing == WHITE){
        game_settings->player_that_is_playing = Black_Player;
        game_settings->color_of_player_that_is_playing = BLACK;
    }
    else if (game_settings->player_that_is_playing == Black_Player && game_settings->color_of_player_that_is_playing == BLACK){
        game_settings->player_that_is_playing = White_Player;
        game_settings->color_of_player_that_is_playing = WHITE;
    }
}

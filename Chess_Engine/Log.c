#include "Log.h"


Log_Element* create_move_element(){

    Log_Element* move_element = (Log_Element*)malloc(sizeof(Log_Element));
    // looking for malloc errors
    if (move_element == NULL){
        printf("Error: memory allocation failed in Create_Move_Element\n");
        return NULL;
    }

    // setting the default values
    move_element->move_value = 0;
    move_element->captured_piece_type = NOTHING;
    move_element->castling_rights = 0;

    // returning the element of the log
    return move_element;
}


Log_Element* create_a_copy_of_move_element(Log_Element* move_element){

    Log_Element* move_element_copy = (Log_Element*)malloc(sizeof(Log_Element));
    // looking for malloc errors
    if (move_element_copy == NULL){
        printf("Error: memory allocation failed in Create_Move_Element\n");
        return NULL;
    }

    // copying the values
    move_element_copy->move_value = move_element->move_value;
    move_element_copy->captured_piece_type = move_element->captured_piece_type;
    move_element_copy->castling_rights = move_element->castling_rights;

    // returning the copy of the element of the log
    return move_element_copy;
}


void destroy_move_element(Log_Element* move_element){
    // if no malloc error
    if (move_element != NULL){
        // freeing the memory
        free(move_element);
    }
}


Log* create_log(int max_size){
    
    Log* log = (Log*)malloc(sizeof(Log));
    // looking for malloc errors
    if (log == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return NULL;
    }
    
    // setting the default values for the sizes and if the castles have been done
    log->actual_size = 0;
    log->max_size = max_size;

    // allocating the memory for the Log_Element
    log->moves = (Log_Element**)malloc(sizeof(Log_Element*)*max_size);
    // looking for malloc errors
    if (log->moves == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return NULL;
    }
    for (int i = 0; i < max_size; i++){
        log->moves[i] = create_move_element();
        // looking for malloc errors
        if (log->moves[i] == NULL){
            printf("Error: memory allocation failed in Create_Log\n");
            return NULL;
        }
    }
    
    // returning the log
    return log;
}


Log* create_a_copy_of_log(Log* log){

    Log* log_copy = (Log*)malloc(sizeof(Log));
    // looking for malloc errors
    if (log_copy == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return NULL;
    }

    // copying the values
    log_copy->actual_size = log->actual_size;
    log_copy->max_size = log->max_size;

    // allocating the memory for the Log_Element
    log_copy->moves = (Log_Element**)malloc(sizeof(Log_Element*)*log->max_size);
    // looking for malloc errors
    if (log_copy->moves == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return NULL;
    }
    for (int i = 0; i < log->max_size; i++){
        log_copy->moves[i] = create_a_copy_of_move_element(log->moves[i]);
        // looking for malloc errors
        if (log_copy->moves[i] == NULL){
            printf("Error: memory allocation failed in Create_Log\n");
            return NULL;
        }
    }

    // returning the copy of the log
    return log_copy;
}


void reset_log(Log* log){
    // resetting the values
    log->actual_size = 0;
}


void destroy_log(Log* log){
    // looking for malloc errors
    if (log != NULL){
        // freeing the memory
        for (int i = 0; i < log->max_size; i++){
            // looking for malloc errors
            if (log->moves[i] != NULL){
                destroy_move_element(log->moves[i]);
            }
        }
        free(log->moves);
        free(log);
    }
}


void add_move_to_log(Log* log, Log_Element* move_element){
    // if the log is full, we need to free the memory of the first element and make a shift
    if (log->actual_size == log->max_size){
        printf("Error: the log is full in Add_Move_to_Log\n");
        return;
    }

    // looking for malloc errors
    if (log == NULL || move_element == NULL || log->moves == NULL){
        printf("Error: log or move_element is NULL in Add_Move_to_Log\n");
        return;
    }
    
    // copying the move element
    log->moves[log->actual_size] = create_a_copy_of_move_element(move_element);
    // looking for malloc errors
    if (log->moves[log->actual_size] == NULL){
        printf("Error: memory allocation failed in Add_Move_to_Log\n");
        return;
    }
    // incrementing the actual size
    log->actual_size++;
}


void remove_last_move_from_log(Log* log){
    // we don't need to free the memory of the last element, we just need to decrease the actual size
    log->actual_size--;
}


Bitboards_Log* create_bitboards_log(int max_size){
    Bitboards_Log* bitboard_log = (Bitboards_Log*)malloc(sizeof(Bitboards_Log));
    // looking for malloc errors
    if (bitboard_log == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return NULL;
    }
    
    // setting the default values for the sizes and if the castles have been done
    bitboard_log->actual_size = 0;
    bitboard_log->max_size = max_size;

    // allocating the memory for the array of bitboards
    bitboard_log->bitboards = (bit_board**)malloc(sizeof(bit_board*)*max_size);
    // looking for malloc errors
    if (bitboard_log->bitboards == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return NULL;
    }
    for (int i = 0; i < max_size; i++){
        bitboard_log->bitboards[i] = (bit_board*)malloc(sizeof(bit_board)*NUMBER_OF_BIBOARD);
        // looking for malloc errors
        if (bitboard_log->bitboards[i] == NULL){
            printf("Error: memory allocation failed in Create_Log\n");
            return NULL;
        }
    }

    // returning the log
    return bitboard_log;
}


Bitboards_Log* create_a_copy_of_bitboards_log(Bitboards_Log* bitboards_log){
    
    Bitboards_Log* bitboards_log_copy = (Bitboards_Log*)malloc(sizeof(Bitboards_Log));
    // looking for malloc errors
    if (bitboards_log_copy == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return NULL;
    }

    // copying the values
    bitboards_log_copy->actual_size = bitboards_log->actual_size;
    bitboards_log_copy->max_size = bitboards_log->max_size;
    
    // allocating the memory for the array of bitboards
    bitboards_log_copy->bitboards = (bit_board**)malloc(sizeof(bit_board*)*bitboards_log->max_size);
    // looking for malloc errors
    if (bitboards_log_copy->bitboards == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return NULL;
    }
    for (int i = 0; i < bitboards_log->max_size; i++){
        bitboards_log_copy->bitboards[i] = (bit_board*)malloc(sizeof(bit_board)*NUMBER_OF_BIBOARD);
        // looking for malloc errors
        if (bitboards_log_copy->bitboards[i] == NULL){
            printf("Error: memory allocation failed in Create_Log\n");
            return NULL;
        }
        // copying the bitboards
        for (int j = 0; j < NUMBER_OF_BIBOARD; j++){
            bitboards_log_copy->bitboards[i][j] = bitboards_log->bitboards[i][j];
        }
    }

    // returning the copy of the log
    return bitboards_log_copy;

}


void destroy_bitboards_log(Bitboards_Log* bitboards_log){
    // looking for malloc errors
    if (bitboards_log != NULL){
        // freeing the memory
        for (int i = 0; i < bitboards_log->max_size; i++){
            // looking for malloc errors
            if (bitboards_log->bitboards[i] != NULL){
                free(bitboards_log->bitboards[i]);
            }
        }
        free(bitboards_log->bitboards);
        free(bitboards_log);
    }
}


void reset_bitboards_log(Bitboards_Log* bitboards_log){
    // resetting the values
    bitboards_log->actual_size = 0;
}


void add_bitboards_to_log(Bitboards_Log* bitboards_log, bit_board* bitboards){
    // if the log is full, we need to free the memory of the first element and make a shift
    if (bitboards_log->actual_size == bitboards_log->max_size){
        printf("Error: the log is full in Add_Move_to_Log\n");
        return;
    }
    // looking for malloc errors
    if (bitboards_log == NULL){
        printf("Error: log or move_element is NULL in Add_Move_to_Log\n");
        return;
    }

    // copying the bitboards
    for (int i = 0; i < NUMBER_OF_BIBOARD; i++){
        bitboards_log->bitboards[bitboards_log->actual_size][i] = bitboards[i];
    }
    // incrementing the actual size
    bitboards_log->actual_size++;
}


void remove_last_bitboards_from_log(Bitboards_Log* bitboards_log){
    // we don't need to free the memory of the last element, we just need to decrease the actual size
    bitboards_log->actual_size--;
}

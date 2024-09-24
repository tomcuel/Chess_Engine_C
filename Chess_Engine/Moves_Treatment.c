#include "Moves_Treatment.h"


move get_move_value_without_flag(int from, int to){
    return (move)(from | to << 6);
}


move get_move_value(int from, int to, int flag){
    return (move)(from | to << 6 | flag << 12);
}


void add_flag_to_move(move* move_value, int flag){
    *move_value = *move_value | flag << 12;
}


bool is_move_null(move move_value){
    return (move_value == 0);
}


bool are_same_move(move move_a, move move_b){
    return move_a == move_b;
}


int get_from_square(move move_value){
    return move_value & start_square_mask;
}


int get_to_square(move move_value){
    return (move_value & target_square_mask) >> 6;
}


int get_flag(move move_value){
    return move_value >> 12;
}


bool is_promotion_flag(int move_flag){
    return move_flag >= Promote_To_Queen_Flag;
}


int get_type_of_promoted_piece(int move_flag, int color){
    if (move_flag == Promote_To_Queen_Flag && color == WHITE){
        return QUEEN_WHITE;
    }
    if (move_flag == Promote_To_Queen_Flag && color == BLACK){
        return QUEEN_BLACK;
    }
    if (move_flag == Promote_To_Rook_Flag && color == WHITE){
        return ROOK_WHITE;
    }
    if (move_flag == Promote_To_Rook_Flag && color == BLACK){
        return ROOK_BLACK;
    }
    if (move_flag == Promote_To_Bishop_Flag && color == WHITE){
        return BISHOP_WHITE;
    }
    if (move_flag == Promote_To_Bishop_Flag && color == BLACK){
        return BISHOP_BLACK;
    }
    if (move_flag == Promote_To_Knight_Flag && color == WHITE){
        return KNIGHT_WHITE;
    }
    if (move_flag == Promote_To_Knight_Flag && color == BLACK){
        return KNIGHT_BLACK;
    }
    return NOTHING;
}


void set_castling_flag(castling_rights_flags* castling_rights, castling_rights_flags flag) {
    *castling_rights |= flag;
}


bool is_castling_flag_set(castling_rights_flags castling_rights, castling_rights_flags flag) {
    return (castling_rights & flag) != 0;
}


int is_legal_pawn_move(int color, bit_board friendly_pawn_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int from_rank, int rank_diff, int file_diff, int flag) {
    
    // check if this is a pawn at the starting rank
    if (!(friendly_pawn_board & (1ULL << from))){
        return 0;
    }
    
    // looking for an en passant move
    if (flag == En_Passant_Flag){
        return 1;
    }
    
    if (color == WHITE){
        // Move forward one square
        if (rank_diff == 1 && file_diff == 0 && !(friendly_fullboard & (1ULL << to)) && !(enemy_board & (1ULL << to))) {
            return 1;
        }
        // Move forward two squares from the starting rank
        if (rank_diff == 2 && file_diff == 0 && from_rank == 1 && !(friendly_fullboard & (1ULL << to)) && !(enemy_board & (1ULL << to)) && !(friendly_fullboard & (1ULL << (from + 8))) && !(enemy_board & (1ULL << (from + 8)))) {
            return 1;
        }
        // Capture diagonally
        if (rank_diff == 1 && abs(file_diff) == 1 && (enemy_board & (1ULL << to))) {
            return 1;
        }
    }
    else if (color == BLACK){
        // Move forward one square
        if (rank_diff == -1 && file_diff == 0 && !(friendly_fullboard & (1ULL << to)) && !(enemy_board & (1ULL << to))) {
            return 1;
        }
        // Move forward two squares from the starting rank
        if (rank_diff == -2 && file_diff == 0 && from_rank == 6 && !(friendly_fullboard & (1ULL << to)) && !(enemy_board & (1ULL << to)) && !(friendly_fullboard & (1ULL << (from - 8))) && !(enemy_board & (1ULL << (from - 8)))) {
            return 1;
        }
        // Capture diagonally
        if (rank_diff == -1 && abs(file_diff) == 1 && (enemy_board & (1ULL << to))) {
            return 1;
        }
    }

    return 0;
}


int is_legal_knight_move(int color, bit_board friendly_knight_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int rank_diff, int file_diff) {
    
    // check if this is a knight at the starting rank
    if (!(friendly_knight_board & (1ULL << from))){
        return 0;
    }

    rank_diff = abs(rank_diff);
    file_diff = abs(file_diff);
    
    // Knight moves in an L-shape: 2 squares in one direction and 1 in the other
    if ((rank_diff == 2 && file_diff == 1) || (rank_diff == 1 && file_diff == 2)) {
        if (enemy_board & (1ULL << to)) {
            return 1; // Capture enemy piece
        } 
        else if (!(friendly_fullboard & (1ULL << to))) {
            return 1; // Move to an empty square
        }
    }

    return 0;
}


int is_legal_bishop_move(int color, bit_board friendly_bishop_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int from_rank, int from_file, int to_rank, int to_file, int rank_diff, int file_diff) {
    
    // check if this is a bishop at the starting rank
    if (!(friendly_bishop_board & (1ULL << from))){
        return 0;
    }

    rank_diff = abs(rank_diff);
    file_diff = abs(file_diff);

    // Bishop moves diagonally
    if (rank_diff == file_diff) {
        // no piece between the bishop and the target square
        int rank_direction = (to_rank - from_rank) / rank_diff;
        int file_direction = (to_file - from_file) / file_diff;
        for (int i = 1; i < rank_diff; i++) {
            if (friendly_fullboard & (1ULL << (from + i * 8 * rank_direction + i * file_direction))) {
                return 0;
            }
            else if (enemy_board & (1ULL << (from + i * 8 * rank_direction + i * file_direction))) {
                return 0;
            }
        }
        if (enemy_board & (1ULL << to)) {
            return 1; // Capture enemy piece
        } 
        else if (!(friendly_fullboard & (1ULL << to))) {
            return 1; // Move to an empty square
        }
    }

    return 0;
}


int is_legal_rook_move(int color, bit_board friendly_rook_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int from_rank, int from_file, int to_rank, int to_file, int rank_diff, int file_diff) {
   
    // check if this is a rook at the starting rank
    if (!(friendly_rook_board & (1ULL << from))){
        return 0;
    }

    rank_diff = abs(rank_diff);
    file_diff = abs(file_diff);
    
    // Rook moves horizontally or vertically
    if ((rank_diff == 0 && file_diff > 0) || (file_diff == 0 && rank_diff > 0)) {
        // no piece between the rook and the target square
        if (rank_diff > 0) {
            int rank_direction = (to_rank - from_rank) / rank_diff;
            for (int i = 1; i < rank_diff; i++) {
                if (friendly_fullboard & (1ULL << (from + i * 8 * rank_direction))) {
                    return 0;
                }
                else if (enemy_board & (1ULL << (from + i * 8 * rank_direction))) {
                    return 0;
                }
            }
        }
        if (file_diff > 0) {
            int file_direction = (to_file - from_file) / file_diff;
            for (int i = 1; i < file_diff; i++) {
                if (friendly_fullboard & (1ULL << (from + i * file_direction))) {
                    return 0;
                }
                else if (enemy_board & (1ULL << (from + i * file_direction))) {
                    return 0;
                }
            }
        }
        if (enemy_board & (1ULL << to)) {
            return 1; // Capture enemy piece
        } 
        else if (!(friendly_fullboard & (1ULL << to))) {
            return 1; // Move to an empty square
        }
    }

    return 0;
}


int is_legal_queen_move(int color, bit_board friendly_queen_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int from_rank, int from_file, int to_rank, int to_file, int rank_diff, int file_diff) {
    // Queen moves like a rook or a bishop
    return (is_legal_bishop_move(color, friendly_queen_board, friendly_fullboard, enemy_board, from, to, from_rank, from_file, to_rank, to_file, rank_diff, file_diff) || is_legal_rook_move(color, friendly_queen_board, friendly_fullboard, enemy_board, from, to, from_rank, from_file, to_rank, to_file, rank_diff, file_diff));
}


int is_legal_king_move(int color, bit_board friendly_king_board, bit_board friendly_fullboard, bit_board enemy_board, int from, int to, int rank_diff, int file_diff, int flag) {
    
    // check if this is a king at the starting rank
    if (!(friendly_king_board & (1ULL << from))){
        return 0;
    }

    // Check for castling
    if (flag == Castle_Flag){
        return 1;
    }

    rank_diff = abs(rank_diff);
    file_diff = abs(file_diff);
    
    // King moves one square in any direction
    if (rank_diff <= 1 && file_diff <= 1) {
        if (enemy_board & (1ULL << to)) {
            return 1; // Capture enemy piece
        } 
        else if (!(friendly_fullboard & (1ULL << to))) {
            return 1; // Move to an empty square
        }
    }

    return 0;
}


int is_legal_move(int attacking_color, bit_board* bitboards, int from, int to, int flag){

    int from_rank = get_rank(from);
    int to_rank = get_rank(to);
    int from_file = get_file(from);
    int to_file = get_file(to);
    int rank_diff = to_rank - from_rank;
    int file_diff = to_file - from_file;

    // check if the move is legal
    // for the white player
    if (attacking_color == WHITE){
        if (is_legal_pawn_move(WHITE, bitboards[PAWN_WHITE], bitboards[WHITE_PIECES], bitboards[BLACK_PIECES], from, to, from_rank, rank_diff, file_diff, flag)){
            return PAWN_WHITE;
        }
        if (is_legal_knight_move(WHITE, bitboards[KNIGHT_WHITE], bitboards[WHITE_PIECES], bitboards[BLACK_PIECES], from, to, rank_diff, file_diff)){
            return KNIGHT_WHITE;
        }
        if (is_legal_bishop_move(WHITE, bitboards[BISHOP_WHITE], bitboards[WHITE_PIECES], bitboards[BLACK_PIECES], from, to, from_rank, from_file, to_rank, to_file, rank_diff, file_diff)){
            return BISHOP_WHITE;
        }
        if (is_legal_rook_move(WHITE, bitboards[ROOK_WHITE], bitboards[WHITE_PIECES], bitboards[BLACK_PIECES], from, to, from_rank, from_file, to_rank, to_file, rank_diff, file_diff)){
            return ROOK_WHITE;
        }
        if (is_legal_queen_move(WHITE, bitboards[QUEEN_WHITE], bitboards[WHITE_PIECES], bitboards[BLACK_PIECES], from, to, from_rank, from_file, to_rank, to_file, rank_diff, file_diff)){
            return QUEEN_WHITE;
        }
        if (is_legal_king_move(WHITE, bitboards[KING_WHITE], bitboards[WHITE_PIECES], bitboards[BLACK_PIECES], from, to, rank_diff, file_diff, flag)){
            return KING_WHITE;
        }
    }
    // for the black player
    else if (attacking_color == BLACK){
        if (is_legal_pawn_move(BLACK, bitboards[PAWN_BLACK], bitboards[BLACK_PIECES], bitboards[WHITE_PIECES], from, to, from_rank, rank_diff, file_diff, flag)){
            return PAWN_BLACK;
        }
        if (is_legal_knight_move(BLACK, bitboards[KNIGHT_BLACK], bitboards[BLACK_PIECES], bitboards[WHITE_PIECES], from, to, rank_diff, file_diff)){
            return KNIGHT_BLACK;
        }
        if (is_legal_bishop_move(BLACK, bitboards[BISHOP_BLACK], bitboards[BLACK_PIECES], bitboards[WHITE_PIECES], from, to, from_rank, from_file, to_rank, to_file, rank_diff, file_diff)){
            return BISHOP_BLACK;
        }
        if (is_legal_rook_move(BLACK, bitboards[ROOK_BLACK], bitboards[BLACK_PIECES], bitboards[WHITE_PIECES], from, to, from_rank, from_file, to_rank, to_file, rank_diff, file_diff)){
            return ROOK_BLACK;
        }
        if (is_legal_queen_move(BLACK, bitboards[QUEEN_BLACK], bitboards[BLACK_PIECES], bitboards[WHITE_PIECES], from, to, from_rank, from_file, to_rank, to_file, rank_diff, file_diff)){
            return QUEEN_BLACK;
        }
        if (is_legal_king_move(BLACK, bitboards[KING_BLACK], bitboards[BLACK_PIECES], bitboards[WHITE_PIECES], from, to, rank_diff, file_diff, flag)){
            return KING_BLACK;
        }
    }

    // default
    return NOTHING;
}


int get_king_index(bit_board* bitboards, int color){
    if (color == WHITE){
        // if there is no king on the board, return -1
        if (bitboards[KING_WHITE] == 0x0000000000000000ULL){
            return -1;
        }
        // return the index of the king, only if the king is present on the board, otherwise, the answer is not consistent
        return __builtin_ctzll(bitboards[KING_WHITE]);
    }
    else if (color == BLACK){
        // if there is no king on the board, return -1
        if (bitboards[KING_BLACK] == 0x0000000000000000ULL){
            return -1;
        }
        // return the index of the king, only if the king is present on the board, otherwise, the answer is not consistent
        return __builtin_ctzll(bitboards[KING_BLACK]);
    }
    return -1;
}


bool is_case_threatened(int color, int case_index, bit_board* bitboards, int nb_bitboard, Log* log){

    // looking for a pawn that can threaten the case
    // a white pawn can threaten the case for a black player
    if (bitboards[PAWN_WHITE] & (1ULL << (case_index -7)) && case_index - 7 >= 0 && get_file(case_index) != 7 && color == BLACK){
        return 1;
    }
    if (bitboards[PAWN_WHITE] & (1ULL << (case_index -9)) && case_index - 9 >= 0 && get_file(case_index) != 0 && color == BLACK){
        return 1;
    }
    // a black pawn can threaten the case for a white player
    if (bitboards[PAWN_BLACK] & (1ULL << (case_index +7)) && case_index + 7 < NUMBER_SQUARES && get_file(case_index) != 0 && color == WHITE){
        return 1;
    }
    if (bitboards[PAWN_BLACK] & (1ULL << (case_index +9)) && case_index + 9 < NUMBER_SQUARES && get_file(case_index) != 7 && color == WHITE){
        return 1;
    }
    // look for en passant (the out of range will be dealt with in the is_en_passant_possible function)
    if (is_en_passant_possible(BLACK, bitboards, NUMBER_OF_BIBOARD, case_index, case_index + 7, log)){
        return 1;
    }
    if (is_en_passant_possible(BLACK, bitboards, NUMBER_OF_BIBOARD, case_index, case_index + 9, log)){
        return 1;
    }
    if (is_en_passant_possible(WHITE, bitboards, NUMBER_OF_BIBOARD, case_index, case_index - 7, log)){
        return 1;
    }
    if (is_en_passant_possible(WHITE, bitboards, NUMBER_OF_BIBOARD, case_index, case_index - 9, log)){
        return 1;
    }


    // looking for a knight that can threaten the case
    // a white knight can threaten the case for a black player
    if (bitboards[KNIGHT_WHITE] & (1ULL << (case_index +6)) && case_index + 6 < NUMBER_SQUARES && get_file(case_index+6) == get_file(case_index)-2 && get_rank(case_index+6) == get_rank(case_index)+1 && color == BLACK){
        return 1;
    }
    if (bitboards[KNIGHT_WHITE] & (1ULL << (case_index +10)) && case_index + 10 < NUMBER_SQUARES && get_file(case_index+10) == get_file(case_index)+2 && get_rank(case_index+10) == get_rank(case_index)+1 && color == BLACK){
        return 1;
    }
    if (bitboards[KNIGHT_WHITE] & (1ULL << (case_index +15)) && case_index + 15 < NUMBER_SQUARES && get_file(case_index+15) == get_file(case_index)-1 && get_rank(case_index+15) == get_rank(case_index)+2 && color == BLACK){
        return 1;
    }
    if (bitboards[KNIGHT_WHITE] & (1ULL << (case_index +17)) && case_index + 17 < NUMBER_SQUARES && get_file(case_index+17) == get_file(case_index)+1 && get_rank(case_index+17) == get_rank(case_index)+2 && color == BLACK){
        return 1;
    }
    if (bitboards[KNIGHT_WHITE] & (1ULL << (case_index -6)) && case_index - 6 >= 0 && get_file(case_index-6) == get_file(case_index)+2 && get_rank(case_index-6) == get_rank(case_index)-1 && color == BLACK){
        return 1;
    }
    if (bitboards[KNIGHT_WHITE] & (1ULL << (case_index -10)) && case_index - 10 >= 0 && get_file(case_index-10) == get_file(case_index)-2 && get_rank(case_index-10) == get_rank(case_index)-1 && color == BLACK){
        return 1;
    }
    if (bitboards[KNIGHT_WHITE] & (1ULL << (case_index -15)) && case_index - 15 >= 0 && get_file(case_index-15) == get_file(case_index)+1 && get_rank(case_index-15) == get_rank(case_index)-2 && color == BLACK){
        return 1;
    }
    if (bitboards[KNIGHT_WHITE] & (1ULL << (case_index -17)) && case_index - 17 >= 0 && get_file(case_index-17) == get_file(case_index)-1 && get_rank(case_index-17) == get_rank(case_index)-2 && color == BLACK){
        return 1;
    }
    // a black knight can threaten the case for a white player
    if (bitboards[KNIGHT_BLACK] & (1ULL << (case_index +6)) && case_index + 6 < NUMBER_SQUARES && get_file(case_index+6) == get_file(case_index)-2 && get_rank(case_index+6) == get_rank(case_index)+1 && color == WHITE){
        return 1;
    }
    if (bitboards[KNIGHT_BLACK] & (1ULL << (case_index +10)) && case_index + 10 < NUMBER_SQUARES && get_file(case_index+10) == get_file(case_index)+2 && get_rank(case_index+10) == get_rank(case_index)+1 && color == WHITE){
        return 1;
    }
    if (bitboards[KNIGHT_BLACK] & (1ULL << (case_index +15)) && case_index + 15 < NUMBER_SQUARES && get_file(case_index+15) == get_file(case_index)-1 && get_rank(case_index+15) == get_rank(case_index)+2 && color == WHITE){
        return 1;
    }
    if (bitboards[KNIGHT_BLACK] & (1ULL << (case_index +17)) && case_index + 17 < NUMBER_SQUARES && get_file(case_index+17) == get_file(case_index)+1 && get_rank(case_index+17) == get_rank(case_index)+2 && color == WHITE){
        return 1;
    }
    if (bitboards[KNIGHT_BLACK] & (1ULL << (case_index -6)) && case_index - 6 >= 0 && get_file(case_index-6) == get_file(case_index)+2 && get_rank(case_index-6) == get_rank(case_index)-1 && color == WHITE){
        return 1;
    }
    if (bitboards[KNIGHT_BLACK] & (1ULL << (case_index -10)) && case_index - 10 >= 0 && get_file(case_index-10) == get_file(case_index)-2 && get_rank(case_index-10) == get_rank(case_index)-1 && color == WHITE){
        return 1;
    }
    if (bitboards[KNIGHT_BLACK] & (1ULL << (case_index -15)) && case_index - 15 >= 0 && get_file(case_index-15) == get_file(case_index)+1 && get_rank(case_index-15) == get_rank(case_index)-2 && color == WHITE){
        return 1;
    }
    if (bitboards[KNIGHT_BLACK] & (1ULL << (case_index -17)) && case_index - 17 >= 0 && get_file(case_index-17) == get_file(case_index)-1 && get_rank(case_index-17) == get_rank(case_index)-2 && color == WHITE){
        return 1;
    }


    // looking for a king that can threaten the case
    // a white king can threaten the case for a black player
    if (bitboards[KING_WHITE] & (1ULL << (case_index +1)) && case_index + 1 < NUMBER_SQUARES && get_file(case_index) != 7 && color == BLACK){
        return 1;
    }
    if (bitboards[KING_WHITE] & (1ULL << (case_index -1)) && case_index - 1 >= 0 && get_file(case_index) != 0 && color == BLACK){
        return 1;
    }
    if (bitboards[KING_WHITE] & (1ULL << (case_index +7)) && case_index + 7 < NUMBER_SQUARES && get_file(case_index) != 0 && get_rank(case_index) != 7 && color == BLACK){
        return 1;
    }
    if (bitboards[KING_WHITE] & (1ULL << (case_index +8)) && case_index + 8 < NUMBER_SQUARES && get_rank(case_index) != 7 && color == BLACK){
        return 1;
    }
    if (bitboards[KING_WHITE] & (1ULL << (case_index +9)) && case_index + 9 < NUMBER_SQUARES && get_file(case_index) != 7 && get_rank(case_index) != 7 && color == BLACK){
        return 1;
    }
    if (bitboards[KING_WHITE] & (1ULL << (case_index -7)) && case_index - 7 >= 0 && get_file(case_index) != 7 && get_rank(case_index) != 0 && color == BLACK){
        return 1;
    }
    if (bitboards[KING_WHITE] & (1ULL << (case_index -8)) && case_index - 8 >= 0 && get_rank(case_index) != 0 && color == BLACK){
        return 1;
    }
    if (bitboards[KING_WHITE] & (1ULL << (case_index -9)) && case_index - 9 >= 0 && get_file(case_index) != 0 && get_rank(case_index) != 0 && color == BLACK){
        return 1;
    }
    // a black king can threaten the case for a white player
    if (bitboards[KING_BLACK] & (1ULL << (case_index +1)) && case_index + 1 < NUMBER_SQUARES && get_file(case_index) != 7 && color == WHITE){
        return 1;
    }
    if (bitboards[KING_BLACK] & (1ULL << (case_index -1)) && case_index - 1 >= 0 && get_file(case_index) != 0 && color == WHITE){
        return 1;
    }
    if (bitboards[KING_BLACK] & (1ULL << (case_index +7)) && case_index + 7 < NUMBER_SQUARES && get_file(case_index) != 0 && get_rank(case_index) != 7 && color == WHITE){
        return 1;
    }
    if (bitboards[KING_BLACK] & (1ULL << (case_index +8)) && case_index + 8 < NUMBER_SQUARES && get_rank(case_index) != 7 && color == WHITE){
        return 1;
    }
    if (bitboards[KING_BLACK] & (1ULL << (case_index +9)) && case_index + 9 < NUMBER_SQUARES && get_file(case_index) != 7 && get_rank(case_index) != 7 && color == WHITE){
        return 1;
    }
    if (bitboards[KING_BLACK] & (1ULL << (case_index -7)) && case_index - 7 >= 0 && get_file(case_index) != 7 && get_rank(case_index) != 0 && color == WHITE){
        return 1;
    }
    if (bitboards[KING_BLACK] & (1ULL << (case_index -8)) && case_index - 8 >= 0 && get_rank(case_index) != 0 && color == WHITE){
        return 1;
    }
    if (bitboards[KING_BLACK] & (1ULL << (case_index -9)) && case_index - 9 >= 0 && get_file(case_index) != 0 && get_rank(case_index) != 0 && color == WHITE){
        return 1;
    }


    // looking for a bishop or a queen that can threaten the case (diagonally)
    // from the top left to the bottom right (case_index - 7 increments)
    for (int i = case_index - 7; i >= 0; i -= 7){
        // the diagonal needs to be continuous and not cross the border of the board to appear again on the other side
        if (get_file(i) == 0){
            break;
        }
        if (bitboards[BISHOP_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[QUEEN_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[BISHOP_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[QUEEN_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[WHITE_PIECES] & (1ULL << i) || bitboards[BLACK_PIECES] & (1ULL << i)){
            break;
        }
    }
    // from the top right to the bottom left (case_index - 9 increments)
    for (int i = case_index - 9; i >= 0; i -= 9){
        // the diagonal needs to be continuous and not cross the border of the board to appear again on the other side
        if (get_file(i) == 7){
            break;
        }
        if (bitboards[BISHOP_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[QUEEN_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[BISHOP_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[QUEEN_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[WHITE_PIECES] & (1ULL << i) || bitboards[BLACK_PIECES] & (1ULL << i)){
            break;
        }
    }
    // from the bottom left to the top right (case_index + 9 increments)
    for (int i = case_index + 9; i < NUMBER_SQUARES; i += 9){
        // the diagonal needs to be continuous and not cross the border of the board to appear again on the other side
        if (get_file(i) == 0){
            break;
        }
        if (bitboards[BISHOP_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[QUEEN_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[BISHOP_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[QUEEN_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[WHITE_PIECES] & (1ULL << i) || bitboards[BLACK_PIECES] & (1ULL << i)){
            break;
        }
    }
    // from the bottom right to the top left (case_index + 7 increments)
    for (int i = case_index + 7; i < NUMBER_SQUARES; i += 7){
        // the diagonal needs to be continuous and not cross the border of the board to appear again on the other side
        if (get_file(i) == 7){
            break;
        }
        if (bitboards[BISHOP_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[QUEEN_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[BISHOP_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[QUEEN_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[WHITE_PIECES] & (1ULL << i) || bitboards[BLACK_PIECES] & (1ULL << i)){
            break;
        }
    }


    // looking for a rook or a queen that can threaten the case (straight)
    // from the top to the bottom (case_index + 8 increments)
    for (int i = case_index + 8; i < NUMBER_SQUARES; i += 8){
        if (bitboards[ROOK_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[QUEEN_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[ROOK_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[QUEEN_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[WHITE_PIECES] & (1ULL << i) || bitboards[BLACK_PIECES] & (1ULL << i)){
            break;
        }
    }
    // from the bottom to the top (case_index - 8 increments)
    for (int i = case_index - 8; i >= 0; i -= 8){
        if (bitboards[ROOK_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[QUEEN_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[ROOK_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[QUEEN_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[WHITE_PIECES] & (1ULL << i) || bitboards[BLACK_PIECES] & (1ULL << i)){
            break;
        }
    }
    // from the left to the right (case_index + 1 increments)
    for (int i = case_index + 1; i < NUMBER_SQUARES; i += 1){
        // if we reach the right border of the board
        if (get_file(i) == 0){
            break;
        }
        if (bitboards[ROOK_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[QUEEN_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[ROOK_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[QUEEN_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[WHITE_PIECES] & (1ULL << i) || bitboards[BLACK_PIECES] & (1ULL << i)){
            break;
        }
    }
    // from the right to the left (case_index - 1 increments)
    for (int i = case_index - 1; i >= 0; i -= 1){
        // if we reach the left border of the board
        if (get_file(i) == 7){
            break;
        }
        if (bitboards[ROOK_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[QUEEN_WHITE] & (1ULL << i) && color == BLACK){
            return 1;
        }
        if (bitboards[ROOK_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[QUEEN_BLACK] & (1ULL << i) && color == WHITE){
            return 1;
        }
        if (bitboards[WHITE_PIECES] & (1ULL << i) || bitboards[BLACK_PIECES] & (1ULL << i)){
            break;
        }
    }
    

    // default, if the case_index is not threatened
    return 0;
}


int is_check(int color, bit_board* bitboards, int nb_bitboard, Log* log){

    // get the index of the king
    int king_index = get_king_index(bitboards, color);

    // check if the king is threatened
    if (is_case_threatened(color, king_index, bitboards, nb_bitboard, log)){
        return CHECK;
    }
    return NO_CHECK;
}


bool is_castle_possible(int color, bit_board* bitboards, int nb_bitboard, int from, int to, Log* log){

    // returning 0 if the starting square is not the king (to avoid having to calculate the is case threatened function that is heavy)
    if (color == WHITE && !(bitboards[KING_WHITE] & (1ULL << from))){
        return false;
    }
    if (color == BLACK && !(bitboards[KING_BLACK] & (1ULL << from))){
        return false;
    }

    // for the white player
    if (color == WHITE){

        // check if the king is moving two squares to the right for a short castle
        if (from == 4 && to == 6){
            
            // first we need to check in the log if all the parameters for this castle are false
            if (is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, White_King_Moved_Flag) || is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, White_Rook_H_Moved_Flag)){
                return false;
            }
            // check if the rook is at the right place
            if (!(bitboards[ROOK_WHITE] & (1ULL << 7))){
                return false;
            }
            // check if the squares between the king and the rook are empty
            // if a white piece is on the squares 5 or 6, the castle is not possible
            if (bitboards[WHITE_PIECES] & (1ULL << 5) || bitboards[WHITE_PIECES] & (1ULL << 6)){
                return false;
            }
            // if a black piece is on the squares 5 or 6, the castle is not possible
            if (bitboards[BLACK_PIECES] & (1ULL << 5) || bitboards[BLACK_PIECES] & (1ULL << 6)){
                return false;
            }
            // check if the squares between the king and the rook are not threatened, but the king need also not to be threatened
            if (is_case_threatened(WHITE, 4, bitboards, nb_bitboard, log)){
                return false;
            }
            if (is_case_threatened(WHITE, 5, bitboards, nb_bitboard, log)){
                return false;
            }
            if (is_case_threatened(WHITE, 6, bitboards, nb_bitboard, log)){
                return false;
            }
            // if all the conditions are met, the castle is possible
            return true;
        }

        // check if the king is moving two squares to the left for a long castle
        if (from == 4 && to == 2){

            // first we need to check in the log if all the parameters for this castle are false
            if (is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, White_King_Moved_Flag) || is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, White_Rook_A_Moved_Flag)){
                return false;
            }
            // check if the rook is at the right place
            if (!(bitboards[ROOK_WHITE] & (1ULL << 0))){
                return false;
            }
            // check if the squares between the king and the rook are empty
            // if a white piece is on the squares 1 or 2 or 3, the castle is not possible
            if (bitboards[WHITE_PIECES] & (1ULL << 3) || bitboards[WHITE_PIECES] & (1ULL << 2) || bitboards[WHITE_PIECES] & (1ULL << 1)){
                return false;
            }
            // if a black piece is on the squares 1 or 2 or 3, the castle is not possible
            if (bitboards[BLACK_PIECES] & (1ULL << 3) || bitboards[BLACK_PIECES] & (1ULL << 2) || bitboards[BLACK_PIECES] & (1ULL << 1)){
                return false;
            }
            // check if the squares between the king and the rook are not threatened, but the king need also not to be threatened
            if (is_case_threatened(WHITE, 4, bitboards, nb_bitboard, log)){
                return false;
            }
            if (is_case_threatened(WHITE, 3, bitboards, nb_bitboard, log)){
                return false;
            }
            if (is_case_threatened(WHITE, 2, bitboards, nb_bitboard, log)){
                return false;
            }
            // if all the conditions are met, the castle is possible
            return true;
        }

    }
    // for the black player
    else if (color == BLACK){
        
        // check if the king is moving two squares to the right for a short castle
        if (from == 60 && to == 62){

            // first we need to check in the log if all the parameters for this castle are false
            if (is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, Black_King_Moved_Flag) || is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, Black_Rook_H_Moved_Flag)){
                return false;
            }
            // check if the rook is at the right place
            if (!(bitboards[ROOK_BLACK] & (1ULL << 63))){
                return false;
            }
            // check if the squares between the king and the rook are empty
            // if a black piece is on the squares 61 or 62, the castle is not possible
            if (bitboards[BLACK_PIECES] & (1ULL << 61) || bitboards[BLACK_PIECES] & (1ULL << 62)){
                return false;
            }
            // if a white piece is on the squares 61 or 62, the castle is not possible
            if (bitboards[WHITE_PIECES] & (1ULL << 61) || bitboards[WHITE_PIECES] & (1ULL << 62)){
                return false;
            }
            // check if the squares between the king and the rook are not threatened, but the king need also not to be threatened
            if (is_case_threatened(BLACK, 60, bitboards, nb_bitboard, log)){
                return false;
            }
            if (is_case_threatened(BLACK, 61, bitboards, nb_bitboard, log)){
                return false;
            }
            if (is_case_threatened(BLACK, 62, bitboards, nb_bitboard, log)){
                return false;
            }
            // if all the conditions are met, the castle is possible
            return true;
        }

        // check if the king is moving two squares to the left for a long castle
        if (from == 60 && to == 58){

            // first we need to check in the log if all the parameters for this castle are false
            if (is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, Black_King_Moved_Flag) || is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, Black_Rook_A_Moved_Flag)){
                return false;
            }
            // check if the rook is at the right place
            if (!(bitboards[ROOK_BLACK] & (1ULL << 56))){
                return false;
            }
            // check if the squares between the king and the rook are empty
            // if a black piece is on the squares 59 or 58, the castle is not possible
            if (bitboards[BLACK_PIECES] & (1ULL << 59) || bitboards[BLACK_PIECES] & (1ULL << 58) || bitboards[BLACK_PIECES] & (1ULL << 57)){
                return false;
            }
            // if a white piece is on the squares 59 or 58, the castle is not possible
            // check if the squares between the king and the rook are not threatened, but the king need also not to be threatened
            if (is_case_threatened(BLACK, 60, bitboards, nb_bitboard, log)){
                return false;
            }
            if (is_case_threatened(BLACK, 59, bitboards, nb_bitboard, log)){
                return false;
            }
            if (is_case_threatened(BLACK, 58, bitboards, nb_bitboard, log)){
                return false;
            }
            // if all the conditions are met, the castle is possible
            return true;
        }

    }

    // default, if the castle is not possible
    return false;
}


bool is_promotion_possible(int color, bit_board* bitboards, int nb_bitboard, int from, int to){
    
    // for the white player
    if (color == WHITE){
        // check if the pawn is at the last rank (we need to verify if it's really a pawn at the from index)
        if (get_rank(from) == 6 && get_rank(to) == 7 && (bitboards[PAWN_WHITE] & (1ULL << from))){
            return true;
        }
    }
    // for the black player
    else if (color == BLACK){
        // check if the pawn is at the last rank (we need to verify if it's really a pawn at the from index)
        if (get_rank(from) == 1 && get_rank(to) == 0 && (bitboards[PAWN_BLACK] & (1ULL << from))){
            return true;
        }
    }

    // default, if the promotion is not possible
    return false;
}


bool is_en_passant_possible(int color, bit_board* bitboards, int nb_bitboard, int from, int to, Log* log){
    
    // check if the log is not empty
    if (log->actual_size == 0){
        return false;
    }

    // it need to be a pawn at the from index
    if (color == WHITE && !(bitboards[PAWN_WHITE] & (1ULL << from))){
        return false;
    }
    if (color == BLACK && !(bitboards[PAWN_BLACK] & (1ULL << from))){
        return false;
    }

    // for an en passant to be possible, the last move must be a pawn moving two squares
    if (get_flag(log->moves[log->actual_size-1]->move_value) == Pawn_Two_Up_Flag){

        // for the white player, the pawn must be at the right rank (the fifth, index 4)
        if (color == WHITE && get_rank(from) == 4 && get_rank(to) == 5){
            
            // if we go left to make the en passant, the previous to_index must be the left of this move from_index
            if (get_file(to) == get_file(from) - 1 && get_to_square(log->moves[log->actual_size-1]->move_value) == from - 1 && from - 1 >= 0){
                return true;
            }

            // if we go right to make the en passant
            else if (get_file(to) == get_file(from) + 1 && get_to_square(log->moves[log->actual_size-1]->move_value) == from + 1 && from + 1 < NUMBER_SQUARES){
                return true;
            }

        }
        
        // for the black player, the pawn must be at the right rank (the fourth, index 3)
        else if (color == BLACK && get_rank(from) == 3 && get_rank(to) == 2){
            
            // if we go left to make the en passant, the previous to_index must be the left of this move from_index
            if (get_file(to) == get_file(from) - 1 && get_to_square(log->moves[log->actual_size-1]->move_value) == from - 1 && from - 1 >= 0){
                return true;
            }

            // if we go right to make the en passant
            else if (get_file(to) == get_file(from) + 1 && get_to_square(log->moves[log->actual_size-1]->move_value) == from + 1 && from + 1 < NUMBER_SQUARES){
                return true;
            }

        }
    
    }

    // default, if the en passant is not possible
    return false;
}


bool has_pawn_moved_two_squares(int color, bit_board* bitboards, int nb_bitboard, int from, int to){
    
    // for the white player
    if (color == WHITE && bitboards[PAWN_WHITE] & (1ULL << from)){
        // check if the pawn is at the right rank (the second, index 1)
        if (get_rank(from) == 1 && get_rank(to) == 3){
            return true;
        }
    }
    // for the black player
    else if (color == BLACK && bitboards[PAWN_BLACK] & (1ULL << from)){
        // check if the pawn is at the right rank (the seventh, index 6)
        if (get_rank(from) == 6 && get_rank(to) == 4){
            return true;
        }
    }

    // default, if the pawn has not moved two squares
    return false;

}


bool will_capture(int color, bit_board* bitboards, int nb_bitboard, int to){

    // if the color is white, we search if the "to" position is occupied by a black piece
    if (color == WHITE){
        if (bitboards[BLACK_PIECES] & (1ULL << to)){
            return true;
        }
    }
    // if the color is black, we search if the "to" position is occupied by a white piece
    else if (color == BLACK){
        if (bitboards[WHITE_PIECES] & (1ULL << to)){
            return true;
        }
    }

    // if the "to" position is not occupied by a piece of the opposite color, we return false
    return false;

}


int get_type_of_piece(bit_board* bitboards, int nb_bitboard, int position_index){

    for (int i = 0; i < nb_bitboard; i++){
        if (bitboards[i] & (1ULL << position_index) && i != WHITE_PIECES && i != BLACK_PIECES){
            return i;
        }
    }

    // if the position is empty, we return NOTHING
    return NOTHING;

}

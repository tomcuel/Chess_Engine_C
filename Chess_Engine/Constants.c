#include "Constants.h"


// Masks
const move start_square_mask = 0b0000000000111111;
const move target_square_mask = 0b0000111111000000;
const move flag_mask = 0b1111000000000000;
// Flags
const int No_Flag = 0b0000;
const int En_Passant_Flag = 0b0001;
const int Castle_Flag = 0b0010;
const int Pawn_Two_Up_Flag = 0b0011;
const int Promote_To_Queen_Flag = 0b0100;
const int Promote_To_Knight_Flag = 0b0101;
const int Promote_To_Rook_Flag = 0b0110;
const int Promote_To_Bishop_Flag = 0b0111;
// Castling rights flags
const castling_rights_flags White_King_Moved_Flag = 0b000001;
const castling_rights_flags White_Rook_A_Moved_Flag = 0b000010;
const castling_rights_flags White_Rook_H_Moved_Flag = 0b000100;
const castling_rights_flags Black_King_Moved_Flag = 0b001000;
const castling_rights_flags Black_Rook_A_Moved_Flag = 0b010000;
const castling_rights_flags Black_Rook_H_Moved_Flag = 0b100000;

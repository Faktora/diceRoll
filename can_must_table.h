// Created by Nedelin Todorov on 28-Feb-20.

#include <stdbool.h>

#ifndef POKERDICE_CAN_MUST_TABLE_H
#define POKERDICE_CAN_MUST_TABLE_H


//this function will be used in can must game mode
//this function will only write to the table once per row per round
void can_must_pt_one(int points_pt_one[][2], int round_counter, bool has_rerolled, int game_mode);

#endif //POKERDICE_CAN_MUST_TABLE_H

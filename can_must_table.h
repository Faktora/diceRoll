// Created by Nedelin Todorov on 26-Feb-20.

#include <stdbool.h>

/**
 * \file can_must_table.h
 * \brief second part of the 3rd game mode called "Can Must"
 * */

#ifndef POKERDICE_CAN_MUST_TABLE_H
#define POKERDICE_CAN_MUST_TABLE_H

/** \fn void can_must_pt_two(int round_counter, int points_array[][2])
 * \brief 2nd part of the 3rd game mode (MUST)
 * \param round_counter - storing the rounds, used for the rules of the mode
 * \param points_array - stores each player's points in his own column
 * */
void can_must_pt_two(int round_counter, int points_array[][2]);

#endif //POKERDICE_CAN_MUST_TABLE_H

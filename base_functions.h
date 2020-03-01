// Created by Nedelin Todorov on 26-Feb-20.

#include <stdbool.h>
#include "pyramid.h"

/**
 * \file base_functions.h
 * \brief the basic game functions
 * */

#ifndef POKERDICE_BASE_FUNCTIONS_H
#define POKERDICE_BASE_FUNCTIONS_H


/** \fn void roll_dice(int keep, int *array_keep)
 * \brief a basic function that rolls or if desired re-rolls players unwanted dice
 * \param array_keep -
 * pointer array with dices, the chosen ones are saved, rest gets re-rolled
 * \param keep -
 * amount of dice that the player wants to keep
 * */
void roll_dice(int keep, const int *array_keep);

/** \fn void translate(const int array[])
 * \brief basic printing function for player throws
 * \param array -
 * array with current player throws
 * */
void translate(const int array[]);

/** \fn bool keep_dice(int keep, int *amount_of_rolls, bool *has_rerolled)
 * \brief follows if the player is allowed to re-roll anymore
 * \param keep - int used to store amount of dices to save
 * \param amount_of_rolls - pointer to int that stores how many rolls did the player
 * \param has_rerolled - true if the player has re-rolled, which results in fewer points from special rolls
 * */
bool keep_dice(int keep, int *amount_of_rolls, bool *has_rerolled);

/** \fn bool calculate_points(bool *has_rerolled)
 * \brief basic calculating function
 * \param has_rerolled - true if the player has re-rolled, which results in fewer points from special rolls
 * */
bool calculate_points(const bool *has_rerolled);

/** \fn bool is_game_finished(int game_mode, bool *has_rerolled, int array_points[][2])
 * \brief main game function that ends the game when a requirement is met
 * \param game_mode - user's choice of game mode to play
 * \param has_rerolled - true if the player has re-rolled, which results in fewer points from special rolls; used for function call
 * \param array_points - two dimensional array saving each player's points in it's own column
 * \param single_throws - stores current player and round dice throws by type
 * */
bool is_game_finished(int game_mode, bool *has_rerolled, int array_points[][2], int round_counter, struct pyramid *pyra);

/** \fn int next_free(const int* array_to_find_free_position, int array_len)
 * \brief Finds next free position to indicate safe writing of values
 * \param array_to_find_free_position - pointer to array to find free position in
 * \param array_len - length of array to safely iterate through array
 * */
int next_free(const int* array_to_find_free_position, int array_len);

#endif //POKERDICE_BASE_FUNCTIONS_H

// Created by Nedelin Todorov on 26-Feb-20.

#include <stdbool.h>

/** \file point_computing.h
 *  \brief here are all special throw function prototypes
 * */


#ifndef POKERDICE_POINT_COMPUTING_H
#define POKERDICE_POINT_COMPUTING_H

/** \fn bool is_consecutive(int player_throws[], int array_throws_length)
 * \brief takes array with player's throws returns true if elements are consecutive, false otherwise;
 * getting help from is_min and is_max to find it (aka straight)
 * \param array_throws_length -
 * defines the length of the array
 * \param player_throws -
 * array that stores player's throws
 * */
bool is_consecutive(int player_throws[], int array_throws_length);

/** \fn int is_min(const int player_throws[], int array_throws_length)
 * \brief searches the array with player throws for the min element in it
 * \param array_throws_length -
 * defines the length of the array
 * \param player_throws -
 * array that stores player's throws
 * */
int is_min(const int player_throws[], int array_throws_length);

/** \fn int is_max(const int player_throws[], int array_throws_length)
 * \brief searches the array with player throws for the max element in it
 * \param array_throws_length -
 * defines the length of the array
 * \param player_throws -
 * array that stores player's throws
 * */
int is_max(const int player_throws[], int array_throws_length);

/** \fn bool is_fullhouse()
 * \brief takes a sorted player's throws array from is_highest and returns true if three and two of a
 * kind are found in player's throw array, false otherwise
 * */
bool is_fullhouse();

/** \fn bool is_grande(const int grande_array[], int array_length)
 * \brief checks the player's throw array if all dices are Aces
 * \param grande_array -
 * stored player throws from the round
 * \param array_length -
 * int showing the length of the array
 * */
bool is_grande(const int grande_array[], int array_length);

/** \fn bool is_poker()
 * \brief takes the sorted player's throws array and returns true if there are four of a kind, false otherwise
 * */
bool is_poker();

/** \fn void is_highest()
 * \brief takes the array as argument and sorts it by power
 * */
void is_highest();


#endif //POKERDICE_POINT_COMPUTING_H

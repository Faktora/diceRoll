// Created by Nedelin Todorov on 26-Feb-20.

#include <stdbool.h>

/// \file point_computing.h
///
/// \brief functions that are checking players rolls for special combinations
///


#ifndef POKERDICE_POINT_COMPUTING_H
#define POKERDICE_POINT_COMPUTING_H

/*func takes array with player_throws and the length of it
 * calls the is_max and is_min (check their comments for explanation)
 * after getting the min and max goes thru player_throws to find if all numbers are consecutive*/

/// \fn is_consecutive
/// takes array with player's throws returns true if elements are consecutive, false otherwise;
/// getting help from is_min and is_max to find it (aka straight)
bool is_consecutive(int player_throws[], int array_throws_length);

/* helping functions for is_consecutive, they find the min and max number in the array player_throws */


/// \param is_min
/// searches the array with player throws for the min element in it
int is_min(const int player_throws[], int array_throws_length);

//finds the min element in the array
/// is_max
/// searches the array with player throws for the max element in it
///
int is_max(const int player_throws[], int array_throws_length);

//finds the max element in the array

/*func with no arguments, gets called by is_highest to check if there is full house in the current throw*/

/// \fn is_fullhouse
/// takes a sorted player's throws array from is_highest and returns true if three and two of a
/// kind are found in player's throw array, false otherwise
bool is_fullhouse();

/*takes the array with player throws and the length of it as arguments
 * then goes thru the array looking if all the elements are == 5 (Aces)*/

/// \fn is_grande
/// checks the player's throw array if all dices are Aces
bool is_grande(const int grande_array[], int array_length);


/*func with no arguments, gets called by is_highest to check if there is poker in the current throw*/

/// \fn is_poker
/// takes the sorted player's throws array and returns true if there are four of a kind, false otherwise
bool is_poker();


/*takes the array and sorts it by power in search for poker and full house*/

/// \fn is_highest
/// takes the array as argument and sorts it by power
void is_highest();


#endif //POKERDICE_POINT_COMPUTING_H

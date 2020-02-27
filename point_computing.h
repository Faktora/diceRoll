//
// Created by Faktora on 26-Feb-20.
//
#include <stdbool.h>

/// \brief functions that are checking players rolls for special combinations
/// \param is_consecutive - takes array with player throws returns true if elements are consecutive, false otherwise;
/// getting help from is_min and is_max to find it (aka straight)
/// \param is_min - searches the array with player throws for the min element in it
/// \param is_max - searches the array with player throws for the max element in it
/// \param if_fullhouse - takes a sorted player throws array from is_highest and returns true if three and two of a
/// kind are found in players throw array, false otherwise
/// \param is_poker - takes the sorted player thhrows array and returns true if there are four of a kind, false otherwise
/// \param is_grande - checks the player throw array if all dices are Aces
/// \param is_highest - takes the array as argument and sorts it by power

#ifndef POKERDICE_POINT_COMPUTING_H
#define POKERDICE_POINT_COMPUTING_H

/*func takes array with player_throws and the length of it
 * calls the is_max and is_min (check their comments for explanation)
 * after getting the min and max goes thru player_throws to find if all numbers are consecutive*/
bool is_consecutive(int player_throws[], int array_throws_length);

/* helping functions for is_consecutive, they find the min and max number in the array player_throws */
int is_min(const int player_throws[], int array_throws_length);//finds the min element in the array
int is_max(const int player_throws[], int array_throws_length);//finds the max element in the array

/*func with no arguments, gets called by is_highest to check if there is full house in the current throw*/
bool is_fullhouse();

/*takes the array with player throws and the length of it as arguments
 * then goes thru the array looking if all the elements are == 5 (Aces)*/
bool is_grande(const int grande_array[], int array_length);

/*func with no arguments, gets called by is_highest to check if there is poker in the current throw*/
bool is_poker();

/*takes the array and sorts it by power in search for poker and full house*/
void is_highest(const int array[]);


#endif //POKERDICE_POINT_COMPUTING_H

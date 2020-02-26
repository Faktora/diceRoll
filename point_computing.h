//
// Created by Faktora on 26-Feb-20.
//
#include <stdbool.h>

#ifndef POKERDICE_POINT_COMPUTING_H
#define POKERDICE_POINT_COMPUTING_H

/*func takes array with player_throws and the length of it
 * calls the is_max and is_min (check their comments for explanation)
 * after getting the min and max goes thru player_throws to find if all numbers are consecutive*/
bool is_consecutive(int player_throws[], int array_throws_length);

/* helping functions for is_consecutive, they find the min and max number in the array player_throws */
int is_min(const int player_throws[], int array_throws_length);//finds the min element in the array
int is_max(const int player_throws[], int array_throws_length);//finds the max element in the array

/*takes the array with player throws and the length of it as arguments
 * then goes thru the array looking if all the elements are == 5 (Aces)*/
bool is_grande(const int grande_array[], int array_length);

/*func with no arguments, gets called by is_highest to check if there is poker in the current throw*/
bool is_poker();

/*func with no arguments, gets called by is_highest to check if there is full house in the current throw*/
bool is_fullhouse();

/*takes the array and sorts it by power in search for poker and full house*/
void is_highest(const int array[]);


#endif //POKERDICE_POINT_COMPUTING_H

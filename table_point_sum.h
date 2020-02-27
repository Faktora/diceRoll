//
// Created by Faktora on 27-Feb-20.
//

/// \file table_point_sum.h
/// \brief Function for game mode: 2. Table Point Summary. Saves and prints out data
///
/// \param table_point_summary - takes 2 dimensional array as argument, it saves each players point's in their own column
/// and after the player's turn is over, the table is being printed
///

#ifndef POKERDICE_TABLE_POINT_SUM_H
#define POKERDICE_TABLE_POINT_SUM_H

void table_point_summary(int array_points[][2]);

void table_point_scoring(int array_points[][2], bool has_rerolled);

/*array_points[12][2] = {{0,                0},  //9s       position 0
                        {0,                0},  //10s           position 1
                        {0,                0},  //Jacks         position 2
                        {0,                0},  //Queens        position 3
                        {0,                0},  //Kings         position 4
                        {0,                0},  //Aces          position 5
                        {0,                0},  //Straight      position 6
                        {0,                0},  //Full House    position 7
                        {0,                0},  //Poker         position 8
                        {0,                0},  //Grande        position 9
                        {0,                0}}; //Sum           position 10
     */

#endif //POKERDICE_TABLE_POINT_SUM_H

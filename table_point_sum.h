// Created by Nedelin Todorov on 26-Feb-20.

/** \file table_point_sum.h
 * \brief Function for second game mode: Table point summary
 * */

#ifndef POKERDICE_TABLE_POINT_SUM_H
#define POKERDICE_TABLE_POINT_SUM_H

/** \fn void table_point_summary(int array_points[][2])
 * \brief prints the static part of the table
 *  \param array_points -
 *  stores each player's score in his own column
 * */
void table_point_summary(int array_points[][2]);

/** \fn void table_point_scoring(int array_points[][2], bool has_rerolled)
 * \brief the backbone of the 2nd game mode, calculate each player's points, then saves them in the respective column
 * \param array_points -
 * stores each player's score in his own column
 * \param has_rerolled -
 * used in points calculating, checks if the player did special roll on first throw or not
 * */
void table_point_scoring(int array_points[][2], bool has_rerolled, int game_mode);

/** \fn void count_single_throws(int array_single_throws[6])
 * \brief function that sums the type and amount if dice that are thrown
 * \param array_single_throws - array in which they are saved; gets overridden³
 */
void count_single_throws(int array_single_throws[6]);

void save_singles_table(int points_array[][2], const int single_throws[], bool already_saved, int game_mode);

bool save_special(int points_array[][2], int game_mode, int row);

int* gather_counts();


#endif //POKERDICE_TABLE_POINT_SUM_H

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
 * \param game_mode - stores player's choice of game mode to play
 * */
void table_point_scoring(int array_points[][2], bool has_rerolled, int game_mode);

/** \fn void count_single_throws(int array_single_throws[6])
 * \brief function that sums the type and amount if dice that are thrown
 * \param array_single_throws - array in which they are saved; gets overridden³
 * */
//void count_single_throws(int array_single_throws[6]);

/** \fn void save_singles_table(int points_array[][2], const int single_throws[], bool already_saved, int game_mode)
 * \brief saves a singly type of dice, when no special combos are available
 * \param points_array - stores each player's points in his own column
 * \param single_throws - array storing the amounts of single type dices
 * \param already_saved - saves if the player saved already or not
 * \param game_mode - stores player's choice of game mode to play, passed to other functions for calculating
 * */
void save_singles_table(int points_array[][2], const int single_throws[], bool already_saved, int game_mode);

/** \fn bool save_special(int points_array[][2], int game_mode, int row)
 * \brief function that saves a special throw if the player made one
 * \param points_array - stores each player's points in his own column
 * \param game_mode - stores the player's choice of game mode to play, passed to other functions for calculating
 * \param row - used to point to the desired row that the current player wants to save to
 * */
bool save_special(int points_array[][2], int game_mode, int row);

/** \fn int* gather_counts()
 * \brief counts and saves the amount of each individual dice that the current player threw that round, stores it
 * in array for other functions to use it
 * */
int* gather_counts();


#endif //POKERDICE_TABLE_POINT_SUM_H

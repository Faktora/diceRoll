// Created by Nedelin Todorov on 26-Feb-20.

/** \file table_point_sum.h
 * \brief Function for second game mode: Table point summary
 * */

#ifndef POKERDICE_TABLE_POINT_SUM_H
#define POKERDICE_TABLE_POINT_SUM_H

/** \fn table_point_summary
 * \brief prints the static part of the table
 *  \param array_points -
 *  stores each player's score in his own column
 * */
void table_point_summary(int array_points[][2]);

/** \fn table_point_scoring
 * \brief the backbone of the 2nd game mode, calculate each player's points, then saves them in the respective column
 * \param array_points -
 * stores each player's score in his own column
 * \param has_rerolled -
 * used in points calculating, checks if the player did special roll on first throw or not
 * */
void table_point_scoring(int array_points[][2], bool has_rerolled);

#endif //POKERDICE_TABLE_POINT_SUM_H

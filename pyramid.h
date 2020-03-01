// Created by Nedelin Todorov on 26-Feb-20.

#ifndef POKERDICE_PYRAMID_H
#define POKERDICE_PYRAMID_H


//grande[number of saves][number of players]

struct pyramid {
    int grande[2][1];
    int poker[2][2];
    int full_house[2][3];
    int straight[2][4];
    int aces[2][5];
    int kings[2][6];
    int queens[2][7];
    int jacks[2][8];
    int tens[2][9];
    int nines[2][10];

};

/** \fn struct pyramid initialise_pyramid()
 * \brief returns an empty pyramid
 * */
struct pyramid initialise_pyramid();

/** \fn void write_to_pyramid(struct pyramid *pyra)
 * \brief Asks players on which values to save to pyramid
 * \param *pyra pointer to pyramid
 * */
void write_to_pyramid(struct pyramid *pyra);

/** \fn void print_pyramid(struct pyramid *pyra)
 * \brief Prints pyramid
 * \param *pyra pointer to pyramid
 * */
void print_pyramid(struct pyramid *pyra);

/** \fn bool check_pyramid(struct pyramid *pyra, int current_player)
 * \brief Checks if current player has completed pyramid
 * \param *pyra pointer to pyramid
 * */
bool check_pyramid(struct pyramid *pyra);

#endif //POKERDICE_PYRAMID_H

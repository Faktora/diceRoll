// Created by Nedelin Todorov on 26-Feb-20.

#ifndef POKERDICE_PYRAMID_H
#define POKERDICE_PYRAMID_H


//grande[number of saves][number of players]

struct pyramid {
    int grande[1][2];
    int poker[2][2];
    int full_house[3][2];
    int straight[4][2];
    int aces[5][2];
    int kings[6][2];
    int queens[7][2];
    int jacks[8][2];
    int tens[9][2];
    int nines[10][2];

};

#endif //POKERDICE_PYRAMID_H

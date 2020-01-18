#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "function.h"

#define LENGTH 5

int player_throws[2][LENGTH];
int playerPoints[2];
int currentPlayer = 1;


void is_highest(const int array[]);

//printing func so it does not just spit the numbers from the array
void translate(const int array[]);

//this should be the func to save dice, rest of the dice should be rerolled (max 3 times)
//if the player saves all, then his turn must end (later on)
//boolean so it can keep track of numbers of rolls
bool keepDice(int keep, int *rollsAmount);

void get_points();

/* is_consecutive's little helpers */
int is_min(const int playerThrows[], int arrayThrowsLength);//finds the min element in the array
int is_max(const int playerThrows[], int arrayThrowsLength);//finds the max element in the array
/* returns true if all array elements are consecutive
 * returns false if the array elements are not consecutive*/
bool is_consecutive(int playerThrows[], int arrayThrowsLength);
/*checks if all array elements are Aces or not*/
bool is_grande(const int isGrande[], int arrayLength);

bool is_game_finished(int gameChoice);

bool is_poker();

bool is_fullhouse();

int main() {
    srand((unsigned int) time(NULL));// starting here for more randomness
    int numToKeep = 0;// takes users choice on which dice to keep, rest is getting rerolled!!!
    int rollsMade = 0;
    int userGameChoice = 0;
    bool gameFinished = false;
    int roundCounter = 1;

    printf(" *** GAME MODES ***\n1) Normal point summary (100points)\n2) Table point summary\n");
    printf("\n");
    scanf("%d", &userGameChoice);

    while (!gameFinished) {
        if (currentPlayer == 0) {
            currentPlayer = 1;
        } else {
            printf("Round %d ", roundCounter);
            currentPlayer = 0;
        }
        printf("Player %d rolls now! Good luck!\n", currentPlayer + 1);
        setbuf(stdout, 0);
        bool isTurnEnded = false;
        while (!isTurnEnded) {
            isTurnEnded = keepDice(numToKeep, &rollsMade);
        }

        gameFinished = is_game_finished(userGameChoice);
        setbuf(stdout, 0);
        printf("\n");

    }
    printf("Player %d wins with: %d points!\n", currentPlayer + 1, playerPoints[currentPlayer]);
    return 0;
}

void translate(const int array[]) {
    //going through the array taking each element and then putting it in the switch machine for proper print
    for (int i = 0; i < LENGTH; i++) {
        //later on i can dump the tmp and just stay with:   switch(array[i])
        if (array[i] == 0) {
            setbuf(stdout, 0);
            printf("%-7d", 9);
        } else if (array[i] == 1) {
            setbuf(stdout, 0);
            printf("%-7d", 10);
        } else if (array[i] == 2) {
            setbuf(stdout, 0);
            printf("%-7s", "Jack");
        } else if (array[i] == 3) {
            setbuf(stdout, 0);
            printf("%-7s", "Queen");
        } else if (array[i] == 4) {
            setbuf(stdout, 0);
            printf("%-7s", "King");
        } else if (array[i] == 5) {
            setbuf(stdout, 0);
            printf("%-7s", "Ace");
        }
    }
    setbuf(stdout, 0);
    printf("\n");//beauty print
}

bool keepDice(int keep, int *rollsAmount) {
    int currDice;
    *rollsAmount += 1;
    if (*rollsAmount == 4) {
        *rollsAmount = 0;
        return true;
    } else {
        // search
        if (*rollsAmount != 1) {
            setbuf(stdout, 0);
            printf("\nHow many dice to save?\n");
            scanf("%d", &keep);
        }
        if (keep == 5) { //if no "if" here => player must do 5 inputs on which to save
            *rollsAmount = 0;
            return true;
        } else {
            int arrayKeep[keep];
            for (int k = 0; k < keep; k++) {
                setbuf(stdout, 0);
                printf("\nWhich one to keep?\n");
                scanf("%d", &currDice);
                arrayKeep[k] = currDice;
            }
            for (int j = 0; j < 5; j++) {//
                bool isKeep = false;
                for (int i = 0; i < keep; i++) {
                    if (arrayKeep[i] == j) {
                        isKeep = true;
                    }
                }
                if (!isKeep) {
                    player_throws[currentPlayer][j] = j + 1;// rand() % 6; to make them shuffle again
                }
            }
        }
        translate(player_throws[currentPlayer]);
        return false;
    }
}

void get_points(const int *rollsAmount) {
    int tempSum = 0;
    bool pointSumationEnded = false;

    //need to implement if else statement to check if some of the special hands are made on 1st throw
    /*if (rollsMade == 1) more points else fewer points*/
    if (is_consecutive(player_throws[currentPlayer],
                       LENGTH)) { // Straight from 9 to King or from 10 to Ace forward and backwards
        (*rollsAmount == 1) ? (tempSum += 25) : (tempSum += 20);
        //tempSum += 20; // still scoring 20points/dice even if not consecutive
        pointSumationEnded = true;
    } else if (is_grande(player_throws[currentPlayer], LENGTH)) { // Works only with 5x Ace
        (*rollsAmount == 1) ? (tempSum += 80) : (tempSum += 50);
        //tempSum += 50;
        pointSumationEnded = true;
    } else if (is_fullhouse(player_throws[currentPlayer])) {
        (*rollsAmount == 1) ? (tempSum += 35) : (tempSum += 30);
        //tempSum += 30;
        pointSumationEnded = true;
    } else if (is_poker(player_throws[currentPlayer])) {
        (*rollsAmount == 1) ? (tempSum += 45) : (tempSum += 40);
        //tempSum += 40;
        pointSumationEnded = true;
    }

    if (!pointSumationEnded) {
        for (int i = 0; i < LENGTH; i++) {
            // it resets on each and every re-roll
            if (player_throws[currentPlayer][i] == 0) { // 9
                tempSum += 1;
            } else if (player_throws[currentPlayer][i] == 1) { // 10
                tempSum += 2;
            } else if (player_throws[currentPlayer][i] == 2) { // Jack
                tempSum += 3;
            } else if (player_throws[currentPlayer][i] == 3) { // Queen
                tempSum += 4;
            } else if (player_throws[currentPlayer][i] == 4) { // King
                tempSum += 5;
            } else if (player_throws[currentPlayer][i] == 5) { // Ace
                tempSum += 6;
            }
        }
    }

    playerPoints[currentPlayer] += tempSum;

    printf("Player %d made: %d points this round and total: %d points!\n", currentPlayer + 1,
           tempSum, playerPoints[currentPlayer]);
    /*when player1 wins displays: player 1 won points: 0
     *when player2 wins display: player 0 won points: x amount*/
    //printf("Player %d got: %d points so far.\n", currentPlayer + 1, playerPoints[currentPlayer]);
}


//finding the smallest element in the array
int is_min(const int playerThrows[], int arrayThrowsLength) {
    int min = playerThrows[0];
    for (int i = 0; i < arrayThrowsLength; i++) {
        if (playerThrows[i] > min) {
            min = playerThrows[i];
        }
    }
    return min;
}

//finding the biggest element in the array
int is_max(const int playerThrows[], int arrayThrowsLength) {
    int max = playerThrows[0];
    for (int i = 0; i < arrayThrowsLength; i++) {
        if (playerThrows[i] < max) {
            max = playerThrows[i];
        }
    }
    return max;
}

bool is_consecutive(int playerThrows[], int arrayThrowsLength) {
    //get the minimum number from the array
    int min = is_min(playerThrows, arrayThrowsLength);

    //get the maximum number from the array
    int max = is_max(playerThrows, arrayThrowsLength);

    //if max - min + 1 == arrayThrowsLength, only then check all elements
    if (max - min + 1 == arrayThrowsLength) {
        int indexOne;
        for (indexOne = 0; indexOne < arrayThrowsLength; indexOne++) {
            int indexTwo;
            if (playerThrows[indexOne] < 0) {
                indexTwo = -playerThrows[indexOne] - min;
            } else {
                indexTwo = playerThrows[indexOne] - min;
            }
            //if the value at indexTwo is negative => there is repetition
            if (playerThrows[indexTwo] > 0) {
                playerThrows[indexTwo] = -playerThrows[indexTwo];
            } else {
                return false;
            }
        }
        //if no negative values are present => the arrays elements are distinct
        return true;
    }
    //if max - min + 1 != n
    return false;
}

bool is_grande(const int isGrande[], int arrayLength) {
    const int checker = 5;
    for (int i = 0; i < arrayLength; i++) {
        if (checker == isGrande[i]) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool is_game_finished(int gameChoice) {
    if (gameChoice == 1) {
        get_points(/*const int *rollsAmount*/);
        (playerPoints[currentPlayer] >= 100) ? (true) : (false);
    } else if (gameChoice == 2) {
        printf("Still under construction sorry!\n ");
        return true;
    }
    /*switch (gameChoice) {
        case 1:
            get_points(const int *rollsAmount);// this motherfucker is fucking up my work now :/
            if (playerPoints[currentPlayer] >= 100) {
                return true;
            }
    }*/
}

bool is_poker() {
    bool firstPossibility, secondPossibility;
    is_highest(player_throws[currentPlayer]);

    firstPossibility =
            player_throws[currentPlayer][0] == player_throws[currentPlayer][1] &&
            player_throws[currentPlayer][1] == player_throws[currentPlayer][2] &&
            player_throws[currentPlayer][2] == player_throws[currentPlayer][3];

    secondPossibility =
            player_throws[currentPlayer][1] == player_throws[currentPlayer][2] &&
            player_throws[currentPlayer][2] == player_throws[currentPlayer][3] &&
            player_throws[currentPlayer][3] == player_throws[currentPlayer][4];

    return (firstPossibility || secondPossibility);
}


bool is_fullhouse() {
    bool firstPossibility, secondPossibility;
    is_highest(player_throws[currentPlayer]);

    firstPossibility =
            player_throws[currentPlayer][0] == player_throws[currentPlayer][1] &&
            player_throws[currentPlayer][1] == player_throws[currentPlayer][2] &&
            player_throws[currentPlayer][3] == player_throws[currentPlayer][4];

    secondPossibility =
            player_throws[currentPlayer][0] == player_throws[currentPlayer][1] &&
            player_throws[currentPlayer][2] == player_throws[currentPlayer][3] &&
            player_throws[currentPlayer][3] == player_throws[currentPlayer][4];

    return (firstPossibility || secondPossibility);
}

//sorting array by power
void is_highest(const int array[]) {
    int i, j, minimum_j;

    for (i = 0; i < LENGTH; i++) {
        // search the array for the minimum element value in the array
        minimum_j = i;   // take that array[i] is the minimum

        for (j = i + 1; j < LENGTH; j++) {
            if (player_throws[currentPlayer][j] < player_throws[currentPlayer][minimum_j]) {
                minimum_j = j;    // found smaller => updating minimum_j with new element
            }
        }
        // swapping the elements around so they can be sorted by power
        int help = player_throws[currentPlayer][i];// temporary value to help with swapping
        player_throws[currentPlayer][i] = player_throws[currentPlayer][minimum_j];
        player_throws[currentPlayer][minimum_j] = help;
    }
}

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "function.h"

#define LENGTH 5

int playerRolls[2][LENGTH];
int playerPoints[2];
bool roundEnd = false;
int currentPlayer = 0;


//printing func so it does not just spit the numbers from the array
void translate(const int array[]);

//this should be the func to save dice, rest of the dice should be rerolled (max 3 times)
//if the player saves all, then his turn must end (later on)
//boolean so it can keep track of numbers of rolls
bool keepDice(int keep, int *rollsAmount);

//implement a pointing system :
/*POINT SUMMARY
 *  9s are 1 point
 *  10s are 2 points
 *  Jacks are 3 points
 *  Queens are 4 points
 *  Kings are 5 points
 *  Aces are 6 points*/
void countPoints();

/* these funcs thelp the main func that
 * checks if the array is consecutive*/
int getMin(const int arr[], int number);//finds the min element in the array
int getMax(const int arr[], int number);//finds the max element in the array
/* returns true if all array elements are consecutive
 * returns false if the array elements are not consecutive*/
bool consecutiveChecker(int arrCons[], int number);
/*checks if all array elements are Aces or not*/
bool grandeChecker(const int isGrande[], int arrayLength);

bool checkGameFinished(int gameChoice);

bool checkPoker(const int arrayPoker[]);

int main() {

    srand((unsigned int) time(NULL));// starting here for more randomness
    int numToKeep = 0;// takes users choice on which dice to keep, rest is getting rerolled!!!
    int rollsMade = 0;
    int userGameChoice = 0;
    bool gameFinished = false;

    printf(" *** GAME MODES ***\n1) Normal point summary (100points)\n2) Table point summary\n");
    printf("\n");
    scanf("%d", &userGameChoice);

    while (!gameFinished) {
        printf("Player %d rolls now! Good luck!\n", currentPlayer + 1);
        //grandeChecker(playerRolls[currentPlayer], LENGTH);
        setbuf(stdout, 0);
        bool isTurnEnded = false;
        while (!isTurnEnded) {
            isTurnEnded = keepDice(numToKeep, &rollsMade);
        }

        gameFinished = checkGameFinished(userGameChoice);
        (currentPlayer == 0) ? (currentPlayer = 1) : (currentPlayer = 0);
        setbuf(stdout, 0);
        printf("\n");

    }
    printf("Player %d wins with: %d points!\n", currentPlayer, playerPoints[currentPlayer + 1]);
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
        if (keep == 5) { //if no if here > 5 inputs on which to save
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
                    playerRolls[currentPlayer][j] = rand() % 6;
                }
            }
        }
        printf("Roll: %d\n", *rollsAmount);
        translate(playerRolls[currentPlayer]);
        return false;
    }
}

void countPoints() {
    int roundPoints = 0;
    for (int i = 0; i < LENGTH; i++) {
        int tempSum = 0; // it resets on each and every re-roll
        //need to implement if else statement to check if some of the special hands are made on 1st throw
        /*if (rollsMade == 1) more points else fewer points*/
        if (consecutiveChecker(playerRolls[currentPlayer],
                               LENGTH)) { // Straight from 9 to King or from 10 to Ace forward and backwards
            tempSum += 20; // still scoring 20points/dice even if not consecutive
        } else if (grandeChecker(playerRolls[currentPlayer], LENGTH)) { // Works only with 5x Ace
            tempSum += 50;
        } else if (playerRolls[currentPlayer][i] == 0) { // 9
            tempSum += 1;
        } else if (playerRolls[currentPlayer][i] == 1) { // 10
            tempSum += 2;
        } else if (playerRolls[currentPlayer][i] == 2) { // Jack
            tempSum += 3;
        } else if (playerRolls[currentPlayer][i] == 3) { // Queen
            tempSum += 4;
        } else if (playerRolls[currentPlayer][i] == 4) { // King
            tempSum += 5;
        } else if (playerRolls[currentPlayer][i] == 5) { // Ace
            tempSum += 6;
        }
        roundPoints += tempSum;
        playerPoints[currentPlayer] += tempSum;
    }
    printf("Player %d made: %d points this round and total: %d points!\n", currentPlayer + 1,
           roundPoints, playerPoints[currentPlayer]);
    /*when player1 wins displays: player 1 won points: 0
     *when player2 wins display: player 0 won points: x amount*/
    //printf("Player %d got: %d points so far.\n", currentPlayer + 1, playerPoints[currentPlayer]);
}

/* the two functions finding min and max number in the array */
int getMin(const int arr[], int number) {
    int min = arr[0];
    for (int i = 1; i < number; i++)
        if (arr[i] < min)
            min = arr[i];
    return min;
}

int getMax(const int arr[], int number) {
    int max = arr[0];
    for (int i = 1; i < number; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
//this shit does not work
//even if the dices are scrambled it still returns true...
bool consecutiveChecker(int arr[], int number) {
    /* min number from the array */
    int min = getMin(arr, number);

    /* max number from the array */
    int max = getMax(arr, number);

    /* if max - min + 1 = number,  only then check all elements */
    if (max - min + 1 == number) {
        int i;
        for (i = 0; i < number; i++) {
            int j;
            if (arr[i] < 0) {
                j = -arr[i] - min;
            }else{
                j = arr[i] - min;
            }
            // if the value at index j is negative => there is repetition
            if (arr[j] > 0){
                arr[j] = -arr[j];
            }else{
                return false;
            }
        }
        /* if no negative values are present => the array has distinct values */
        return true;
    }
    return false; // if (max - min  + 1 != n)
}

bool grandeChecker(const int isGrande[], int arrayLength) {
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

bool checkGameFinished(int gameChoice) {
    switch (gameChoice) {
        case 1:
            countPoints();
            if (playerPoints[currentPlayer] >= 100) {
                return true;
            }
    }
}

bool checkPoker(const int arrayPoker[]){
    int checker = 0;
    for (int i = 0; i < LENGTH; i++) {
        if(checker == arrayPoker[i]){
            arrayPoker[i++];
        }
    }
}
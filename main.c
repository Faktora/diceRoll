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
bool grandeChecker(const int arrayGrande[],  int arrayLength);

bool checkGameFinished(int gameChoice);

int main() {

    srand((unsigned int) time(NULL));// starting here for test
    int numToKeep = 0;// takes users choice on which dice to keep, rest is getting rerolled!!!
    //printf("First roll: \n");
    int rollsMade = 0;
    int userGameChoice = 0;
    bool gameFinished = false;
    printf("What you wanna play man?\n");
    printf("");
    scanf("%d", &userGameChoice);
    while(!gameFinished) {
        grandeChecker(playerRolls[currentPlayer], LENGTH);
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
    printf("Player %d WINS!\n", currentPlayer);
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
/*  0 = 9; 1 = 10; 2 = Jack; 3 = Queen; 4 = King; 5 = Ace */
bool keepDice(int keep, int *rollsAmount) {
    int currDice;
    *rollsAmount += 1;
    if (keep == 5 || *rollsAmount == 4) {
        *rollsAmount = 0;
        return true;
    } else {
        // search
        if(*rollsAmount != 1){
            setbuf(stdout, 0);
            printf("\nHow many dice to save?\n");
            scanf("%d", &keep);
        }

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
        printf("Roll: %d\n", *rollsAmount);
        translate(playerRolls[currentPlayer]);
        return false;
    }
}

/*POINT SUMMARY
 *  9s are 1 point
 *  10s are 2 points
 *  Jacks are 3 points
 *  Queens are 4 points
 *  Kings are 5 points
 *  Aces are 6 points*/
void countPoints() {
    int tempSum = 0;
    for (int i = 0; i < LENGTH; i++) {
        if (consecutiveChecker(playerRolls[currentPlayer], LENGTH)) {
            tempSum += 20;
        } else if (grandeChecker(playerRolls[currentPlayer], LENGTH)) {
            tempSum += 50;
        } else if (playerRolls[currentPlayer][i] == 0) {
            tempSum += 1;
        } else if (playerRolls[currentPlayer][i] == 1) {
            tempSum += 2;
        } else if (playerRolls[currentPlayer][i] == 2) {
            tempSum += 3;
        } else if (playerRolls[currentPlayer][i] == 3) {
            tempSum += 4;
        } else if (playerRolls[currentPlayer][i] == 4) {
            tempSum += 5;
        } else if (playerRolls[currentPlayer][i] == 5) {
            tempSum += 6;
        }
        playerPoints[currentPlayer] += tempSum;
    }
    printf("Player %d got: %d points this round.\n", currentPlayer+1, playerPoints[currentPlayer]);
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

bool consecutiveChecker(int arr[], int number) {
    if (number < 1)
        return false;

    /* first we get the minimum number from array */
    int min = getMin(arr, number);

    /* then we get the biggest number from array */
    int max = getMax(arr, number);

    /* if max - min + 1 = number,  only then check all elements */
    if (max - min + 1 == number) {
        /* Create a temp arr to hold visited flag of all elements.
           Note that, calloc is used here so that all values are initialized
           as false */
        bool *visited = (bool *) calloc(number, sizeof(bool));
        for (int i = 0; i < number; i++) {
            /* If we see an element again, then return false */
            if (visited[arr[i] - min] != false){
                return false;
            }else {
                visited[arr[i] - min] = true;
            }
            /* If visited first time, then mark the element as visited */
        }
        /* If all elements occur once, then return true */
        return true;
    }
    return false; // if (max - min  + 1 != number)
}

bool grandeChecker(const int arrayGrande[], int arrayLength) {
    int checker = 5;
    for (int i = 0; i < arrayLength; i++) {
        if (checker == arrayGrande[i]) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool checkGameFinished(int gameChoice){
    switch (gameChoice){
        case 1: countPoints();
            if (playerPoints[currentPlayer] >= 100){
                return true;
            }
    }
}
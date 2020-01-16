#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTH 5

int playerOneRolls[LENGTH];
int playerOnePoints = 0;

//func to make the dice roll
void roll(void);

//printing func so it does not just spit the numbers from the array
void translate(const int array[]);

//this should be the func to save dice, rest of the dice should be rerolled (max 3 times)
//if the player saves all, then his turn must end (later on)
//boolean so it can keep track of numbers of rolls
bool keepDice(int keep);

//implement a pointing system :
/*POINT SUMMARY
 *  9s are 1 point
 *  10s are 2 points
 *  Jacks are 3 points
 *  Queens are 4 points
 *  Kings are 5 points
 *  Aces are 6 points*/
void countPoints(const int array[]);

int main() {
    int numToKeep = 0;// takes users choice on which dice to keep, rest is getting rerolled!!!
    //printf("First roll: \n");

    roll();
    setbuf(stdout, 0);
    printf("\nHow many dice to save?\n");
    scanf("%d", &numToKeep);
    bool isTurnEnded = keepDice(numToKeep);
    if (!isTurnEnded) {
        setbuf(stdout, 0);
        printf("\nHow many dice to save?\n");
        scanf("%d", &numToKeep);
        keepDice(numToKeep);
    }

    translate(playerOneRolls);//calls the printing function to see the rolls
    countPoints(playerOneRolls);
    /*testing print
    for (int j = 0; j < LENGTH; j++) {
        setbuf(stdout, 0);
        printf("%d ", playerOneRolls[j]);
    }*/
    setbuf(stdout, 0);
    printf("\n");

    return 0;
}

//suitable only for first time roll to fill the array with random numbers
//not going to work with re-rolls probably
//might work if I put the old rolls at the start and re-roll just the last spaces in the array
void roll() {
    int currRoll;//int to save the current roll used for testing now
    srand((unsigned int) time(NULL));
    for (int i = 0; i < LENGTH; i++) {
        currRoll = rand() % 6;// save current roll here
        playerOneRolls[i] = currRoll; // later on should be:  rolls[i] = rand() % 6
    }
    setbuf(stdout, 0);
    printf("\n");//beauty print
    translate(playerOneRolls);
    countPoints(playerOneRolls);
}

void translate(const int array[]) {
    //going through the array taking each element and then putting it in the switch machine for proper print
    for (int i = 0; i < LENGTH; i++) {
        //later on i can dump the tmp and just stay with:   switch(array[i])
        if (array[i] == 0) {
            setbuf(stdout, 0);
            printf("%-7d", 9);
        }else if(array[i] == 1) {
            setbuf(stdout, 0);
            printf("%-7d", 10);
        }else if (array[i] == 2) {
            setbuf(stdout, 0);
            printf("%-7s", "Jack");
        }else if (array[i] == 3) {
            setbuf(stdout, 0);
            printf("%-7s", "Queen");
        }else if (array[i] == 4) {
            setbuf(stdout, 0);
            printf("%-7s", "King");
        }else if (array[i] == 5){
            setbuf(stdout, 0);
            printf("%-7s", "Ace");
        }
    }
    setbuf(stdout, 0);
    printf("\n");//beauty print
}

/*  0 = 9; 1 = 10; 2 = Jack; 3 = Queen; 4 = King; 5 = Ace */

bool keepDice(int keep) {
    int currDice;
    if (keep == 5) {
        return true;
    } else {// search
        int arrayKeep[keep];
        setbuf(stdout, 0);
        printf("\nWhich one to keep? Separate with enters.\n");
        for (int k = 0; k < keep; k++) {
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
                srand((unsigned int) time(NULL));
                playerOneRolls[j] = rand() % 6;
            }
        }
        translate(playerOneRolls);
        countPoints(playerOneRolls);
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
void countPoints(const int array[]) {
    int tempSum = 0;
    for (int i = 0; i < LENGTH; i++) {
        if (array[i] == 0) {
            if (array[i] == 0) {
                tempSum += 1;
            } else if (array[i] == 1) {
                tempSum += 2;
            } else if (array[i] == 2) {
                tempSum += 3;
            } else if (array[i] == 3) {
                tempSum += 4;
            } else if (array[i] == 4) {
                tempSum += 5;
            } else if (array[i] == 5) {
                tempSum += 6;
            }
            playerOnePoints = tempSum;
        }
        printf("Player one got: %d points this round.\n", playerOnePoints);

    }
}
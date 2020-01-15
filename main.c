#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LENGHT 6

int rolls[LENGHT];
int throws = 0;

//func to make the dice roll
void roll();

//printing func so it does not just spit the numbers from the array
void translate(const int array[]);

//this should be the func to save dice, rest of the dice should be rerolled (max 3 times)
//if the player saves all, then his turn must end (later on)
void keepDice(int ch, int array[]);

int main() {
    int choice = 0;// takes users choice on which dice to keep, rest is getting rerolled!!!
    roll(rolls);
    scanf("Which dice do you want to keep?\nChoose between 0 and 5!\n%d", choice);
    keepDice(choice, rolls);
    translate(rolls);//calls the printing function to see the rolls
    //testing print
    for (int j = 0; j < LENGHT; j++) {
        printf("%d ", rolls[j]);
    }
    printf("\n");

    return 0;
}
//suitable only for first time roll to fill the array with random numbers
//not going to work with rerolls probably
//might work if I put the old rolls at the start and reroll just the last spaces in the array
void roll() {
    int currRoll;//int to save the current roll used for testing now
    srand((unsigned int) time(NULL));
    for (int i = 0; i <= 5; i++) {
        currRoll = rand() % 6;// save current roll here
        rolls[i] = currRoll; // later on should be:  rolls[i] = rand() % 6;
        printf("%d ", currRoll);//just checking
    }
    printf("\n");//beauty print
}

void translate(const int array[]) {
    int tmp = 0;// using it for the switch statement, no better idea atm
    //going through the array taking each element and then putting it in the switch machine for proper print
    for (int i = 0; i < LENGHT; i++) {
        tmp = array[i];
        //later on i can dump the tmp and just stay with:   switch(array[i])
        switch (tmp) {
            case 0:
                printf("%7d", 9);
                break;
            case 1:
                printf("%7d", 10);
                break;
            case 2:
                printf("%7s", "Jack");
                break;
            case 3:
                printf("%7s", "Queen");
                break;
            case 4:
                printf("%7s", "King");
                break;
            case 5:
                printf("%7s", "Ace");
                break;
            default:
                break;
        }
    }
    printf("\n");//beauty print
}

/*  0 = 9; 1 = 10; 2 = Jack; 3 = Queen; 4 = King; 5 = Ace */

void keepDice(int ch, int array[]) {
    int tmp[LENGHT];
    for (int i = 0; i < LENGHT; i++) {
        tmp[i] = array[i];
    }
}
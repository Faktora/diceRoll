#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "function.h"

#define LENGTH 5

int player_throws[2][LENGTH];
int player_points[2];
int current_player = 1;


void is_highest(const int array[]);

//printing func so it does not just spit the numbers from the array
void translate(const int array[]);

//this should be the func to save dice, rest of the dice should be rerolled (max 3 times)
//if the player saves all, then his turn must end (later on)
//boolean so it can keep track of numbers of rolls
bool keep_dice(int keep, int *amount_of_rolls, bool *has_rerolled);

bool calculate_points(bool *has_rerolled);

/* is_consecutive's little helpers */
int is_min(const int player_throws[], int array_throws_length);//finds the min element in the array
int is_max(const int player_throws[], int array_throws_length);//finds the max element in the array
/* returns true if all array elements are consecutive
 * returns false if the array elements are not consecutive*/
bool is_consecutive(int player_throws[], int array_throws_length);
/*checks if all array elements are Aces or not*/
bool is_grande(const int grande_array[], int array_length);

bool is_game_finished(int gameChoice, bool *has_rerolled);

bool is_poker();

bool is_fullhouse();

void roll_dice(int keep, int *array_keep);

int main() {
    srand((unsigned int) time(NULL));// starting here for more randomness
    int save_dice = 0;// takes users choice on which dice to keep, rest is getting rerolled!!!
    int user_game_choice = 0;
    int round_counter = 1;
    int cnt_rolls = 0;
    bool game_finished = false;

    printf(" *** GAME MODES ***\n1) Normal point summary (100points)\n2) Table point summary\n");
    printf("\n");
    scanf("%d", &user_game_choice);

    while (!game_finished) {
        if (current_player == 0) {
            current_player = 1;
        } else {
            printf("Round %d ", round_counter);
            current_player = 0;
        }

        printf("Player %d rolls now! Good luck!\n", current_player + 1);
        setbuf(stdout, 0);
        bool isTurnEnded = false;
        bool has_rerolled = false;
        while (!isTurnEnded) {
            isTurnEnded = keep_dice(save_dice, &cnt_rolls, &has_rerolled);
        }

        game_finished = is_game_finished(user_game_choice, &has_rerolled);
        cnt_rolls = 0;
        setbuf(stdout, 0);
        printf("\n");

    }
    printf("Player %d wins with: %d points!\n", current_player + 1, player_points[current_player]);
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

bool keep_dice(int keep, int *amount_of_rolls, bool *has_rerolled) {
    int cnt_dice;
    *amount_of_rolls += 1;
    if (*amount_of_rolls == 4) {
        return true;
    } else {
        // search
        if (*amount_of_rolls == 1) {
            roll_dice(0, NULL);
            translate(player_throws[current_player]);
            return false;
        } else {
            setbuf(stdout, 0);
            printf("\nHow many dice to save?\n");
            scanf("%d", &keep);
            int *array_keep = malloc(LENGTH * sizeof(int));
            if (keep == 5) {
                return true;
            }

            *has_rerolled = true;

            for (int k = 0; k < keep; k++) {
                setbuf(stdout, 0);
                printf("\nWhich one to keep?\n");
                scanf("%d", &cnt_dice);
                array_keep[k] = cnt_dice;
            }

            roll_dice(keep, array_keep);
            free(array_keep);
        }
        translate(player_throws[current_player]);
        return false;
    }
}

bool calculate_points(bool *has_rerolled) {
    int temp_sum = 0;
    bool point_sumation_ended = false;

    //need to implement if else statement to check if some of the special hands are made on 1st throw
    /*if (rollsMade == 1) more points else fewer points*/
    if (is_consecutive(player_throws[current_player],
                       LENGTH)) { // Straight from 9 to King or from 10 to Ace forward and backwards
        (*has_rerolled) ? (temp_sum += 20) : (temp_sum += 25);
        //tempSum += 20; // still scoring 20points/dice even if not consecutive
        point_sumation_ended = true;
    } else if (is_grande(player_throws[current_player], LENGTH)) { // Works only with 5x Ace
        (*has_rerolled) ? (temp_sum += 50) : (temp_sum += 80);
        //tempSum += 50;
        point_sumation_ended = true;
    } else if (is_fullhouse(player_throws[current_player])) {
        (*has_rerolled) ? (temp_sum += 30) : (temp_sum += 35);
        //tempSum += 30;
        point_sumation_ended = true;
    } else if (is_poker(player_throws[current_player])) {
        (*has_rerolled) ? (temp_sum += 40) : (temp_sum += 45);
        //tempSum += 40;
        point_sumation_ended = true;
    }

    if (!point_sumation_ended) {
        for (int i = 0; i < LENGTH; i++) {
            // it resets on each and every re-roll
            if (player_throws[current_player][i] == 0) { // 9
                temp_sum += 1;
            } else if (player_throws[current_player][i] == 1) { // 10
                temp_sum += 2;
            } else if (player_throws[current_player][i] == 2) { // Jack
                temp_sum += 3;
            } else if (player_throws[current_player][i] == 3) { // Queen
                temp_sum += 4;
            } else if (player_throws[current_player][i] == 4) { // King
                temp_sum += 5;
            } else if (player_throws[current_player][i] == 5) { // Ace
                temp_sum += 6;
            }
        }
        point_sumation_ended = true;
    }

    player_points[current_player] += temp_sum;

    printf("Player %d made: %d points this round and total: %d points!\n", current_player + 1,
           temp_sum, player_points[current_player]);
    return point_sumation_ended;
    /*when player1 wins displays: player 1 won points: 0
     *when player2 wins display: player 0 won points: x amount*/
    //printf("Player %d got: %d points so far.\n", currentPlayer + 1, playerPoints[currentPlayer]);
}


//finding the smallest element in the array
int is_min(const int player_throws[], int array_throws_length) {
    int min = player_throws[0];
    for (int i = 0; i < array_throws_length; i++) {
        if (player_throws[i] < min) {
            min = player_throws[i];
        }
    }
    return min;
}

//finding the biggest element in the array
int is_max(const int player_throws[], int array_throws_length) {
    int max = player_throws[0];
    for (int i = 0; i < array_throws_length; i++) {
        if (player_throws[i] > max) {
            max = player_throws[i];
        }
    }
    return max;
}

bool is_consecutive(int player_throws[], int array_throws_length) {
    //get the minimum number from the array
    int min = is_min(player_throws, array_throws_length);

    //get the maximum number from the array
    int max = is_max(player_throws, array_throws_length);

    //if max - min + 1 == arrayThrowsLength, only then check all elements
    if (max - min + 1 == array_throws_length) {
        int indexOne;
        for (indexOne = 0; indexOne < array_throws_length; indexOne++) {
            int indexTwo;
            if (player_throws[indexOne] < 0) {
                indexTwo = -player_throws[indexOne] - min;
            } else {
                indexTwo = player_throws[indexOne] - min;
            }
            //if the value at indexTwo is negative => there is repetition
            if (player_throws[indexTwo] > 0) {
                player_throws[indexTwo] = -player_throws[indexTwo];
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

bool is_grande(const int grande_array[], int array_length) {
    const int checker = 5;
    for (int i = 0; i < array_length; i++) {
        if (checker == grande_array[i]) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

bool is_game_finished(int gameChoice, bool *has_rerolled) {
    if (gameChoice == 1) {
        calculate_points(has_rerolled);
        return ((player_points[current_player] >= 100) ? (true) : (false));
    } else if (gameChoice == 2) {
        printf("Still under construction sorry!\n ");
        return true;
    }
    return false;
}

bool is_poker() {
    bool first_possibility, second_possibility;
    is_highest(player_throws[current_player]);

    first_possibility =
            player_throws[current_player][0] == player_throws[current_player][1] &&
            player_throws[current_player][1] == player_throws[current_player][2] &&
            player_throws[current_player][2] == player_throws[current_player][3];

    second_possibility =
            player_throws[current_player][1] == player_throws[current_player][2] &&
            player_throws[current_player][2] == player_throws[current_player][3] &&
            player_throws[current_player][3] == player_throws[current_player][4];

    return (first_possibility || second_possibility);
}


bool is_fullhouse() {
    bool first_possibility, second_possibility;
    is_highest(player_throws[current_player]);

    first_possibility =
            player_throws[current_player][0] == player_throws[current_player][1] &&
            player_throws[current_player][1] == player_throws[current_player][2] &&
            player_throws[current_player][3] == player_throws[current_player][4];

    second_possibility =
            player_throws[current_player][0] == player_throws[current_player][1] &&
            player_throws[current_player][2] == player_throws[current_player][3] &&
            player_throws[current_player][3] == player_throws[current_player][4];

    return (first_possibility || second_possibility);
}

//sorting array by power
void is_highest(const int array[]) {
    int i, j, minimum_j;

    for (i = 0; i < LENGTH; i++) {
        // search the array for the minimum element value in the array
        minimum_j = i;   // take that array[i] is the minimum

        for (j = i + 1; j < LENGTH; j++) {
            if (player_throws[current_player][j] < player_throws[current_player][minimum_j]) {
                minimum_j = j;    // found smaller => updating minimum_j with new element
            }
        }
        // swapping the elements around so they can be sorted by power
        int help = player_throws[current_player][i];// temporary value to help with swapping
        player_throws[current_player][i] = player_throws[current_player][minimum_j];
        player_throws[current_player][minimum_j] = help;
    }
}

void roll_dice(int keep, int *array_keep) {
    for (int j = 0; j < 5; j++) {//
        bool isKeep = false;
        for (int i = 0; i < keep; i++) {
            if (array_keep[i] == j) {
                isKeep = true;
            }
        }
        if (!isKeep) {
            player_throws[current_player][j] = rand() % 6; //to make them shuffle again
        }
    }
}

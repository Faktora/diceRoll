#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "table_point_sum.h"
#include "base_functions.h"
#include "point_computing.h"

#define LENGTH 5 //length five because we throw 5 dices

/// \brief the main() - saves most of the variables used by the game
/// and calls each and every function inside this .c file
/// function definitions are external to reduce clutter in main.c
/// and for better overview of them
///
/// \param LENGTH - how many dices are used in the game
/// \param player_throws - saves the current player's dice trow combination, and shows it to him
/// \param player_points - saves player's points (later on displayed as sum)
/// \param current_player - shows which player turn is, and displays it when needed (start of each round)
/// \param save_dice - takes user input on dices he choose to save, rest gets re-rolled
/// \param user_game_choice - saves what the user input at the start for game choice
/// \param round_counter - counts game rounds, then used to display to show players the current round
/// \param count_rolls - follows how many rolls did the player have this round, resets every round
/// \param array_points - saves each players points in his own column
/// \param game_finished - boolean to check if any of the game modes have finished to end the game
/// \param is_turn_ended - boolean to checking if players turn has ended
/// \param has_rerolled - boolean to check if the player has re-rolled, used in throws and pointing
/// system to reward players greatly for lucky first throws


int player_throws[2][LENGTH];
int player_points[2];
int current_player = 1;


int main() {
    srand((unsigned int) time(NULL));// starting here for more randomness
    int save_dice = 0;// takes users choice on which dice to keep, rest is getting rerolled!!!
    int user_game_choice = 0;
    int round_counter = 1;
    int count_rolls = 0;
    int array_points[12][2] = {0};
    //int pointing_table[2][10]; used for the 2nd game choice, which is still not done.
    bool game_finished = false;

    printf(" *** GAME MODES ***\n1) Normal point summary (100 Points)\n2) Table point summary (100 Points)\n");
    printf("\n");
    scanf("%d", &user_game_choice);

    while (!game_finished) {
        if (current_player == 0) {
            current_player = 1;
            round_counter += 1;
        } else {
            printf("Round %d ", round_counter);
            current_player = 0;
        }

        printf("Player %d Roll %d Good luck!\n", current_player + 1, count_rolls + 1);
        setbuf(stdout, 0);
        bool is_turn_ended = false;
        bool has_rerolled = false;
        while (!is_turn_ended) {
            is_turn_ended = keep_dice(save_dice, &count_rolls, &has_rerolled);
        }

        game_finished = is_game_finished(user_game_choice, &has_rerolled, array_points);
        count_rolls = 0;
        setbuf(stdout, 0);
        printf("\n");

    }
    printf("Player %d wins with: %d points!\n", current_player + 1, player_points[current_player]);
    return 0;
}

void translate(const int array[]) {
    //going through the array taking each element and then putting it in the switch machine for proper print
    for (int i = 0; i < LENGTH; i++) {
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
            printf("\nHow many dice to save?\n(Numbers between 0 [none] and 5 [all, end turn], enter to confirm)\n");
            scanf("%d", &keep);
            int *array_keep = malloc(LENGTH * sizeof(int));
            if (keep == 5) {
                return true;
            }

            *has_rerolled = true;

            for (int k = 0; k < keep; k++) {
                setbuf(stdout, 0);
                printf("\nWhich one to keep?\n(use numbers between 0 and 5 and end with enter please!)\n");
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
    bool point_summation_ended = false;

    //need to implement if else statement to check if some of the special hands are made on 1st throw
    /*if has_rerolled true => fewer points else more points*/
    if (is_consecutive(player_throws[current_player],
                       LENGTH)) { // Straight from 9 to King or from 10 to Ace forward and backwards
        (*has_rerolled) ? (temp_sum += 20) : (temp_sum += 25);
        point_summation_ended = true;
    } else if (is_grande(player_throws[current_player], LENGTH)) { // Works only with 5x Ace
        (*has_rerolled) ? (temp_sum += 50) : (temp_sum += 80);
        point_summation_ended = true;
    } else if (is_fullhouse(player_throws[current_player])) {
        (*has_rerolled) ? (temp_sum += 30) : (temp_sum += 35);
        point_summation_ended = true;
    } else if (is_poker(player_throws[current_player])) {
        (*has_rerolled) ? (temp_sum += 40) : (temp_sum += 45);
        point_summation_ended = true;
    }

    if (!point_summation_ended) {
        for (int i = 0; i < LENGTH; i++) {
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
        point_summation_ended = true;
    }

    player_points[current_player] += temp_sum;

    printf("Player %d made: %d points this round and total: %d points!\n\n\n", current_player + 1,
           temp_sum, player_points[current_player]);
    return point_summation_ended;
}

int is_min(const int player_throws_min[], int array_throws_length) {
    int min = player_throws_min[0];
    for (int i = 0; i < array_throws_length; i++) {
        if (player_throws_min[i] < min) {
            min = player_throws_min[i];
        }
    }
    return min;
}

int is_max(const int player_throws_max[], int array_throws_length) {
    int max = player_throws_max[0];
    for (int i = 0; i < array_throws_length; i++) {
        if (player_throws_max[i] > max) {
            max = player_throws_max[i];
        }
    }
    return max;
}

bool is_consecutive(int player_throws_consecutive[], int array_throws_length) {
    //get the minimum number from the array
    int min = is_min(player_throws_consecutive, array_throws_length);

    //get the maximum number from the array
    int max = is_max(player_throws_consecutive, array_throws_length);

    //if max - min + 1 == arrayThrowsLength, only then check all elements
    if (max - min + 1 == array_throws_length) {
        int indexOne;
        for (indexOne = 0; indexOne < array_throws_length; indexOne++) {
            int indexTwo;
            if (player_throws_consecutive[indexOne] < 0) {
                indexTwo = -player_throws_consecutive[indexOne] - min;
            } else {
                indexTwo = player_throws_consecutive[indexOne] - min;
            }
            //if the value at indexTwo is negative => there is repetition
            if (player_throws_consecutive[indexTwo] > 0) {
                player_throws_consecutive[indexTwo] = -player_throws_consecutive[indexTwo];
            } else {
                return false;
            }
        }
        //if no negative values are present => the arrays elements are distinct
        return true;
    }
    //if max - min + 1 != n
    return false;
} //straight

bool is_grande(const int grande_array[], int array_length) {
    const int checker = 5; // because Aces = 5
    for (int i = 0; i < array_length; i++) {
        if (checker == grande_array[i]) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}//grande

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
}//poker

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
}//full house

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
        // sorting elements by power
        int temp_help = player_throws[current_player][i];// temporary value to help with swapping
        player_throws[current_player][i] = player_throws[current_player][minimum_j];
        player_throws[current_player][minimum_j] = temp_help;
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
            player_throws[current_player][j] = 5;//rand() % 6; //to make them shuffle again
        }
    }
}

bool is_game_finished(int game_choice, bool *has_rerolled, int array_points[][2]) {
    if (game_choice == 1) {
        calculate_points(has_rerolled);
        return ((player_points[current_player] >= 100) ? (true) : (false));
    } else if (game_choice == 2) {
        calculate_points(has_rerolled);
        table_point_scoring(array_points);
        return ((player_points[current_player] >= 100) ? (true) : (false));
    }
    return false;
}

void table_point_summary(int points[][2]){
    //bool already_saved = false; //checking if the player have saved to the table already

    //Scoring table
    char array_first_row[3][10] = {"Deck", "Player 1", "Player 2"};
    char array_rolls_column[12][11] = {"9s", "10s", "Jacks", "Queens", "Kings", "Aces",
                               "Straight", "Full House", "Poker", "Grande", "Sum"};
    /* How array looks like:
     * array_points[12][2] = {
     *                  {0,                0},  //9s            position 0
                        {0,                0},  //10s           position 1
                        {0,                0},  //Jacks         position 2
                        {0,                0},  //Queens        position 3
                        {0,                0},  //Kings         position 4
                        {0,                0},  //Aces          position 5
                        {0,                0},  //Straight      position 6
                        {0,                0},  //Full House    position 7
                        {0,                0},  //Poker         position 8
                        {0,                0},  //Grande        position 9
                        {0,                0}   //Sum           position 10
                        };
     */

    // just 1000 loops printing the beautiful table
    printf("\n");
            //printing the scoring table
    for (int k = 0; k < 41; k++) {
        printf("=");
    }
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf("| %10s ", array_first_row[i]);
    }
    printf(" |\n");
    for (int k = 0; k < 41; k++) {
        printf("=");
    }
    printf("\n");
    for (int i = 0; i < 11; i++) {
        printf("| %10s ", array_rolls_column[i]);
        for (int j = 0; j < 2 ; j++) {
            printf("| %10d ", points[i][j]);
        }
        printf(" |\n");
        for (int k = 0; k < 41; k++) {
            printf("=");
        }
        printf("\n");
    }
}

void table_point_scoring(int points_array[][2]){
    char save;
    bool already_saved = false;
    if(&is_grande){
        printf("You got grande! Thats 50 pts. Wanna save? y/n\n");
        scanf(" %c", &save);

        if(save == 'Y' || save == 'y'){
            if (points_array[9][current_player] == 0){
                points_array[9][current_player] += 1;
                bool already_saved = true;
            }else if (points_array[9][current_player] == 1){
                points_array[9][current_player] += 1;
                bool already_saved = true;
            }else if (points_array[9][current_player] == 2){
                points_array[9][current_player] += 1;
                bool already_saved = true;
            } else {
                printf("\nYou have already saved 3.\n Save something else.\n");
            }
        }
        points_array[10][current_player] = player_points[current_player];
        table_point_summary(points_array);
    }
    if(&is_poker){
        printf("You got grande! Thats 50 pts. Wanna save? y/n\n");
        scanf(" %c", &save);

        if(save == 'Y' || save == 'y'){
            if (points_array[8][current_player] == 0){
                points_array[8][current_player] += 1;
                bool already_saved = true;
            }else if (points_array[8][current_player] == 1){
                points_array[8][current_player] += 1;
                bool already_saved = true;
            }else if (points_array[8][current_player] == 2){
                points_array[8][current_player] += 1;
                bool already_saved = true;
            } else {
                printf("\nYou have already saved 3.\n Save something else.\n");
            }
        }
        points_array[10][current_player] = player_points[current_player];
        table_point_summary(points_array);
    }
    if(&is_fullhouse){
        printf("You got grande! Thats 50 pts. Wanna save? y/n\n");
        scanf(" %c", &save);

        if(save == 'Y' || save == 'y'){
            if (points_array[7][current_player] == 0){
                points_array[7][current_player] += 1;
                bool already_saved = true;
            }else if (points_array[7][current_player] == 1){
                points_array[7][current_player] += 1;
                bool already_saved = true;
            }else if (points_array[7][current_player] == 2){
                points_array[7][current_player] += 1;
                bool already_saved = true;
            } else {
                printf("\nYou have already saved 3.\n Save something else.\n");
            }
        }
        points_array[10][current_player] = player_points[current_player];
        table_point_summary(points_array);
    }
    if(&is_consecutive){
        printf("You got grande! Thats 50 pts. Wanna save? y/n\n");
        scanf(" %c", &save);

        if(save == 'Y' || save == 'y'){
            if (points_array[6][current_player] == 0){
                points_array[6][current_player] += 1;
                bool already_saved = true;
            }else if (points_array[6][current_player] == 1){
                points_array[6][current_player] += 1;
                bool already_saved = true;
            }else if (points_array[6][current_player] == 2){
                points_array[6][current_player] += 1;
                bool already_saved = true;
            } else {
                printf("\nYou have already saved three times.\n Save something else.\n");
            }
        }
        points_array[10][current_player] = player_points[current_player];
        table_point_summary(points_array);
    }
    while (already_saved == false){
        
    }
}
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "table_point_sum.h"
#include "base_functions.h"
#include "point_computing.h"
#include "can_must_table.h"
#include "pyramid.h"

#define DICES 5 //we throw 5 dices

/// \brief the main() - saves most of the variables used by the game
/// and calls each and every function inside this .c file
/// function definitions are external to reduce clutter in main.c
/// and for better overview of them
///
/// \param DICES - how many dices are used in the game
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


int player_throws[2][DICES];
int player_points[2];
int current_player = 1;


int main() {
    srand((unsigned int) time(NULL));// starting here for more randomness
    int save_dice = 0;// takes users choice on which dice to keep, rest is getting re-rolled!!!
    int user_game_choice = 0;
    int round_counter = 1;
    int count_rolls = 0;
    int array_points[12][2] = {0};
    struct pyramid *pyra = {0};
    bool game_finished = false;


    printf(" *** GAME MODES ***\n1) Normal point summary (100 Points)\n2) Table point summary (100 Points)\n");
    printf("3) Can Must Game Mode\n");
    printf("4) Pyramid\n");
    printf("\n");
    scanf("%d", &user_game_choice);

    if(user_game_choice == 4) {
        struct pyramid new_pyramid = initialise_pyramid();
        pyra = &new_pyramid;
    }

    while (!game_finished) {
        if (current_player == 0) {
            current_player = 1;
        } else {
            printf("Round %d ", round_counter);
            current_player = 0;
        }

        printf("Player %d Roll %d Good luck!\n", current_player + 1, count_rolls + 1);
        bool is_turn_ended = false;
        bool has_rerolled = false;
        while (!is_turn_ended) {
            is_turn_ended = keep_dice(save_dice, &count_rolls, &has_rerolled);
        }

        game_finished = is_game_finished(user_game_choice, &has_rerolled, array_points, round_counter, pyra);
        count_rolls = 0;
        if (current_player == 1) {
            round_counter += 1;
        }
        setbuf(stdout, 0);
        printf("\n");

    }
    printf("Player %d wins with: %d points!\n", current_player + 1, player_points[current_player]);
    return 0;
}

void translate(const int array[]) {
    //going through the array taking each element and then putting it in the switch machine for proper print
    for (int i = 0; i < DICES; i++) {
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
            int *array_keep = malloc(DICES * sizeof(int));
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

bool calculate_points(const bool *has_rerolled) {
    int temp_sum = 0;
    bool point_summation_ended = false;

    if (is_consecutive(player_throws[current_player])) {
        (*has_rerolled) ? (temp_sum += 20) : (temp_sum += 25);
        point_summation_ended = true;
    } else if (is_grande()) {
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
        for (int i = 0; i < DICES; i++) {
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

int is_min(const int player_throws_min[]) {
    int min = player_throws_min[0];
    for (int i = 0; i < DICES; i++) {
        if (player_throws_min[i] < min) {
            min = player_throws_min[i];
        }
    }
    return min;
}

int is_max(const int player_throws_max[]) {
    int max = player_throws_max[0];
    for (int i = 0; i < DICES; i++) {
        if (player_throws_max[i] > max) {
            max = player_throws_max[i];
        }
    }
    return max;
}

bool is_consecutive(int player_throws_consecutive[]) {
    //get the minimum number from the array
    int min = is_min(player_throws_consecutive);

    //get the maximum number from the array
    int max = is_max(player_throws_consecutive);

    //if max - min + 1 == arrayThrowsLength, only then check all elements
    if (max - min + 1 == DICES) {
        int indexOne;
        for (indexOne = 0; indexOne < DICES; indexOne++) {
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
} //Straight 20/25pts

bool is_grande() {//const int grande_array[], int array_length) { old style Grande 50/80pts
    int *throws = gather_counts();

    if (throws[5] == 5 || throws[4] == 5 || throws[3] == 5 || throws[2] == 5 || throws[1] == 5 || throws[0] == 5 ) {
        return true;
    } else {
        return false;
    }/*
    const int checker = 5; // because Aces = 5
    for (int i = 0; i < array_length; i++) {
        if (checker == grande_array[i]) {
            continue;
        } else {
            return false;
        }
    }
    return true;*/
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
}//Poker 40/45pts

bool is_fullhouse() { //Full House 30/35pts
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

void is_highest() {
    int i, j, minimum_j;

    for (i = 0; i < DICES; i++) {
        // search the array for the minimum element value in the array
        minimum_j = i;   // take that array[i] is the minimum

        for (j = i + 1; j < DICES; j++) {
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

void roll_dice(int keep, const int *array_keep) {
    for (int j = 0; j < 5; j++) {//
        bool isKeep = false;
        for (int i = 0; i < keep; i++) {
            if (array_keep[i] == j) {
                isKeep = true;
            }
        }
        if (!isKeep) {
            player_throws[current_player][j] = rand() % 6;
        }
    }
}

bool is_game_finished(int game_mode, bool *has_rerolled, int array_points[][2], int round_counter, struct pyramid *pyra) {
    if (game_mode == 1) {
        calculate_points(has_rerolled);
        return ((player_points[current_player] >= 100) ? (true) : (false));
    } else if (game_mode == 2) {
        table_point_scoring(array_points, has_rerolled, game_mode);
        return ((player_points[current_player] >= 100) ? (true) : (false));
    } else if (game_mode == 3) {
        //printf(" THIS IS THE CURRENT ROUND ::::::   === %d \n", round_counter);
        if (round_counter < 11) {
            table_point_scoring(array_points, has_rerolled, game_mode);
        } else {
            can_must_pt_two(round_counter, array_points);
            if (round_counter == 20) {
                if (current_player) {
                    if (player_points[current_player] < player_points[current_player - 1]) {
                        current_player = 0;
                        return true;
                    }
                } else {
                    if (player_points[current_player] < player_points[current_player + 1]) {
                        current_player = 1;
                        return true;
                    }
                }
            }
        }
    } else if (game_mode == 4){
        write_to_pyramid(pyra);
        print_pyramid(pyra);
        if(check_pyramid(pyra)) {
            return true;
        }
    }
    return false;
}

void table_point_summary(int points[][2]) {
    //Function printing the scoring table
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
        for (int j = 0; j < 2; j++) {
            printf("| %10d ", points[i][j]);
        }
        printf(" |\n");
        for (int k = 0; k < 41; k++) {
            printf("=");
        }
        printf("\n");
    }
}

void table_point_scoring(int points_array[][2], bool has_rerolled, int game_mode) {

    bool already_saved = false;

    int *single_throws = gather_counts();

    if (is_grande()) {
        printf("You got Grande! Wanna save? y/n\n");
        already_saved = save_special(points_array, game_mode, 9);

        points_array[10][current_player] += (has_rerolled ? 50 : 80);
    } else if (is_poker()) {
        printf("You got Poker! Wanna save? y/n\n");
        already_saved = save_special(points_array, game_mode, 8);

        points_array[10][current_player] += (has_rerolled ? 40 : 45);
    } else if (is_fullhouse()) {
        printf("You got Full House! Wanna save? y/n\n");
        already_saved = save_special(points_array, game_mode, 7);

        points_array[10][current_player] += (has_rerolled ? 30 : 35);
    } else if (is_consecutive(player_throws[current_player])) {
        printf("You got Straight! Wanna save? y/n\n");
        already_saved = save_special(points_array, game_mode, 6);

        points_array[10][current_player] += (has_rerolled ? 20 : 25);
    }
    if (!already_saved) {
        save_singles_table(points_array, single_throws, already_saved, game_mode);
    }
    table_point_summary(points_array);
    free(single_throws);
}

int *gather_counts() {
    int *single_throws = malloc(6 * sizeof(int));

    for (int i = 0; i < 6; i++) {
        single_throws[i] = 0;
    }

    /* Counting what and how many of each individual type of dice is rolled,
    * after that it is printed so the player can see the result
    * currently prints it when the player wishes to save; right before printing the table which
    * makes it completely useless*/
    for (int i = 0; i < DICES; i++) {
        if (player_throws[current_player][i] == 0) {
            single_throws[0] += 1; //9s
        } else if (player_throws[current_player][i] == 1) {
            single_throws[1] += 1; //10s
        } else if (player_throws[current_player][i] == 2) {
            single_throws[2] += 1; //Js
        } else if (player_throws[current_player][i] == 3) {
            single_throws[3] += 1; //Qs
        } else if (player_throws[current_player][i] == 4) {
            single_throws[4] += 1; //Ks
        } else if (player_throws[current_player][i] == 5) {
            single_throws[5] += 1; //As
        }
    }
    return single_throws;
}

bool save_special(int points_array[][2], int game_mode, int row) {
    char save_special_throw;
    scanf(" %c", &save_special_throw);

    if (save_special_throw == 'Y' || save_special_throw == 'y') {
        if (game_mode == 3 && points_array[row][current_player] != 0) {
            printf("You already saved here!\n");
            return false;
        } else {
            points_array[row][current_player] += 1;
            return true;
        }
    } else {
        return false;
    }
}

void save_singles_table(int points_array[][2], const int single_throws[], bool already_saved, int game_mode) {
    int save_single_throw;
    bool can_save_single = false;
    int save_into_row;

    /* this while loop save single dice values only, aka when there is no unique combination roll
     * or no more available unique saves
     * if the player have already saved then this while loop will be skipped */
    for (int i = 0; i < 6; i++) {
        if (points_array[i][current_player] == 0 && single_throws[i] != 0) {
            can_save_single = true;
        }
    }

    if (!can_save_single && game_mode == 3) {
        printf("You can not save any singles.\nYou must choose row to write 0 into.\n");
        printf("Where do you want to write 0?\n");
        while (!already_saved) {
            scanf(" %d", &save_into_row);
            if (save_into_row < 10 && points_array[save_into_row][current_player] == 0) {
                points_array[save_into_row][current_player] = -1; // -1 means the player wrote 0 in this row
                already_saved = true;
            } else {
                printf("Input is not accepted!\n");
            }
        }
    }

    while (!already_saved) {
        printf("Which dice/dices do you want to save?\n");
        printf("0 = Nines, 1 = Tens, 2 = Jacks, 3 = Queens, 4 = Kings, 5 = Aces\n");
        scanf(" %d", &save_single_throw);

        if (single_throws[save_single_throw] > 0 && save_single_throw < 6) {
            if (game_mode == 3 && points_array[save_single_throw][current_player] != 0) {
                printf("You already wrote here!\n");
            } else {
                points_array[save_single_throw][current_player] += single_throws[save_single_throw];
                already_saved = true;
                points_array[10][current_player] += single_throws[save_single_throw] * (save_single_throw + 1);
            }

        } else {
            printf("\nNo cheating! You did not throw any of these this round!\n");
        }
    }
}

void can_must_pt_two(int round_counter, int points_array[][2]) {
    int *singles_throws = gather_counts();
    int position = round_counter - 11;
    int *current_score = &points_array[position][current_player];
    int current_amount = singles_throws[position];
    bool has_special = false;

    //must add prints to explain the point of each case!!!!
    switch (round_counter) {
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            printf("Round 11 - 9s | Round 12 - 10s | Round 13 - Jacks | Round 14 - Queens | Round 15 - Kings | Round 16 - Aces\n");
            printf("If you dont throw them in the required round, you do not get ANY points.\n");
            printf("Saving is done automatically in this part of the game! \n");
            *current_score += (*current_score == -1) ? (current_amount + 1) : (current_amount);
            break;
        case 17:
            printf("You must make a Straight this round in order to get points!\n");
            has_special = is_consecutive(player_throws[current_player]);
            break;
        case 18:
            printf("You must make a Full House this round in order to get points!\n");
            has_special = is_fullhouse();
            break;
        case 19:
            printf("You must make a Poker this round in order to get points!\n");
            has_special = is_poker();
            break;
        case 20:
            printf("You must make a Grande this round in order to get points!\n");
            has_special = is_grande();
            break;
        default:
            break;
    }

    if (has_special) {
        *current_score += (*current_score == -1) ? (current_amount + 1) : (current_amount);
    } else if (*current_score == -1) {
        *current_score = 0;
    }

    table_point_summary(points_array);
    free(singles_throws);
}

struct pyramid initialise_pyramid() {
    struct pyramid pyra = {
            .grande = {0},
            .poker = {0},
            .full_house = {0},
            .straight = {0},
            .aces = {0},
            .kings = {0},
            .queens = {0},
            .jacks = {0},
            .tens = {0},
            .nines = {0}
    };

    return pyra;
}

int next_free(const int* array_to_find_free_position, int array_len) {
    int result = -1;
    for(int i = 0; i < array_len; i++){
        if(array_to_find_free_position[i] == 0) {
            result = i;
            break;
        }
    }

    return result;
}

void write_to_pyramid(struct pyramid *pyra) {
    int *save_singles = gather_counts();
    int save_this;
    char save_pls;
    bool saved = false;

    if (is_grande()) {
        printf("You have a grande, do you want to save it to the pyramid?\n");
        scanf(" %c", &save_pls);
        int next_free_position = next_free(pyra->grande[current_player], 1);
        if(next_free_position != -1 && (save_pls == 'y' || save_pls == 'Y')) {
            pyra->grande[current_player][next_free_position] = 1;
            saved = true;
        } else {
            printf("You can't write any more Grandes! This row is already filled!\n");
        }
    }

    if(!saved && is_poker()) {
        printf("You have a poker, do you want to save it to the pyramid?\n");
        scanf(" %c", &save_pls);
        int next_free_position = next_free(pyra->poker[current_player], 1);
        if(next_free_position != -1 && (save_pls == 'y' || save_pls == 'Y')) {
            pyra->poker[current_player][next_free_position] = 1;
            saved = true;
        } else {
            printf("You can't write any more Pokers! This row is already filled!\n");
        }
    }

    if (!saved && is_fullhouse()) {
        printf("You have a Full House, do you want to save it to the pyramid?\n");
        scanf(" %c", &save_pls);
        int next_free_position = next_free(pyra->full_house[current_player], 1);
        if(next_free_position != -1 && (save_pls == 'y' || save_pls == 'Y')) {
            pyra->full_house[current_player][next_free_position] = 1;
            saved = true;
        } else {
            printf("You can't write any more Full Houses! This row is already filled!\n");
        }
    }

    if (!saved && is_consecutive(player_throws[current_player])) {
        printf("You have a Straight, do you want to save it to the pyramid?\n");
        scanf(" %c", &save_pls);
        int next_free_position = next_free(pyra->straight[current_player], 1);
        if(next_free_position != -1 && (save_pls == 'y' || save_pls == 'Y')) {
            pyra->straight[current_player][next_free_position] = 1;
            saved = true;
        } else {
            printf("You can't write any more Straights! This row is already filled!\n");
        }
    }

    while(!saved) {
        printf("What do you want to save to the Pyramid?\nYou can save only once per round.\n");
        scanf(" %d", &save_this);

        if(save_this == 5 && save_singles[5] != 0) {
            int next_free_position = next_free(pyra->aces[current_player], 1);
            if(next_free_position != -1) {
                for(int i = 0; i < save_singles[save_this]; i++) {
                    if(next_free_position < 5) {
                        pyra->aces[next_free_position][current_player] = 1;
                        next_free_position++;
                    } else {
                        printf("You have filled up the Aces row!\n");
                        break;
                    }
                }
                saved = true;
            } else {
                printf("You can't write any more Aces! This row is already filled!\n");
            }
        } else if (save_this == 4 && save_singles[4] != 0) {
            int next_free_position = next_free(pyra->kings[current_player], 1);
            if(next_free_position != -1) {
                for(int i = 0; i < save_singles[save_this]; i++) {
                    if(next_free_position < 6) {
                        pyra->kings[next_free_position][current_player] = 1;
                        next_free_position++;
                    } else {
                        printf("You have filled up the Kings row!\n");
                        break;
                    }
                }
                saved = true;
            } else {
                printf("You can't write any more Kings! This row is already filled!\n");
            }
        } else if (save_this == 3 && save_singles[3] != 0) {
            int next_free_position = next_free(pyra->queens[current_player], 1);
            if(next_free_position != -1) {
                for(int i = 0; i < save_singles[save_this]; i++) {
                    if(next_free_position < 7) {
                        pyra->queens[next_free_position][current_player] = 1;
                        next_free_position++;
                    } else {
                        printf("You have filled up the Queens row!\n");
                        break;
                    }
                }
                saved = true;
            } else {
                printf("You can't write any more Queens! This row is already filled!\n");
            }
        } else if (save_this == 2 && save_singles[2] != 0) {
            int next_free_position = next_free(pyra->jacks[current_player], 1);
            if(next_free_position != -1) {
                for(int i = 0; i < save_singles[save_this]; i++) {
                    if(next_free_position < 8) {
                        pyra->jacks[next_free_position][current_player] = 1;
                        next_free_position++;
                    } else {
                        printf("You have filled up the Jacks row!\n");
                        break;
                    }
                }
                saved = true;
            } else {
                printf("You can't write any more Jacks! This row is already filled!\n");
            }
        } else if (save_this == 1 && save_singles[1] != 0) {
            int next_free_position = next_free(pyra->tens[current_player], 1);
            if(next_free_position != -1) {
                for(int i = 0; i < save_singles[save_this]; i++) {
                    if(next_free_position < 9) {
                        pyra->tens[next_free_position][current_player] = 1;
                        next_free_position++;
                    } else {
                        printf("You have filled up the Tens row!\n");
                        break;
                    }
                }
                saved = true;
            } else {
                printf("You can't write any more Tens! This row is already filled!\n");
            }
        } else if (save_this == 0 && save_singles[0] != 0) {
            int next_free_position = next_free(pyra->nines[current_player], 1);
            if(next_free_position != -1) {
                for(int i = 0; i < save_singles[save_this]; i++) {
                    if(next_free_position < 10) {
                        pyra->nines[next_free_position][current_player] = 1;
                        next_free_position++;
                    } else {
                        printf("You have filled up the Nines row!\n");
                        break;
                    }
                }
                saved = true;
            } else {
                printf("You can't write any more Nines! This row is already filled!\n");
            }
        } else {
            printf("You do not have any amount of this card! Pick again.");
        }
    }
}

void print_pyramid(struct pyramid *pyra) {
    printf("%12s", "Grande: ");
    pyra->grande[current_player][0] == 1 ? printf("X") : printf("_");
    printf("\n");

    printf("%12s", "Poker: ");
    for(int i = 0; i < 2; i++) {
        if(pyra->poker[current_player][i] == 1) {
            printf("X");
        } else {
            printf("_");
        }
    }
    printf("\n");

    printf("%12s", "Full House: ");
    for(int i = 0; i < 3; i++) {
        if(pyra->full_house[current_player][i] == 1) {
            printf("X");
        } else {
            printf("_");
        }
    }
    printf("\n");

    printf("%12s", "Straight: ");
    for(int i = 0; i < 4; i++) {
        if(pyra->straight[current_player][i] == 1) {
            printf("X");
        } else {
            printf("_");
        }
    }
    printf("\n");

    printf("%12s", "Aces: ");
    for(int i = 0; i < 5; i++) {
        if(pyra->aces[current_player][i] == 1) {
            printf("X");
        } else {
            printf("_");
        }
    }
    printf("\n");

    printf("%12s", "Kings: ");
    for(int i = 0; i < 6; i++) {
        if(pyra->kings[current_player][i] == 1) {
            printf("X");
        } else {
            printf("_");
        }
    }
    printf("\n");

    printf("%12s", "Queens: ");
    for(int i = 0; i < 7; i++) {
        if(pyra->queens[current_player][i] == 1) {
            printf("X");
        } else {
            printf("_");
        }
    }
    printf("\n");

    printf("%12s", "Jacks: ");
    for(int i = 0; i < 8; i++) {
        if(pyra->jacks[current_player][i] == 1) {
            printf("X");
        } else {
            printf("_");
        }
    }
    printf("\n");

    printf("%12s", "Tens: ");
    for(int i = 0; i < 9; i++) {
        if(pyra->tens[current_player][i] == 1) {
            printf("X");
        } else {
            printf("_");
        }
    }
    printf("\n");

    printf("%12s", "Nines: ");
    for(int i = 0; i < 10; i++) {
        if(pyra->nines[current_player][i] == 1) {
            printf("X");
        } else {
            printf("_");
        }
    }
    printf("\n");

}

bool check_pyramid(struct pyramid *pyra) {
    return !(pyra->grande[current_player][0] == 0 ||
            pyra->poker[current_player][1] == 0 ||
            pyra->full_house[current_player][2] == 0 ||
            pyra->straight[current_player][3] == 0 ||
            pyra->aces[current_player][4] == 0 ||
            pyra->kings[current_player][5] == 0 ||
            pyra->queens[current_player][6] == 0 ||
            pyra->jacks[current_player][7] == 0 ||
            pyra->tens[current_player][8] == 0 ||
            pyra->nines[current_player][9] == 0);
}

//
// Created by Faktora on 26-Feb-20.
//

#ifndef POKERDICE_BASE_FUNCTIONS_H
#define POKERDICE_BASE_FUNCTIONS_H

/*function using keep(amount of dices to keep) and array_keep (array with the elements the user wants to save)
 * then re-rolls the rest of the dice that are not supposed to be kept*/
void roll_dice(int keep, int *array_keep);

/*function used to print out the rolled dices*/
void translate(const int array[]);

/*function takes the dice we keep, how many rolls did the player do and if he re-rolled already
 * if it is first roll, we call function roll and then asks the user how many and which dices he wants to save */
bool keep_dice(int keep, int *amount_of_rolls, bool *has_rerolled);

/*function using the re-rolled boolean to check for extra points
 * just prints and then saves the points each player made*/
bool calculate_points(bool *has_rerolled);

/*game switching for other mods to come takes user input game_choice and whether the player has rerolled
* used to call the game type and its corresponding pointing system*/
bool is_game_finished(int game_choice, bool *has_rerolled, int array_points[][2]);

#endif //POKERDICE_BASE_FUNCTIONS_H

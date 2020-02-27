// Created by Nedelin Todorov on 26-Feb-20.


///
/// \file base_functions.h
/// \brief universal game functions used in all of the gaming modes
///

#ifndef POKERDICE_BASE_FUNCTIONS_H
#define POKERDICE_BASE_FUNCTIONS_H


/*function using keep(amount of dices to keep) and array_keep (array with the elements the user wants to save)
 * then re-rolls the rest of the dice that are not supposed to be kept*/
/// \fn roll_dice - takes int keep for amount of dices to keep and array for the chosen dices to save to, also
/// re-rolls all of the unsaved dices
void roll_dice(int keep, int *array_keep);

/*function used to print out the rolled dices*/
/// \fn translate - takes the array with current throws and prints it to a understandable for the user text
void translate(const int array[]);

/*function takes the dice we keep, how many rolls did the player do and if he re-rolled already
 * if it is first roll, we call function roll and then asks the user how many and which dices he wants to save */
/// \fn keep_dice - takes the amount of dices to keep, how many rolls have the user already made and a boolean
/// if rolls = 3, no more re-rolls, if has_rerolled = true, lesser points for combination roll
bool keep_dice(int keep, int *amount_of_rolls, bool *has_rerolled);

/*function using the re-rolled boolean to check for extra points
 * just prints and then saves the points each player made*/
/// \fn calculate_points - takes one boolean argument to check for re-rolls, sums player points
bool calculate_points(bool *has_rerolled);

/*game switching for other mods to come takes user input game_choice and whether the player has rerolled
* used to call the game type and its corresponding pointing system*/
/// \fn is_game_finished - takes players game choice, if he re-rolled and players array with points,
/// at the end of each round checks if the player reached the needed amount of points to win
bool is_game_finished(int game_choice, bool *has_rerolled, int array_points[][2]);

#endif //POKERDICE_BASE_FUNCTIONS_H

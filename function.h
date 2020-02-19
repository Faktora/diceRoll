/*takes the array and sorts it by power in search for poker and full house*/
void is_highest(const int array[]);

/*function used to print out the rolled dices*/
void translate(const int array[]);

/*function takes the dice we keep, how many rolls did the player do and if he re-rolled already
 * if it is first roll, we call function roll and then asks the user how many and which dices he wants to save */
bool keep_dice(int keep, int *amount_of_rolls, bool *has_rerolled);

/*function using the re-rolled boolean to check for extra points
 * just prints and then saves the points each player made*/
bool calculate_points(bool *has_rerolled);

/* helping functions for is_consecutive, they find the min and max number in the array player_throws */
int is_min(const int player_throws[], int array_throws_length);//finds the min element in the array
int is_max(const int player_throws[], int array_throws_length);//finds the max element in the array

/*func takes array with player_throws and the length of it
 * calls the is_max and is_min (check their comments for explanation)
 * after getting the min and max goes thru player_throws to find if all numbers are consecutive*/
bool is_consecutive(int player_throws[], int array_throws_length);

/*takes the array with player throws and the length of it as arguments
 * then goes thru the array looking if all the elements are == 5 (Aces)*/
bool is_grande(const int grande_array[], int array_length);

/*game switching for other mods to come takes user input game_choice and whether the player has rerolled
 * used to call the game type and its corresponding pointing system*/
bool is_game_finished(int game_choice, bool *has_rerolled, int array_points[][2]);

/*func with no arguments, gets called by is_highest to check if there is poker in the current throw*/
bool is_poker();

/*func with no arguments, gets called by is_highest to check if there is fullhouse in the current throw*/
bool is_fullhouse();

/*function using keep(amount of dices to keep) and array_keep (array with the elements the user wants to save)
 * then re-rolls the rest of the dice that are not supposed to be kept*/
void roll_dice(int keep, int *array_keep);

void table_point_summary(int array_points[][2]);

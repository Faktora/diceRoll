int playerRolls[2][LENGTH];
int playerPoints[2];
int currentPlayer = 1;


void sortByPower(const int array[]);
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
void countPoints(int *rollsAmount);

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

bool pokerChecker();

bool fullHouseChecker();

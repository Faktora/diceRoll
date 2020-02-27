# Projekt Poker Dice, from Nedelin Todorov
Poker Dice, from Nedelin Todorov, ic19b110, BIC1

__Compile__:

Project is compiled as usual, you need to include all .c files.

("gcc -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter main.c -o dice_roll")

__Running__:

To run the program you have to enter is the name.

ATTENTION! Make sure you input the name correctly and only use uppercase/lowercase letters, 
numbers, '_', '-' and '.' appear in the file name.

 \verbatim
 
__Completed Tasks__:

== Task Specification ==

Implement a simple poker dice link:https://de.wikipedia.org/wiki/Escalero[game]. Two players roll 5 dices maximum 3 times per round and the points are summarized. First one to reach 100 points wins.

. **Main Task (40 points)**
  * Implement a program which allows two human players to play poker dice.
  * The game follows this principle:
  ** Player rolls 5 dice (rand function)
  ** Poker dice values are shown (9, 10, Jack, Queen, King and Ace)
  ** Player chooses 0 to 5 dice that he wants to keep.
     Keeping all of them ends the player's turn.
     The other dice are rolled again.
  ** The player is allowed to select and re-throw the respective dice two times for a total number of up to three throws per turn.
     The values after the last throw count.
  * For each round the points are counted:
  ** 9s count one point
  ** 10s count two points
  ** Jacks count three points
  ** Queens count four points
  ** Kings count five points
  ** Aces count six points


. **Task (15 points)**
+
  * Add additional point counting:
    ** Straight (the combination of 9, 10, J, Q, K or 10, J, Q, K, A) counts 20 points or 25 if done on the first roll
  ** Full House (three equal dice values + two other equal dice values e.g. 9+9+9+J+J) counts 30 points or 35 if done on the first roll
  ** Poker (four equal dice values e.g. Q+Q+Q+Q) counts 40 points or 45 if done on the first roll
  ** Grande (five equal dice values e.g. A+A+A+A+A) counts 50 points or 80 if done on the first roll

. **Task (15 points)**
+
  * Implement a counting table instead of the summary for the points.
In the table only one row value can be written per round.
  * Player has to choose which dice they want to write to the table after they finished their round.
  * Winner is again who reaches 100 Points.
+
.Example of a counting table<br>

|===================================|
| Deck       || Player 1 | Player 2 |
|===================================|
|===================================|
| 9s        0||  	     |          |
|===================================|
| 10s       1||  	     |          |
|===================================|
| Jacks     2||  	     |          |
|===================================|
| Queens    3||  	     |          |
|===================================|
| Kings     4||  	     |          |
|===================================|
| Aces      5||  	     |          |
|===================================|
| Straight  6||  	     |          |
|===================================|
| Full House7||  	     |          |
|===================================|
| Poker     8||  	     |          |
|===================================|
| Grande    9||  	     |          |
|===================================|
|===================================|
| **Sum**  10||  	     |          |
|===================================|


  . **Task (20 points)**
+
  * Expand the counting table game mode for a special mode called "can must".
    The goal is to get each of the decks described above once.
  * During the can part each player can choose their row they want to write the values to.
  * A row of values can only be written once.
  * When the dice values can not be written any more the player has to choose a row which he will put a zero result into.
  * When all rows are filled (after 10 rounds) the second part starts.
  * This part starts with 9s where all Players have to reach as much 9s as possible. This value is then counted into the 9 row.
  * Next round will be 10s, then Jack, Queen, ...
  * Last round is Grande
  * After this part is finished all points are summarized and the player with most points wins.

. **Task (20 points)**
+
  * Implement a game mode called pyramid
  * The pyramid has one cell for a grande, two cells for poker, three cells for Full House etc, up to 10 cells for 9s
  * Gameplay is defined by these rules:
  ** The Player can choose which dice should be counted into the pyramid
  ** but only one row at a time e.g the dice show 9+9+J+Q+A then the player can select the two 9s, one Jack, one Queen or one Ace to be written into the pyramid.
  ** In the pyramid each cell is only marked as finished. If no value can be written then the round is not counted for this player.
  ** When a Player finishes all cells he/she win the game.


. **Task (25 points)**
+
  * Extend the program to use ncurses.
  Description how to use ncurses can be found link:https://embsys.technikum-wien.at/mio/bic/1/prg/download/ncurses.pdf[here].
  * Build the Playfield, Point summary or table or pyramid on the screen and only overwrite the changed parts.


== Example Execution:

 
----
$ ./poker_dice
Choose Game Mode:
1) Normal point summary
2) Table point summary
3) Can Must game
4) Pyramid
your choice:
4
Round 1 Player 1 Roll 1:
Your dices are: 9 J Q A A
Please select dices to keep:
2 3 4
Roll 2
Your dices are: J Q Q K A
Please select dices to keep:
1 2 4 5
Last Roll
Your dices are: 10 J Q K A
You have a straight. Do you want to write it. (Y/N)?
Y

Pyramid for Player 1:
G _
P __
F ___
S X___
A _____
K ______
Q _______
J ________
10_________
9 __________

Round 1 Player 2 Roll 1:
Your dices are: 9 9 9 9 A
Congratulation you roll a Poker. Do you want to write it. (Y/N)?
N
Please select dices to keep:
1 2 3 4
Roll 2
Your dices are: 9 9 9 9 9
Congratulation you roll a Grande. Do you want to write it. (Y/N)?
N
Please select dices to write
1 2 3 4 5

Pyramid for Player 2:
G _
P __
F ___
S ____
A _____
K ______
Q _______
J ________
10_________
9 XXXXX_____

Round 2 Player 1 Roll 1:

----

 \endverbatim
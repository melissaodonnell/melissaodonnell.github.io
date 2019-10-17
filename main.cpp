//Melissa Caviglia O'Donnell
//IT-312 Q3262
//7-1 Final Project Submission: Dice Game (Farkle)
//Due Feb. 25, 2018
//
// finalFarkle.cpp : Farkle is a game that uses 6 dice.
//The goal is to strategically decide how to score your
//own dice according to the point combinations laid out
//in the rules to be the first player to reacher 10,000
//points.
//

#include "windows.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string player1Name;  //Variables to store player names
string player2Name;

int sumPlayer1 = 0;  //Variables to declare a winner
int sumPlayer2 = 0;

int player1Score = 0;  //Variables to track players' score
int player2Score = 0;

void playerNames(){

    //Player name section:

    cout << "Input player 1's name: " << endl;  //Ask user for player names.
    cin >> player1Name;

    cout << "\nInput player 2's name: " << endl;  //Ask user for player names.
    cin >> player2Name;
}

void farkleRules() {  //Farkle rules section

    string s;
    ifstream rulesFile;  //Identify variable with fstream.
    rulesFile.open("farkleGameRules.txt");  //My created text file with rules.

    if (rulesFile.is_open())
    {
        while (getline(rulesFile, s))  //Read text file line by line.
        {
            cout << s << endl;  //Print text file contents.
        }
        rulesFile.close();
    }

    else  //Check for error.
    {
        cerr << "Unable to open file farkleGameRules.txt" << endl;

    }

    Sleep(2000);
}

string checkWinner() {
    if ((sumPlayer1 >= 10000) && (sumPlayer1 > sumPlayer2))  //Declaring Player 1 winner, unless Player 2 has a higher score at the end of the last round played.
    {
        cout << "Congratulations Player 1, you win!" << endl;
        return "\n\n Player 1 wins!";
    }
    else if (sumPlayer2 >= 10000)  //Declaring Player 2 winner
    {
        cout << "Congratulations Player 2, you win!" << endl;
        return "\n\n Player 2 wins!";
    }
    else
    {
        return "Final score error.";  //Tracking a scoring error.
    }
}

int rollDie(){
    int roll = (rand() % 6) + 1;
    return roll;
}

bool scoringRoll(int diceArray[], int size){

    int playerDice[6] = {};
    for (int j = 0; j < size; ++j) {
        playerDice[j] = diceArray[j];
    }

    //All combinations of dice that give points

    if ((playerDice[0] == 1) || (playerDice[0] == 5) || (playerDice[1] == 1) || (playerDice[1] == 5) || (playerDice[2] == 1) || (playerDice[2] == 5)
        || (playerDice[3] == 1) || (playerDice[3] == 5) || (playerDice[4] == 1) || (playerDice[4] == 5) || (playerDice[5] == 1) || (playerDice[5] == 5)
        || (playerDice[0] == playerDice[1] && playerDice[1] == playerDice[2]) || (playerDice[0] == playerDice[1] && playerDice[1] == playerDice[3])
        || (playerDice[0] == playerDice[1] && playerDice[1] == playerDice[4]) || (playerDice[0] == playerDice[1] && playerDice[1] == playerDice[5])
        || (playerDice[0] == playerDice[2] && playerDice[2] == playerDice[3]) || (playerDice[0] == playerDice[2] && playerDice[2] == playerDice[4])
        || (playerDice[0] == playerDice[2] && playerDice[2] == playerDice[5]) || (playerDice[0] == playerDice[3] && playerDice[3] == playerDice[4])
        || (playerDice[0] == playerDice[3] && playerDice[3] == playerDice[5]) || (playerDice[0] == playerDice[4] && playerDice[4] == playerDice[5])
        || (playerDice[1] == playerDice[2] && playerDice[2] == playerDice[3]) || (playerDice[1] == playerDice[2] && playerDice[2] == playerDice[4])
        || (playerDice[1] == playerDice[2] && playerDice[2] == playerDice[5]) || (playerDice[1] == playerDice[3] && playerDice[3] == playerDice[4])
        || (playerDice[1] == playerDice[3] && playerDice[3] == playerDice[5]) || (playerDice[1] == playerDice[4] && playerDice[4] == playerDice[5])
        || (playerDice[2] == playerDice[3] && playerDice[3] == playerDice[4]) || (playerDice[2] == playerDice[3] && playerDice[3] == playerDice[5])
        || (playerDice[2] == playerDice[4] && playerDice[4] == playerDice[5]) || (playerDice[3] == playerDice[4] && playerDice[4] == playerDice[5])) {
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int scoreRoll(int diceArray[], int size){

    int specifiedPlayerScore = 0;

    int playerDice[6] = {};
    for (int j = 0; j <= size; ++j) {
        playerDice[j] = diceArray[j];
    }

    //3 of a kind scoring matching to dice 1.
    if ((playerDice[0] == playerDice[1] && playerDice[1] == playerDice[2]) || (playerDice[0] == playerDice[1] && playerDice[1] == playerDice[3])
        || (playerDice[0] == playerDice[1] && playerDice[1] == playerDice[4]) || (playerDice[0] == playerDice[1] && playerDice[1] == playerDice[5])
        || (playerDice[0] == playerDice[2] && playerDice[2] == playerDice[3]) || (playerDice[0] == playerDice[2] && playerDice[2] == playerDice[4])
        || (playerDice[0] == playerDice[2] && playerDice[2] == playerDice[5]) || (playerDice[0] == playerDice[3] && playerDice[3] == playerDice[4])
        || (playerDice[0] == playerDice[3] && playerDice[3] == playerDice[5]) || (playerDice[0] == playerDice[4] && playerDice[4] == playerDice[5])
            )
    {
        if (playerDice[0] == 1)
        {
            specifiedPlayerScore += 700;  //1000 minus 300 points that will be given for the '3' individual 1's below.
        }
        else if (playerDice[0] == 5)
        {
            specifiedPlayerScore += 350;  //500 minus 150 points that will be given for the '3' individual 5's below.
        }
        else
        {
            specifiedPlayerScore += playerDice[1] * 100;
        }
    }
    //3 of a kind scoring matching to dice 2.
    if ((playerDice[1] == playerDice[2] && playerDice[2] == playerDice[3]) || (playerDice[1] == playerDice[2] && playerDice[2] == playerDice[4])
        || (playerDice[1] == playerDice[2] && playerDice[2] == playerDice[5]) || (playerDice[1] == playerDice[3] && playerDice[3] == playerDice[4])
        || (playerDice[1] == playerDice[3] && playerDice[3] == playerDice[5]) || (playerDice[1] == playerDice[4] && playerDice[4] == playerDice[5]))
    {
        if (playerDice[1] == 1)
        {
            specifiedPlayerScore += 700;  //1000 minus 300 points that will be given for the '3' individual 1's below.
        }
        else if (playerDice[1] == 5)
        {
            specifiedPlayerScore += 350;  //500 minus 150 points that will be given for the '3' individual 5's below.
        }
        else {
            specifiedPlayerScore += playerDice[1] * 100;
        }
    }
    //3 of a kind scoring matching to dice 3.
    if ((playerDice[2] == playerDice[3] && playerDice[3] == playerDice[4]) || (playerDice[2] == playerDice[3] && playerDice[3] == playerDice[5])
        || (playerDice[2] == playerDice[4] && playerDice[4] == playerDice[5]))
    {
        if (playerDice[2] == 1)
        {
            specifiedPlayerScore += 700;  //1000 minus 300 points that will be given for the '3' individual 1's below.
        }
        else if (playerDice[2] == 5)
        {
            specifiedPlayerScore += 350;  //500 minus 150 points that will be given for the '3' individual 5's below.
        }
        else
        {
            specifiedPlayerScore += playerDice[2] * 100;
        }
    }
    //3 of a kind scoring matching to dice 4.
    if (playerDice[3] == playerDice[4] && playerDice[4] == playerDice[5])
    {
        if (playerDice[3] == 1)
        {
            specifiedPlayerScore += 700;  //1000 minus 300 points that will be given for the '3' individual 1's below.
        }
        else if (playerDice[3] == 5)
        {
            specifiedPlayerScore += 350;  //500 minus 150 points that will be given for the '3' individual 5's below.
        }
        else
        {
            specifiedPlayerScore += playerDice[3] * 100;
        }
    }
    //Individual die scoring for 1's.
    for (int j = 0; j < 6; ++j)
    {
        if (playerDice[j] == 1) {
            specifiedPlayerScore += 100;
        }
    }
    //Individual die scoring for 5's.
    for (int j = 0; j < 6; ++j)
    {
        if (playerDice[j] == 5) {
            specifiedPlayerScore += 50;
        }
    }

    return specifiedPlayerScore;
}

int main() {

    cout << "Welcome to Farkle!" << endl << endl;  //Welcome statement

    playerNames();  //Get player names

    ofstream myfile;
    myfile.open("farkleGameScoreRecord.txt");  //Opening file for writing scores into.

    if (myfile.is_open()) {
        myfile << "Player Names:\t";  //Writing to file.

        //cin.ignore();

        myfile << player1Name << "\t";  //Writing names to file.
        myfile << player2Name << "\n";
    }
    else {
        cout << "Score card file did not open properly." << endl;
    }

    farkleRules();

    //Rolling Dice and Scoring:

    srand(time(0));  // Generate and seed a random number between 1 and 6

    int keepDie;

    int i = 0;  //i stands for round number (i + 1 for print statements).

    cout << "\n\n" << endl;

    while ((sumPlayer1 < 10000) && (sumPlayer2 < 10000)) {

        player1Score = 0;  //Reset variables to track players' score for each round.
        player2Score = 0;

        //Player One rolls:

        int player1Dice[6] = {};
        for (int j = 0; j < 6; ++j) {
            player1Dice[j] = rollDie();
        }

        cout << "Player 1:" << endl << endl;  //Player 1's roll.
        for (int j = 0; j < 6; ++j) {
            cout << "Die " << j + 1 << " rolled: " << player1Dice[j] << endl;
        }

        if (scoringRoll(player1Dice, 6)) {
            for (int j = 0; j < 6; ++j) {
                cout << "Would you like to keep die " << j + 1 << "? Press 1 for yes or 2 for no." << endl;  //Asking user to keep dice
                cin >> keepDie;

                if (keepDie == 2) {
                    player1Dice[j] = rollDie();
                }
            }

            cout << "Your final dice are: " << endl; //Final dice displayed.
            for (int j = 0; j < 6; ++j) {
                cout << player1Dice[j] << " " << endl;
            }
            cout << "\n" << endl;

            //Scoring for Player 1:
            player1Score = scoreRoll(player1Dice, 6);

            //Printing out round number and score.
            cout << "Round " << (i + 1) << " Score for Player 1: " << player1Score << endl << endl;

            //Writing scores to farkleGameScoreRecord.txt
            myfile << "Round " << (i + 1) << " score:\t" << player1Score << "\t";

            sumPlayer1 += player1Score;

        } else {
            cout << "FARKLE!" << endl << endl;  //No scoring dice in a roll and Farkle gives no points for the round.
        }

        Sleep(1000);  //For a small break in between player rolls.

        //Player Two rolls:

        int player2Dice[6] = {};
        for (int j = 0; j < 6; ++j) {
            player2Dice[j] = rollDie();
        }

        cout << "Player 2:\n" << endl << endl;  //Player 2's roll.
        for (int j = 0; j < 6; ++j) {
            cout << "Die " << j + 1 << " rolled: " << player2Dice[j] << endl;
        }

        if (scoringRoll(player2Dice, 6)) {
            for (int j = 0; j < 6; ++j) {
                cout << "Would you like to keep die " << j + 1 << "? Press 1 for yes or 2 for no." << endl;  //Asking user to keep dice
                cin >> keepDie;

                if (keepDie == 2) {
                    player2Dice[j] = rollDie();
                }
            }

            cout << "Your final dice are: " << endl; //Final dice displayed.
            for (int j = 0; j < 6; ++j) {
                cout << player2Dice[j] << " " << endl;
            }
            cout << "\n" << endl;

            //Scoring for Player 2:
            player2Score = scoreRoll(player2Dice, 6);

            //Printing out round number and score.
            cout << "Round " << (i + 1) << " Score for Player 2: " << player2Score << endl << endl;

            //Writing scores to farkleGameScoreRecord.txt
            myfile << player2Score << "\n";

            sumPlayer2 += player2Score;

        }
        else {
            cout << "FARKLE!" << endl << endl;  //No scoring dice in a roll and Farkle gives no points for the round.
        }
        ++i;

        Sleep(1000);  //For a small break in between player rolls.

    }
    myfile << "\nFinal Scores:\t" << sumPlayer1 << "\t" << sumPlayer2 << "\n";
    myfile << checkWinner() << endl;

    myfile.close();  //Closing file

    cout << "\n A new file has been written. \n\n";  //Print statement to show file has been written successfully

    return 0;
}

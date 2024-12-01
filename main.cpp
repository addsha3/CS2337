// main.cpp : Defines the entry point for the console application.
// Dice Game Simulation - Casino Game
// Date: 2024-11-15
// Author: Shashi Addaguduru
// Purpose: Simulate a dice game where the user bets on the outcome of rolling two dice.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function prototypes
unsigned AskForInitialStakeAmount();
unsigned AskForBet(unsigned& stake);
unsigned RollDemBones(unsigned& rollCount);
void EvaluateRoll(unsigned diceRollResults, unsigned& rollCount, unsigned& stake, unsigned bet);
bool PointRollDemBones(unsigned point, unsigned& rollCount);

int main() {
    unsigned stake = AskForInitialStakeAmount();
    unsigned bet;
    unsigned rollCount = 0;
    unsigned diceRollResults;

    do {
        bet = AskForBet(stake);
        if (bet == 0) {
            cout << "You have chosen to end the game." << endl;
            break;
        }

        diceRollResults = RollDemBones(rollCount);
        EvaluateRoll(diceRollResults, rollCount, stake, bet);
    } while (stake > 0);

    if (stake == 0) {
        cout << "You are out of money. Game over." << endl;
    }

    cout << "Total rolls: " << rollCount << endl;
    cout << "Final stake amount: $" << stake << endl;

    cout << "Press enter key once or twice to end ... ";
    cin.ignore();
    cin.get();

    return 0;
}

/*
 * AskForInitialStakeAmount
 * Prompts user for initial stake amount (> 0).
 */
unsigned AskForInitialStakeAmount() {
    unsigned stake;
    while (true) {
        cout << "What is your stake amount ? ";
        cin >> stake;
        if (stake > 0) {
            break;
        } else {
            cout << "You must enter a 0 or positive amount of money to bet with. Try again!" << endl;
        }
    }
    return stake;
}

/*
 * AskForBet
 * Prompts user for bet amount, ensures it's valid.
 */
unsigned AskForBet(unsigned& stake) {
    unsigned bet;
    while (true) {
        cout << "Current Stake Amount : " << stake << endl;
        cout << "What will you bet ? ";
        cin >> bet;
        if (bet > stake) {
            cout << "Bet amount cannot exceed the current stake. Try again!" << endl;
        } else if (bet < 0) {
            cout << "Bet amount cannot be negative. Try again!" << endl;
        } else {
            break;
        }
    }
    return bet;
}

/*
 * RollDemBones
 * Rolls two dice and returns their sum.
 */
unsigned RollDemBones(unsigned& rollCount) {
    cout << "Press enter key once or twice to throw the dice ...";
    cin.ignore();
    cin.get();

    rollCount++;
    srand(clock());
    unsigned die1 = rand() % 6 + 1;
    unsigned die2 = rand() % 6 + 1;

    cout << "Die 01 is " << die1 << endl;
    cout << "Die 02 is " << die2 << endl;
    cout << "The dice throw results : " << (die1 + die2) << " !" << endl;

    return die1 + die2;
}

/*
 * EvaluateRoll
 * Evaluates the result of a roll and updates stake based on win/loss.
 */
void EvaluateRoll(unsigned diceRollResults, unsigned& rollCount, unsigned& stake, unsigned bet) {
    if (diceRollResults == 7 || diceRollResults == 11) {
        cout << "You rolled a " << diceRollResults << ". You win!" << endl;
        stake += bet;
    } else if (diceRollResults == 2 || diceRollResults == 3 || diceRollResults == 12) {
        cout << "You rolled a " << diceRollResults << ". You lose!" << endl;
        stake -= bet;
    } else {
        cout << "The point is " << diceRollResults << endl;
        cout << "Throw em again and hope that luck is on your side!" << endl;
        if (PointRollDemBones(diceRollResults, rollCount)) {
            cout << "You rolled the point! You win!" << endl;
            stake += bet;
        } else {
            cout << "You rolled a 7. You lose!" << endl;
            stake -= bet;
        }
    }
    cout << "New stake amount: $" << stake << endl;
}

/*
 * PointRollDemBones
 * Rolls until the point or a 7 is rolled.
 */
bool PointRollDemBones(unsigned point, unsigned& rollCount) {
    unsigned pointRoll;
    while (true) {
        pointRoll = RollDemBones(rollCount);
        cout << "You rolled a " << pointRoll << endl;
        if (pointRoll == point) {
            return true;
        } else if (pointRoll == 7) {
            return false;
        }
    }
}

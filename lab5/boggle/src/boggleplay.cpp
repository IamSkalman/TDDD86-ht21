// Elis Öhman(elioh505) & Daniel Wendin(danwe681)
// boggleplay.cpp controls how the game is played and all input and output.
// playOneGame() uses a boggle object to get all functions to update the game state
// and get information about it. 

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"

// Asks for input and checks if the input is valid until returning the input
string getBoardStringInput(const int& NUM_CUBES);

// Outputs human words and score. Asks for word guesses and updates Boggle if guess is valid
void humanTurn(Boggle& boggle);

// Finds all remaining words and outputs them as well as the computers' score
void computerTurn(Boggle& boggle);

/*
 * Plays one game of Boggle using the given boggle game state object.
 */

void playOneGame(Boggle& boggle) {
    clearConsole();
    if (!yesOrNo("Do you want to generate a random board? (Y/N) ")) {
        string input = getBoardStringInput(boggle.getNumOfCubes());
        boggle.generateChosenBoard(input);
    }
    else {
        boggle.randomizeBoard();
    }
    cout << endl << "It's your turn now!" << endl;
    cout << boggle.getBoardToPrint();

    humanTurn(boggle);

    computerTurn(boggle);

    if (boggle.getComputerPoints() > boggle.getHumanPoints()){
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
    }
    else if (boggle.getComputerPoints() <= boggle.getHumanPoints()){
        cout << "You win! Somehow...";
    }
    boggle.reset();
}

string getBoardStringInput(const int& NUM_CUBES){
    cout << endl << "Input a string which is 16 chars long, every char belonging to A-Z: ";
    string input;
    bool validInput = false;
    while (!validInput){
        getline(cin, input);
        if (input.size() == NUM_CUBES){
            validInput = true;
            for (int i = 0; i < NUM_CUBES; i++){
                if (!isalpha(input[i])){ // checks if input element is not in the alphabet
                    validInput = false;
                    cout << "Try again!" << endl;
                    break;
                }
            }
        }
        else {
            cout << "Try again!" << endl;
        }
    }
    input = trim(toUpperCase(input));
    return input;
}

void humanTurn(Boggle& boggle){
    string wordGuess;
    while (true){
        set<string> humanWords = boggle.getHumanWords();
        cout << endl << "Your words (" << humanWords.size() << "): { ";
        for (string hWord : humanWords){
            cout << hWord << " ";
        }
        cout << "}" << endl;
        cout << "Your score: " << boggle.getHumanPoints() << endl;
        cout << "Type a word (or press Enter to end your turn): ";
        getline(cin, wordGuess);
        wordGuess = trim(toUpperCase(wordGuess));
        if (wordGuess.size() < 1){
	    // empty answer ends turn
            break;
        }
        if (boggle.isWordGuessValid(wordGuess)){
            cout << "You found a new word! " << wordGuess << endl;
            boggle.addHumanWordandPoints(wordGuess);
        }
    }
}

void computerTurn(Boggle& boggle){
    cout << endl << "It's my turn!" << endl;
    boggle.findAllRemainingWords();
    set<string> computerWords = boggle.getComputerWords();

    cout << "My words (" << computerWords.size() << "): { ";
    for (string cWord : computerWords){
        cout << cWord << " ";
    }
    cout << "}" << endl;
    cout << "My score: " << boggle.getComputerPoints() << endl;
}
/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}

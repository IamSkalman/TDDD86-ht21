// Elis Öhman (elioh505) & Daniel Wendin (danwe681)
// Header file for Boggle. Boggle handles the game state and the algorithms used by the game,
// also the rules of the game as what words is accepted depending on MIN_WORD_LENGTH and
// what Lexicon of words is used

#ifndef _boggle_h
#define _boggle_h


#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "grid.h"
#include "lexicon.h"

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    // Constructor
    Boggle();

    // Shuffles the cubes and then randomly chooses a character from each cube and sets the board
    void randomizeBoard();

    // Sets each character in boardChars in the board
    void generateChosenBoard(string& boardChars);

    // Returns a string which is structured to showcase the board when printed
    string getBoardToPrint();

    // Checks if a word is valid length, an english word, not guessed before and that it exists in the board
    bool isWordGuessValid(string& wordGuess);

    // Attempts to build the postfix of wordGuess and then returns either an equal word to wordGuess or not
    string getWordInBoard(string wGuessSubString, const pair<int, int>& cubePos);

    // Calls in findAllPostfix for every single character in the board
    void findAllRemainingWords();

    // Finds every postfix and therefore every word which gets saved in computerWords as well as adding points saved in computerPoints
    void findAllPostfix(string firstLetter, const pair<int, int>& firstLetterPos);

    // Adds word to humanWords and adds points to humanPoints
    void addHumanWordandPoints(string& correctWord);

    // Resets points and saved word guesses
    void reset();

    int getHumanPoints();
    int getComputerPoints();
    set<string> getHumanWords();
    set<string> getComputerWords();
    int getNumOfCubes();

private:
    Grid<char> board;
    const Lexicon ENGLISH_WORDS = Lexicon(DICTIONARY_FILE);
    set<string> humanWords;
    set<string> computerWords;
    int humanPoints = 0;
    int computerPoints = 0;
    set<pair<int, int>> markedCubes;

};

#endif

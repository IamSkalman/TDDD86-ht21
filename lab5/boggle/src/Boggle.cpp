// Elis Öhman (elioh505) & Daniel Wendin (danwe681)
// Boggle.cpp has all the code to initialize, get and update the game state,
// which includes the CUBES, board, words and points

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include <vector>
#include "grid.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
static const int POINT_DEDUCTION = 3;


Boggle::Boggle(){
     board = Grid<char>(BOARD_SIZE, BOARD_SIZE);
}

void Boggle::randomizeBoard(){
    shuffle(CUBES, NUM_CUBES); // shuffles the index of all the elements in CUBES
    int arrayIndex = 0;
    // loops through all positions in the board
    for (int row = 0; row < board.nRows; row++){
        for (int column = 0; column < board.nCols; column++){
            int randomIndex = randomInteger(0, CUBE_SIDES - 1);
            board.set(row, column, CUBES[arrayIndex][randomIndex]); // random letter from consecutive cube is added to board
            arrayIndex++;
        }
    }
};

void Boggle::generateChosenBoard(string& boardChars){
    int stringIndex = 0;
    // loops through all positions in the board
    for (int row = 0; row < board.nRows; row++){
        for (int column = 0; column < board.nCols; column++){
            board.set(row, column, boardChars[stringIndex]);
            stringIndex++;
        }
    }
}

string Boggle::getBoardToPrint(){
    string boardShowcase;
    int counter = 0; // counts every letter, resets when equal to BOARD_SIZE(width)

    // loops through all positions in the board
    for (int row = 0; row < board.nRows; row++){
        for (int column = 0; column < board.nCols; column++){
            counter++;
            boardShowcase.push_back(board.get(row, column));
            if (counter == BOARD_SIZE){
		// add line breaker when width of the board is reached
                boardShowcase.append("\n");
                counter = 0;
            }
        }
    }
    return boardShowcase;
}

bool Boggle::isWordGuessValid(string& wordGuess){
       int wordLength = wordGuess.size();
       if (wordLength < MIN_WORD_LENGTH || !ENGLISH_WORDS.contains(wordGuess) || humanWords.count(wordGuess)){
           return false;
       }
       string wordCheck;
       // loops through all positions in the board
       for (int row = 0; row < board.nRows; row++){
           for (int col = 0;  col < board.nCols; col++) {
               wordCheck = "";
               if(board.get(row, col) == wordGuess[0]){
                   pair<int, int> cubePos = make_pair(row,col);
                   markedCubes.insert(cubePos); // when a letter from a cube is used it is marked so it can't be reusedhen a letter from a cube is used it is marked so it can't be reused
                   wordCheck = wordGuess[0] + getWordInBoard(wordGuess.substr(1), cubePos);
                   markedCubes.erase(cubePos);
                   if(wordCheck == wordGuess){
                       return true;
                   }
               }
           }
       }
       return false;
}

string Boggle::getWordInBoard(string wGuessSubString, const pair<int, int>& cubePos){
    if(wGuessSubString.empty()){
        return "";
    }
    // loops through all 8 neighbour positions + cubePos
    for (int row = cubePos.first - 1;  row < cubePos.first + 2; row++) {
        for(int col = cubePos.second - 1; col < cubePos.second + 2; col++){
            if(board.inBounds(row, col) && !(row == cubePos.first && col == cubePos.second)){
                if(board.get(row, col) == wGuessSubString[0] && !markedCubes.count(make_pair(row, col))) {
                    pair<int, int> newCubePos = make_pair(row,col);
                    markedCubes.insert(newCubePos); // when a letter from a cube is used it is marked so it can't be reusedhen a letter from a cube is used it is marked so it can't be reused
                    string potentialWord = getWordInBoard(wGuessSubString.substr(1), newCubePos);
                    markedCubes.erase(newCubePos);
                    if(potentialWord == wGuessSubString.substr(1)){
                        return wGuessSubString[0] + potentialWord;
                    }
                }
            }
        }
    }
    return "";
}

void Boggle::findAllRemainingWords(){
    // loops through all positions in the board
    for (int row = 0; row < board.nRows; row++){
        for (int col = 0;  col < board.nCols; col++) {
            string firstLetter;
            firstLetter.assign(1, board.get(row, col));
            pair<int, int> firstLetterPos = make_pair(row, col);
            markedCubes.insert(firstLetterPos); // when a letter from a cube is used it is marked so it can't be reusedhen a letter from a cube is used it is marked so it can't be reused
            findAllPostfix(firstLetter, firstLetterPos);
            markedCubes.erase(firstLetterPos);
        }
    }
}

void Boggle::findAllPostfix(string prefix, const pair<int, int>& lastLetterPos){
    // loops through all 8 neighbour positions + lastLetterPos
    for (int row = lastLetterPos.first - 1;  row < lastLetterPos.first + 2; row++) {
        for (int col = lastLetterPos.second - 1; col < lastLetterPos.second + 2; col++){
            if  (board.inBounds(row, col) && !(row == lastLetterPos.first && col == lastLetterPos.second) && !(markedCubes.count(make_pair(row, col)))){
                pair<int, int> newLetterPos = make_pair(row, col);
                markedCubes.insert(newLetterPos); // when a letter from a cube is used it is marked so it can't be reusedhen a letter from a cube is used it is marked so it can't be reused
                string newPrefix = prefix + board.get(row, col);
                int newPrefixLength = newPrefix.size();
                if  (newPrefixLength >= MIN_WORD_LENGTH && ENGLISH_WORDS.contains(newPrefix) && !(humanWords.count(newPrefix)) && !(computerWords.count(newPrefix))){
                    computerWords.insert(newPrefix);
                    computerPoints += newPrefix.size() - POINT_DEDUCTION;
                }
                if (ENGLISH_WORDS.containsPrefix(newPrefix)) {
                    findAllPostfix(newPrefix, newLetterPos);
                }
                markedCubes.erase(newLetterPos);
            }
        }
    }
}

void Boggle::addHumanWordandPoints(string& correctWord){
    humanWords.insert(correctWord);
    humanPoints += correctWord.size() - POINT_DEDUCTION;
}

void Boggle::reset(){
    humanPoints = 0;
    computerPoints = 0;
    humanWords = set<string>();
    computerWords = set<string>();
}

int Boggle::getHumanPoints(){
    return humanPoints;
}

int Boggle::getComputerPoints(){
    return computerPoints;
}

set<string> Boggle::getHumanWords(){
   return humanWords;
}

set<string> Boggle::getComputerWords(){
   return computerWords;
}

int Boggle::getNumOfCubes(){
   return NUM_CUBES;
}

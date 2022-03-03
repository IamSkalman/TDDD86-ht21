#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
const string DICT_PATH = "di.txt";

void updateDictionary(const string& path, const int& wordLength, vector<string>& dictionary);
string generateSecretWord(const string& word, const unordered_set<char>& guessedLetters);
void printAlternativeWords(const vector<string>& alternativeWords);
void updatePartitions(const vector<string>& wordAlternatives, unordered_set<char>& guessedLetters, map<string, vector<string>>& partitions);
void updateWordAlternatives(const map<string, vector<string>>& partitions, vector<string>& wordAlternatives);
void updateUserInput(vector<string>& wordAlternatives, int& secretWordLength, int& guessesLeft, string& toPrintAlternatives);
void guessALetter(const string& currentWord, const int& guessesLeft, unordered_set<char>& guessedLetters,
                  const string& toPrintAlternatives, const vector<string>& wordAlternatives, char& guessedLetter);


// Runs the game while the string isGameActive == yes,
// starts by asking the player for a word length, amount of guesses etc.
// generates a currentWord and after that the player may continue to guess letters until
// guessesLeft is less than 1 (Loss) or the currentWord has no "empty" characters left in it (Win).
// The alternatives of words updates after every guess (correct or not) and chooses the smallest
// partition of words as the new alternatives.
// You may restart the game by answering the question with a yes or no after the game finishes.
int main() {
    cout << "Welcome to Hangman." << endl;

    int secretWordLength;
    vector<string> wordAlternatives;
    unordered_set<char> guessedLetters;
    string currentWord;
    char guessedLetter;
    string toPrintAlternatives;
    string isGameActive = "yes";


    while (isGameActive == "yes"){
        guessedLetter = ' ';
        guessedLetters = unordered_set<char>();
        wordAlternatives = vector<string> ();
        int guessesLeft = 0;

        updateUserInput(wordAlternatives, secretWordLength, guessesLeft, toPrintAlternatives);
        vector<string> dictionary;

        updateDictionary(DICT_PATH, secretWordLength, dictionary);
        currentWord = generateSecretWord(wordAlternatives[0], guessedLetters);

        while(guessesLeft > 0 && currentWord.find('-') != string::npos){

            guessALetter(currentWord, guessesLeft, guessedLetters, toPrintAlternatives, wordAlternatives, guessedLetter);
            map<string, vector<string>> partitions;
            updatePartitions(wordAlternatives, guessedLetters, partitions);

            updateWordAlternatives(partitions, wordAlternatives);

            if(wordAlternatives[0].find(guessedLetter) == string::npos){
                guessesLeft--;
            }

            currentWord = generateSecretWord(wordAlternatives[0], guessedLetters);
            if(currentWord.find('-') == string::npos){
                cout << "Congratulations You Guessed Right The Word Was: " <<  currentWord << endl;

                cout << endl << "Do you want to play again? (Answer yes or no)" << endl;
                cin >> isGameActive;

            }
            else if (guessesLeft < 1){
                cout << "To bad you didn't Guess the Right Word, the word was: " << wordAlternatives[0] << endl;
                cout << endl << "Do you want to play again? (Answer yes or no)" << endl;
                cin >> isGameActive;
            }
        }
    }


    return 0;
}


// Prints the SecretWord (----), the already guessedLetters, prints the alternative words (if chosen to do so)
// and finally asks for a new guess of a letter.
void guessALetter(const string& currentWord, const int& guessesLeft, unordered_set<char>& guessedLetters,
                  const string& toPrintAlternatives, const vector<string>& wordAlternatives, char& guessedLetter){

    string strGuessedLetters = "";
    cout <<  "Word: " << currentWord << endl;
    cout << "Guesses Left: " << guessesLeft << endl;
    for(const char letter: guessedLetters){
        strGuessedLetters += letter;
    }
    cout << "Guessed Letters: " << strGuessedLetters << endl;

    if (toPrintAlternatives == "yes"){
        cout << "Wordlist: " << endl;
        printAlternativeWords(wordAlternatives);
    }
    while (guessedLetters.count(guessedLetter) || isblank(guessedLetter)){
        cout << "Please guess a letter you haven't guessed before!" << endl;
        cin >> guessedLetter;
    }
    guessedLetters.insert(guessedLetter);

}

// Updates the variables used to start the game from user's inputs.
void updateUserInput(vector<string>& wordAlternatives, int& secretWordLength, int& guessesLeft,  string& toPrintAlternatives){
    while (wordAlternatives.empty()){
        cout << "Please enter the length of your secret word (try again if not valid): " << endl;
        cin >> secretWordLength;
        updateDictionary(DICT_PATH, secretWordLength, wordAlternatives);
    }

    while (guessesLeft < 1){
    cout << endl << "How many times shall you be able to guess? Please enter a positive integer: " << endl;
    cin >> guessesLeft;
    }

    while(toPrintAlternatives != "yes" && toPrintAlternatives != "no"){
        cout << endl << "Do you want the possible list of words to be printed? (Answer with yes or no.) " << endl;
        cin >> toPrintAlternatives;
    }

}

// Returns a vector of words which is the smallest of all partitions
void updateWordAlternatives(const map<string, vector<string>>& partitions, vector<string>& wordAlternatives){

    wordAlternatives.clear();
    for (auto const& [secretWord, partition] : partitions){
        if(partition.size() > wordAlternatives.size()){
            wordAlternatives = partition;
        }
    }
}

// Generates all possible Partitions from the wordAlternatives based on the guessedLetters.
// Returns these  partitions as a Map of partitions(Vectors).
void updatePartitions(const vector<string>& wordAlternatives, unordered_set<char>& guessedLetters, map<string, vector<string>>& partitions ){
    string secretWord;

    for(const string& word: wordAlternatives){
        secretWord = generateSecretWord(word, guessedLetters);
        if(partitions.count(secretWord)){
            partitions[secretWord].push_back(word);
        }
        else{
            vector<string> partition;
            partition.push_back(word);
            partitions.insert(pair<string, vector<string>>(secretWord, partition));
        }
    }
}

//Returns the secretWord depending on the previous guessed letters.
string generateSecretWord(const string& word, const unordered_set<char>& guessedLetters){
    string secretWord = "";
    for(const char letter: word){
        if(guessedLetters.count(letter)){
            secretWord += letter;
        }
        else{
            secretWord += "-";
        }
    }
    return secretWord;
}

// Prints all the alternative words.
void printAlternativeWords(const vector<string>& alternativeWords){
    for (const string word: alternativeWords){
        cout << word << endl;
    }
}

// Returns a dictionary(vector) of strings of the chosen word length from the textfile(path)
void updateDictionary(const string& path, const int& wordLength, vector<string>& dictionary){
    ifstream input;
    input.open(path);
    string newLine;
    int newLineLength;

    while(getline(input, newLine)){
        newLineLength = newLine.length();
        if (newLineLength == wordLength){
            dictionary.push_back(newLine);
        }
    }
    input.close();

}

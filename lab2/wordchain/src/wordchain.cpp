//danwe681 & Elioh505
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
#include <set>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
const string DICT_PATH = "dictionary.txt";

void wordChain(const string& word1, const string& word2);
void updateDictionary(const string& path, unordered_set<string>& dictionary);
void updateNeighbours(const string& word, const unordered_set<string>& dictionary, set<string>& neighbours);

/*
 * Prints the game introduction and asks for input of 2 strings.
 * Calls wordChain() with the given input.
*/
int main() {

    
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: " << endl;

    string word1;
    string word2;

    cin >> word1 >> word2;

    wordChain(word1, word2);    

    return 0;
}

/*
 * A queue of stacks, with stacks being unique possible chains of words, goes through
 * every possible combination of neighbours until the first stack that has reached
 * the final "word2" and prints out the whole wordchain and breaks the while loop.
 */
void wordChain(const string& word1, const string& word2){

    queue<stack<string>> queue;
    stack<string> currentStack;
    stack<string> newStack;
    stack<string> stack;
    unordered_set<string> dictionary;

    stack.push(word1);
    queue.push(stack);
    updateDictionary(DICT_PATH, dictionary);
    set<string> neighbours;
    set<string> oldWords;


    while(!queue.empty()){
        currentStack = queue.front();
        queue.pop();
        if(currentStack.top() == word2){
            cout << "Chain from " << word1 << " to " << word2 << ":" << endl;
            while (!currentStack.empty()){
                cout << currentStack.top() << " ";
                currentStack.pop();
            }
            cout << endl << "Have a nice day." << endl;
            return;
        }
        else {
            string stackTop = currentStack.top();
            updateNeighbours(stackTop, dictionary, neighbours);

            for (const string neighbour : neighbours){
                if (oldWords.find(neighbour) == oldWords.end()){ // neighbour not used before
                    oldWords.insert(neighbour);

                    newStack = currentStack;
                    newStack.push(neighbour);
                    queue.push(newStack);
                }
            }
        }
    }
}

/*
 * Gets the possible words from a .txt file and adds
 * every word to an unordered_set and returns it.
 */
void updateDictionary(const string& path, unordered_set<string>& dictionary){

    ifstream input;
    input.open(path);
    string newLine;

    while(getline(input, newLine)){
        dictionary.insert(newLine);
    }
    input.close();
}

/*
 * For a single word every possible character is exchanged for each letter in
 * the alphabet, and each time if the new version is a word in the dictionary
 * then it is a neighbour word and added to a set which is returned
 */
void updateNeighbours(const string& word, const unordered_set<string>& dictionary, set<string>& neighbours){

    string generatedWord;
    int wordLength = word.length();

    for (int index = 0; index < wordLength; index++){
        for (const char letter : ALPHABET){
            if (letter != word[index]){ // don't check "w" if word[0] is "w"
                generatedWord = word;
                generatedWord[index] = letter;
                if (dictionary.find(generatedWord) != dictionary.end()){
                    neighbours.insert(generatedWord);
                }
            }
        }
    }
}



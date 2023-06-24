#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to get the index of a state in the DFA table
int getIndex(const string& state);

// Function to determine if a word is acceptable or not
bool isAcceptable(const string transitions[10][2], const string* endStates, const string& word);

int main() {
    string filename = "dfa.txt";

    ifstream file(filename);
    if (!file) {
        cout << "Error opening file." << endl;
        return 1;
    }

    // Read states
    string line;
    getline(file, line);
    string states[10];
    size_t pos = 0;
    int stateIndex = 0;
    while ((pos = line.find(' ')) != string::npos) {
        states[stateIndex] = line.substr(0, pos);
        line.erase(0, pos + 1);
        stateIndex++;
    }
    states[stateIndex] = line;

    // Read alphabet
    getline(file, line);
    char alphabet[10];
    int alphabetIndex = 0;
    for (char c : line) {
        if (c != ' ') {
            alphabet[alphabetIndex] = c;
            alphabetIndex++;
        }
    }

    // Read start state
    getline(file, line);
    string startStates[10];
    pos = 0;
    int startStateIndex = 0;
    while ((pos = line.find(' ')) != string::npos) {
        startStates[startStateIndex] = line.substr(0, pos);
        line.erase(0, pos + 1);
        startStateIndex++;
    }
    startStates[startStateIndex] = line;

    // Read end states
    getline(file, line);
    string endStates[10];
    pos = 0;
    int endStateIndex = 0;
    while ((pos = line.find(' ')) != string::npos) {
        endStates[endStateIndex] = line.substr(0, pos);
        line.erase(0, pos + 1);
        endStateIndex++;
    }
    endStates[endStateIndex] = line;

    // Read DFA transition table
    string transitions[10][10];
    for (int i = 0; i < 3; ++i) {
        getline(file, line);
        pos = 0;
        int j = 0;
        while ((pos = line.find(' ')) != string::npos) {
            transitions[i][j] = line.substr(0, pos);
            line.erase(0, pos + 1);
            ++j;
        }
        transitions[i][j] = line;
    }

    // Close the file
    file.close();

    // Test a word
    string word;
    cout << "Enter a word: ";
    cin >> word;

    string currentState = "q0";

    cout << "State: " << currentState << endl;

    for (char c : word) {
        int columnIndex = c - '0';
        currentState = transitions[getIndex(currentState)][columnIndex];
        cout << "State: " << currentState << endl;
    }

    // Check if the word is acceptable
    bool isWordAcceptable = false;
    for (int i = 0; i < 3; ++i) {
        if (currentState == endStates[i]) {
            isWordAcceptable = true;
            break;
        }
    }

    // Display result
    if (isWordAcceptable)
        cout << "Acceptable word." << endl;
    else
        cout << "Not acceptable word." << endl;

    return 0;
}

// Function to get the index of a state in the DFA table
int getIndex(const string& state) {
    return state[state.length() - 1] - '0';
}

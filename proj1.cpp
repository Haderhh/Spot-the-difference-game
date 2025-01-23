/*****************************************
** File: proj1.cpp
** Project: CMSC 202 Project 1, Fall 2024
** Author: Hader Hamayun
** Date: 9/26/2024
** Section: 24
** E-mail: haderh1@umbc.edu
**
** You get to play the game spot the difference 
** with different pictures.
** 
**
***********************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <ctime> 
#include <cstdlib>
#include <iomanip>

using namespace std;

// Constant values for the dimensions of the art
const int ROWS = 10;
const int COLS = 21;

// Function prototypes
void displayArt(const char art[ROWS][COLS]);
int mainMenu(char art[ROWS][COLS]); 
int loadFile(char art[ROWS][COLS]);
void clearArray(char art[ROWS][COLS]);
int playGame(char art[ROWS][COLS]);
bool guessChange(int randRow, int randCol); 

/*****************************************
** Function: main
** Description: Initializes
**              the art array and calls the main menu.
** Pre-condition: None
** Post-condition: Returns 0 
***********************************************/
int main() {
    char art[ROWS][COLS] = {};  // Initialize the art array with empty values
    mainMenu(art);  // Calls the main menu
    return 0;
}

/*****************************************
** Function: displayArt
** Description: Displays the ASCII art in a formatted way.
** Pre-condition: art array must be initialized
** Post-condition: ASCII art is printed to the console
***********************************************/
void displayArt(const char art[ROWS][COLS]) {
    cout << "    ";  
    for (int col = 0; col < COLS; col++) {
        cout << setw(3) << col << " ";  // Print column headers
    }
    cout << endl;

    for (int row = 0; row < ROWS; row++) {
        cout << setw(2) << row << "  ";  // Print row numbers
        for (int col = 0; col < COLS; col++) {
            cout << art[row][col] << "  ";  // Print ASCII characters
        }
        cout << endl; 
    }
}

/*****************************************
** Function: loadFile
** Description: Loads ASCII art from a file into the art array.
** Pre-condition: File must exist and contain valid art data
** Post-condition: art array is populated with characters from the file
***********************************************/
int loadFile(char art[ROWS][COLS]) {
    string file;
    ifstream myfile;
    bool fileLoaded = false;

    while (!fileLoaded) {
        cout << "Enter a file name: ";
        cin >> file;

        myfile.open(file);
        if (!myfile.is_open()) {
            cout << "Could not open file '" << file << "'. Please try again." << endl;
        } else {
            clearArray(art);  // Clear the array before loading new data

            int row, col;
            char character;
            while (myfile >> row >> col >> character) {
                if (row >= 0 and row < ROWS and col >= 0 and col < COLS) {
                    art[row][col] = character;  // Fill the art array
                } else {
                    cerr << "Invalid coordinates (" << row << ", " << col << ") out of bounds." << endl;
                }
            }

            myfile.close();
            cout << "File loaded successfully." << endl;
            fileLoaded = true;
        }
    }
    return 0;
}

/*****************************************
** Function: clearArray
** Description: Clears the art array by filling it with spaces.
** Pre-condition: art array must be initialized
** Post-condition: art array is filled with space characters
***********************************************/
void clearArray(char art[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            art[i][j] = ' ';  // Fill each position with a space
        }
    }
}

/*****************************************
** Function: playGame
** Description: Plays the Spot the Difference game by randomly 
**              modifying a character in the art and asking 
**              the user to guess the modification.
** Pre-condition: art array must be initialized
** Post-condition: Returns to the main menu after the game
***********************************************/
int playGame(char art[ROWS][COLS]) {
    char artCopy[ROWS][COLS] = {};

    // Copy the original art into artCopy
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            artCopy[i][j] = art[i][j];
        }   
    }

    srand(time(NULL));  // Seed random generator

    int randRow = rand() % ROWS;
    int randCol = rand() % COLS;
    char randChar = (rand() % (126 - 32 + 1)) + 32; // Random character between 32 and 126
    artCopy[randRow][randCol] = randChar;  // Modify the artCopy with a random character

    cout << "Original Art:" << endl;
    displayArt(art);
    cout << "Modified Art:" << endl;
    displayArt(artCopy);  // Display the modified art

    // Call the guessing function and return to menu
    if (guessChange(randRow, randCol)) {
        cout << "You are correct!" << endl;
    }

    return 0;
}

/*****************************************
** Function: guessChange
** Description: Prompts the user to guess the coordinates 
**              of the modified character in the art.
** Pre-condition: randRow and randCol must be valid coordinates
** Post-condition: Returns true if the user guesses correctly
***********************************************/
bool guessChange(int randRow, int randCol) {
    int guessRow, guessCol;
    bool guessedCorrectly = false;

    while (!guessedCorrectly) {
        cout << "Guess the coordinates of the change (row col): ";
        cin >> guessRow >> guessCol;

        if (cin.fail()) {
            cin.clear();  // Clear error state
            cin.ignore(1000, '\n');  // Discard invalid input
            cout << "Invalid input. Please enter valid coordinates." << endl;
        } else if (guessRow < 0 || guessRow >= ROWS || guessCol < 0 || guessCol >= COLS) {
            cout << "Coordinates out of bounds. Please enter valid coordinates." << endl;
        } else if (guessRow == randRow && guessCol == randCol) {
            cout << "Correct! You found the change at (" << randRow << ", " << randCol << ")!" << endl;
            guessedCorrectly = true;
        } else {
            cout << "Incorrect guess. Try again!" << endl;
        }
    }
    return guessedCorrectly;
}

/*****************************************
** Function: mainMenu
** Description: Displays the main menu for the user to choose
**              actions such as loading art, displaying art, or playing the game.
** Pre-condition: art array must be initialized
** Post-condition: Exits the program when the user selects 'Exit'
***********************************************/
int mainMenu(char art[ROWS][COLS]) {
    int choice;
    do {
        cout << "Welcome to the Spot The Difference Game" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Load ASCII Art from File" << endl;
        cout << "2. Display Art" << endl;
        cout << "3. Play Game" << endl;
        cout << "4. Exit" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                loadFile(art);
                break;
            case 2:
                displayArt(art);
                cout << "Art Displayed" << endl;
                break;
            case 3:
                playGame(art);
                break;
            case 4:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Please choose a valid option (1-4)." << endl;
                break;
        }
    } while (choice != 4);

    return choice;
}

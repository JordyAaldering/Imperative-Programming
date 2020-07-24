#include <iostream>
#include <fstream>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <sstream>
using namespace std;

// Jordy Aaldering // s1004292 // Informatica
// Thomas van Harskamp // s1007576 // Informatica en Wiskunde
// We hebben de opdracht niet af kunnen krijgen maar hier is wat wel wel hebben:


typedef int Chars;
const int maxChars = 20, maxWords = 30000;

int UserInput (string& command)
{
    //  Pre-condition:
    assert(true);
    /*  Post-condition:
        The user is asked for input.
        The user can enter a command and a filename.
    */
    cout << "Please enter a command, type help for a list of commands" << endl;
    cout << "User>";
    getline(cin, command);
    string commandWord;
    istringstream iss(command);
    iss >> commandWord;

    if (commandWord == "enter")
        return 1;
    else if (commandWord == "content")
        return 2;
    else if (commandWord == "stop")
        return 3;
    else if (commandWord == "count")
        return 4;
    else if (commandWord == "where")
        return 5;
    else if (commandWord == "context")
        return 6;
    return 0;
}

bool OpenFile (ifstream& inputfile, string command)
{
    //  Pre-condition:
    assert(true);
    /*  Post-condition:
        The file is opened.
    */
    string filename;
    filename = command.substr(command.find_first_of(" \t")+1);
    filename = filename + ".txt";
    inputfile.open(filename.c_str());
    if (inputfile.is_open())
        return true;
    return false;
}

int CountWords (ifstream& inputfile, string words[])
{
    //  Pre-condition:
    assert(inputfile.is_open());
    /*  Post-condition:
        The amount of words is shown.
    */
    inputfile.clear();
    inputfile.seekg(0);

    string word;
    int wCount = 0;
    while (inputfile >> word) {
        /*for (int cCount = 0; cCount < maxChars; cCount++) {
            words[wCount][cCount] = word[cCount];
            cout << words[wCount][cCount] << " ";
        }*/
        words[wCount] = word;
        wCount++;
    }   return wCount;
}

void ShowWords (string words[], int nrOfWords)
{
    //  Pre-condition:
    assert(nrOfWords > 0);
    /*  Post-condition:
        The words are shown to the user.
    */
    cout << "List of words: " << endl;
    for (int wCount = 0; wCount < nrOfWords; wCount++)
        cout << words[wCount] << endl;
}

int main()
{
    cout << "hfdsjonfjhsfjfjsfjjsojdfjjsjfsjoidfjo" << endl;
    ifstream inputfile;
    string words[10];
    string command, filename;
    int action = -1, nrOfWords;

    do
    {
        if (action == -1) {
            do {
                cout << "You must open a file first"<<endl;
                action = UserInput(command);
                } while (action != 1);
        }

        switch (action)
        {
        case 1: if (OpenFile (inputfile, command)) {
                    nrOfWords = CountWords(inputfile, words);
                    cout << "File opened, the file contains " << nrOfWords << " words." << endl;
                    }
                else
                    cout << "File could not be opened." << endl;
                break;
        case 2: ShowWords(words, nrOfWords);
                break;
        case 4: break;
        case 5: break;
        case 6: break;
        }
        cin.clear();
        cin.ignore(10000, '\n');

        action = UserInput(command);
    }
    while (action != 3);

    inputfile.close();
    if (inputfile.is_open()) {
        cout << "The file '" << filename << "' could not be closed." << endl;
        return -1;
    }   cout << "File closed.";

    return 0;
}

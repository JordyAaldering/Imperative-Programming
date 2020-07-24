#include <iostream>
#include <fstream>
#include <cassert>
#include <windows.h>
#include "cursor.h"
using namespace std;

//  Thomas van Harskamp  //  s1007576  //  Informatica & Wiskunde
//  Jordy Aaldering      //  s1004292  //  Informatica

enum Cell {Dead=0, Live};                       // a cell is either Dead or Live (we use the fact that dead = 0 and live = 1)
const char DEAD         = '.';                  // the presentation of a dead cell (both on file and screen)
const char LIVE         = '*';                  // the presentation of a live cell (both on file and screen)
const int NO_OF_ROWS    = 40;                   // the number of rows (height) of the universe (both on file and screen)
const int NO_OF_COLUMNS = 60;                   // the number of columns (width) of the universe (both on file and screen)
const int ROWS          = NO_OF_ROWS    + 2;    // the number of rows in a universe array, including the 'frame' of dead cells
const int COLUMNS       = NO_OF_COLUMNS + 2;    // the number of columns in a universe array, including the 'frame' of dead cells
const int MAX_FILENAME_LENGTH = 80;             // the maximum number of characters for a file name (including termination character)

bool enter_filename (char filename[MAX_FILENAME_LENGTH])
{   //  Pre-condition:
    assert(true);
    /*  Post-condition:
        The user is asked to enter a filename.
        After entering the file name the user is told whether if filename is correct or not.
    */
    cout << "Please enter a file name to open (including the extension): ";
    for (int counter = 0; counter < MAX_FILENAME_LENGTH; counter++)
    {   char c;
        cin.get(c);
        if (c == '\n')
            return true;
        filename[counter] = c;
    }
    return false;
}

int user_input ()
{   //  Pre-conditions:
    assert(true);
    /*  post-conditions:
        The content from 'inputfile' is placed in an array.
    */
    int input;
    do
    {   cout << "Enter how many steps you want to simulate: ";
        cin >> input;
    }   while (!(input > 0));
    return input;
}

bool enter_outfile(char filename[MAX_FILENAME_LENGTH])
{   //  Pre-conditions:
    assert(true);
    /*  post-conditions:
        The user is asked to name a file to safe the array to.
    */
    cout << "Please enter a file name to safe to (including the extension): ";
    for (int counter = 0; counter < MAX_FILENAME_LENGTH; counter++)
    {   char c;
        cin.get(c);
        if (c == '\n')
            return true;
        filename[counter] = c;
    }
    return false;
}

bool read_universe_file (ifstream& inputfile, Cell universe[ROWS][COLUMNS])
{   //  Pre-conditions:
    assert(inputfile.is_open());
    /*  post-conditions:
        The content from 'inputfile' is placed in an array.
    */
    int counterColumn, counterRow;
    for (counterColumn = 0; counterColumn < COLUMNS; counterColumn++)
        for (int count = 0; count < ROWS; count++)
            universe[count][counterColumn] = Dead;

    for (counterRow = 1; counterRow < ROWS - 1; counterRow++)
    {   for (counterColumn = 1; counterColumn <= NO_OF_COLUMNS; counterColumn++)
        {   char cRow;
            inputfile.get(cRow);
            if (cRow == '.')
                universe[counterRow][counterColumn] = Dead;
            else
                universe[counterRow][counterColumn] = Live;
        }
        char garbage;
        inputfile.get(garbage);
    }
}

void show_universe (Cell universe[ROWS][COLUMNS])
{   //  Pre-conditions:
    assert(true);
    /*  post-conditions:
        The cells are shown in the console.
        A '*' is shown if a cell is alive and '.' is shown if a cell is dead.
    */
    int counterColumn, counterRow;
    for (counterRow = 0; counterRow < ROWS; counterRow++)
    {   for (counterColumn = 0; counterColumn < COLUMNS; counterColumn++)
        {   if (universe[counterRow][counterColumn] == Dead)
                cout<<DEAD;
            else
                cout<<LIVE;
        }
        cout<<endl;
    }
}

void next_generation (Cell now[ROWS][COLUMNS], Cell next[ROWS][COLUMNS])
{   //  Pre-conditions:
    assert(true);
    /*  post-conditions:
        The next generation is calculated and put in an array.
    */
    int counterColumn, counterRow;
    for (counterColumn = 0; counterColumn < COLUMNS; counterColumn++)
        for (int count = 0; count < ROWS; count++)
            next[count][counterColumn] = Dead;

    for (counterRow = 1; counterRow <= NO_OF_ROWS; counterRow++)
    {   for (counterColumn = 1; counterColumn <= NO_OF_COLUMNS; counterColumn++)
        {   int a,b,c,d,e,f,g,h,sum;
            a   = now[counterRow-1][counterColumn-1];
            b   = now[counterRow]  [counterColumn-1];
            c   = now[counterRow+1][counterColumn-1];
            d   = now[counterRow-1][counterColumn];
            e   = now[counterRow+1][counterColumn];
            f   = now[counterRow-1][counterColumn+1];
            g   = now[counterRow]  [counterColumn+1];
            h   = now[counterRow+1][counterColumn+1];
            sum = a+b+c+d+e+f+g+h;

            if (now [counterRow][counterColumn] == 1 && ( sum < 2 || sum > 3))
                next[counterRow][counterColumn] = Dead;
            else if (now[counterRow][counterColumn] == 0 && sum == 3)
                next[counterRow][counterColumn] = Live;
            else
                next[counterRow][counterColumn] = now[counterRow][counterColumn];
        }
    }
}

void set_universe_to_next (Cell universe[ROWS][COLUMNS], Cell next[ROWS][COLUMNS])
{   //  Pre-conditions:
    assert(true);
    /*  post-conditions:
        The current generation is replaced by the next generation.
    */
    for (int counterRow = 0; counterRow < ROWS; counterRow++)
        for (int counterColumn = 0; counterColumn < COLUMNS; counterColumn++)
            universe[counterRow][counterColumn] = next[counterRow][counterColumn];
}

int main ()
{   ifstream inputfile;
    ofstream outfile;
    char infilename [MAX_FILENAME_LENGTH];
    char outfilename[MAX_FILENAME_LENGTH];
    Cell universe   [ROWS][COLUMNS];
    Cell next       [ROWS][COLUMNS];

    if (enter_filename(infilename) == false || enter_outfile(outfilename) == false)
    {   cout << "Something went wrong entering the file names.";
        return -1;
    }

    int steps = user_input();
    inputfile.open    (infilename);
    read_universe_file(inputfile, universe);
    inputfile.close   ();

    show_universe(universe);
    for (int count = 1; count < steps; count++)
    {   cls();
        set_cursor_position (0, 0);
        next_generation     (universe, next);
        set_universe_to_next(universe, next);
        show_universe       (universe);
        Sleep (100);
    }

    outfile.open(outfilename);
    for (int counterRow = 0; counterRow < ROWS; counterRow++)
    {   for (int counterColumn = 0; counterColumn < COLUMNS; counterColumn++)
        {   if (universe[counterRow][counterColumn] == Dead)
                outfile.put('.');
            else
                outfile.put('*');
        }
        outfile.put('\n');
    }
    outfile.close();
    return 0;
}

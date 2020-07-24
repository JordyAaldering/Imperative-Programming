// Thomas van Harskamp // s1007576 // Wiskunde & Informatica
// Jordy Aaldering     // s1004292 // Informatica

#include <cassert>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int patternLength, sourceLength;

bool input (string& pattern, string& source)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      The user is asked to enter 'pattern' and 'source'.
      False is returned if one of the strings is empty.
      Otherwise true is returned.
    */
    cout << "Pattern: ";
    getline (cin, pattern);
    cout << "Source:  ";
    getline (cin, source);

    if (pattern == "" || source == "")
        return false;
    return true;
}

bool simplify (string& pattern, int patternLength)
{
    //Pre-conditions:
    assert (patternLength >= 0);
    /*Post-conditions:
      Double instances of '*' are removed from 'pattern'.
    */
    for (int i = 0; i <= patternLength; ++i)
        if (pattern[i] == '*' && pattern[i + 1] == '*')
        {
            pattern.erase (pattern.begin() + i);
            return true;
        }
    return false;
}

bool match_pattern (string pattern, int patternPos, string source, int sourcePos)
{
    //Pre-conditions:
    assert (patternPos >= 0 && sourcePos >= 0);
    /*Post-conditions:
      The two strings are matched.
      True is returned if the strings are the same, regarding dots and asterixes.
    */
    if (patternPos == patternLength)
    {
        if (pattern[patternPos] == '*')
            return true;
        else if (pattern[patternPos] == '.' && sourcePos == sourceLength)
            return true;
        else if (pattern[patternPos] == source[sourcePos] && sourcePos == sourceLength)
            return true;
        return false;
    }
    else
    {
        if (pattern[patternPos] == '.')
            return match_pattern (pattern, ++patternPos, source, ++sourcePos);
        else if (pattern[patternPos] == source[sourcePos])
            return match_pattern (pattern, ++patternPos, source, ++sourcePos);
        else if (pattern[patternPos] == '*')
            for (++patternPos; sourcePos <= sourceLength; ++sourcePos)
                if (match_pattern (pattern, patternPos, source, sourcePos))
                    return match_pattern (pattern, patternPos, source, sourcePos);
        return false;
    }
}

void output (string pattern, string source)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      'Pattern' is simplified.
      The user is told whether the strings match.
    */
    do {
        patternLength = pattern.length() - 1;
        sourceLength  = source.length()  - 1;
    } while (simplify (pattern, patternLength));

    if (match_pattern (pattern, 0, source, 0))
        cout << "The patterns match!\n";
    else
        cout << "The patterns don't match.\n";
    cout << endl;
}

int main ()
{
    string pattern, source;

    cout << "Keep 'pattern' or 'source' empty to shut down.\n";
    while (input (pattern, source))
        output (pattern, source);

    return 0;
}

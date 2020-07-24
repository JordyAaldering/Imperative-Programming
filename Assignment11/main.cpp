// Thomas van Harskamp // s1007576 // Wiskunde & Informatica
// Jordy Aaldering     // s1004292 // Informatica

#include <cassert>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int user_input ()
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      The user is asked what function to run.
    */
    int choice;
    do {
        cout << "1: Power\n2: Palindrome\n3: Match\n4: Quit\n>>";
        cin >> choice;
    } while (choice < 1 || choice > 4);

    string garbage;
    getline (cin, garbage);
    return choice;
}

double power1 (double x, int n)
{
    //Pre-conditions:
    assert (n >= 0);
    /*Post-conditions:
      The power of x and n is returned.
    */
    if (n == 0)
        return 1;
    return x * power1 (x, n - 1);
}

double power2 (double x, int n)
{
    //Pre-conditions:
    assert (n >= 0);
    /*Post-conditions:
      The power of x and n is returned.
    */
    if (n == 0)
        return 1;
    else if (n % 2 == 0)
        return power2 (x, n / 2) * power2 (x, n / 2);
    return x * power2 (x, n - 1);
}

void power ()
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      The user is asked for double x and integer n.
      The power of x and n is shown to the user for both functions.
    */
    double x;
    int n;

    cout << "Double x = ";
    cin >> x;
    do {
        cout << "Integer n = ";
        cin >> n;
    } while (n < 0);

    cout << "Power1: " << power1 (x, n) << "\nPower2: " << power2 (x, n) << endl;
    //Order of run-time complexity: O(n / 2).
}

void convert_lowercase (string& text, int j)
{
    //Pre-conditions:
    assert (j >= 0);
    /*Post-conditions:
      Text is converted to lowercase.
    */
    for (int i = 0; i <= j; i++)
        text[i] = tolower(text[i]);
}

bool is_illegal (char c)
{
    //Pre-conditions:
    assert (c >= 0);
    /*Post-conditions:
      True is returned if the chosen character is in the list of illegal characters.
    */
    char chars[] = {' ', '.', ',', ':', ';', '\'', '!', '?', '-'};
    for (int i = 0; (unsigned)i <= strlen(chars); i++)
        if (c == chars[i])
            return true;
    return false;
}

void convert_characters (string& text, int& j)
{
    //Pre-conditions:
    assert (j >= 0);
    /*Post-conditions:
      Special characters are removed from text.
    */
    string newText = "";
    for (int i = 0; i <= j; i++)
            if (!is_illegal(text[i]))
                newText += text[i];
    text = newText;
    j = text.length() - 1;
}

bool palindrome1 (string& text, int i, int j)
{
    //Pre-conditions:
    assert (i >= 0 && j >= 0);
    /*Post-conditions:
      Returns true if text is a palindrome.
      Returns false if text is not a palindrome.
    */
    if (i >= j)
        return true;
    else if (text[i] != text[j])
        return false;
    return palindrome1 (text, ++i, --j);
}

bool palindrome2 (string& text, int i, int j)
{
    //Pre-conditions:
    assert (i >= 0 && j >= 0);
    /*Post-conditions:
      Returns true if text is a not case sensitive palindrome.
      Returns false otherwise.
    */
    convert_lowercase  (text, j);
    return palindrome1 (text, 0, j);
}

bool palindrome3 (string& text, int i, int j)
{
    //Pre-conditions:
    assert (i >= 0 && j >= 0);
    /*Post-conditions:
      Returns true if text is a non case anc character sensitive palindrome.
      Returns false otherwise.
    */
    convert_lowercase  (text, j);
    convert_characters (text, j);
    return palindrome1 (text, 0, j);
}

void palindrome ()
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      A text is asked.
      The user is told if text is a palindrome.
    */
    string text;
    int j;
    do {
        cout << "Text: ";
        getline(cin, text);
        j = text.length() - 1;
    } while (j <= 0);

    cout << "Palindrome1: \"";
    if (palindrome1 (text, 0, j))
        cout << text << "\" is a palindrome.";
    else
        cout << text << "\" is not a palindrome.";

    cout << "\nPalindrome2: \"";
    if (palindrome2 (text, 0, j))
        cout << text << "\" is a palindrome.";
    else
        cout << text << "\" is not a palindrome.";

    cout << "\nPalindrome3: \"";
    if (palindrome3 (text, 0, j))
        cout << text << "\" is a palindrome.";
    else
        cout << text << "\" is not a palindrome.";
    cout << endl;
}

bool match_chars (char chars[], int i, string source, int j)
{
    //Pre-conditions:
    assert (i >= 0 && j >= 0);
    /*Post-conditions:
      True is returned if the chosen character in char match one of the characters in the chosen range of source.
      False is returned if this is not the case.
    */
    int c = strlen(chars) - 1;
    if (i == c)
    {
        for (; (unsigned)j < source.length(); ++j)
            if (chars[i] == source[j])
                return true;
        return false;
    }
    else
    {
        int s = source.length();
        for (; j < s; ++j)
            if (chars[i] == source[j] && match_chars(chars, ++i, source, ++j))
                return true;
        return false;
    }
}

void match ()
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      The user is asked for 'chars' and 'source'.
      The user is shown whether 'chars' and 'source' match.
    */
    char chars[64];
    string source;

    cout << "Chars: ";
    cin.getline(chars, 64);
    cout << "Source: ";
    getline(cin, source);

    cout << "\"" << chars;
    if (match_chars (chars, 0, source, 0))
        cout <<"\" matches \"";
    else
        cout << "\" does not match \"";
    cout << source << "\"." << endl;
}

int main ()
{
    while (true)
    {
        int choice = user_input ();
        switch (choice)
        {
            case 1: power ();       break;
            case 2: palindrome ();  break;
            case 3: match ();       break;
            case 4: return 0;
        }   cout << endl;
    }
}

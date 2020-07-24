#include <iostream>
using namespace std;

enum Month {January=1,February,March,April,May,June,July,August,September,October,November,December};

int easter_base (int year)
{   const int A     = year % 19;
    const int B     = year / 100;
    const int C     = year % 100;
    const int D     = B / 4;
    const int E     = B % 4;
    const int F     = (B + 8) / 25;
    const int G     = (B - F + 1) / 3;
    const int H     = (19 * A + B - D - G + 15) % 30;
    const int I     = C / 4;
    const int K     = C % 4;
    const int L     = (32 + 2 * E + 2 * I - H - K) % 7;
    const int M     = (A + 11 * H + 22 * L) / 451;
    return H + L - 7 * M + 114;
}

int easter_day (int year)
{   return (easter_base (year) % 31) + 1;
}

Month easter_month (int year)
{   return static_cast<Month> (easter_base (year) / 31);
}

/********************************************************************
    Thomas van Harskamp   s1007576   Informatica & Wiskunde
    Jordy Aaldering       s1004292   Informatica
*********************************************************************
    Assignment part 1: Leap years
********************************************************************/
bool is_leap_year (int year)
{   if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return true;
    else
        return false;
}

int number_of_days_in_month (int year, int month)
{   int days;
    if (is_leap_year(year))
        return days = 29;
    else if (!is_leap_year(year) && month == 2)
        return days = 28;
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return days = 30;
    else
        return days = 31;
}

/********************************************************************
    Assignment part 2: Holy days based on Easter
********************************************************************/
int day, month, year;

void count_down_days (int days_to_do)
{   day = easter_day(year);
    month = easter_month(year);

    for (days_to_do; days_to_do != 0; days_to_do--)
    {   day--;
        if (day == 0)
        {   month--;
            day = number_of_days_in_month(year, static_cast<Month>(month));
        }
    }
}

void count_up_days (int days_to_do)
{   day = easter_day(year);
    month = easter_month(year);

    for (days_to_do; days_to_do != 0; days_to_do--)
    {   if (day == number_of_days_in_month(year, static_cast<Month>(month)))
        {   month++;
            day = 0;
        }
        day++;
    }
}

void show_holy_days ()
{   cout << "Enter desired year: ";
    cin >> year;

    if (is_leap_year(year))
        cout << year << " is a leap year!" << endl << endl;
    else
        cout << year << " is not a leap year." << endl << endl;

    cout << "Dates will be shown as:\tday/month/year" << endl;

    count_down_days(49);
    cout << "Carnival starts on:\t" << day << "/" << month << "/" << year << endl;
    count_down_days(47);
    cout << "Carnival ends on:\t" << day << "/" << month << "/" << year << endl;

    count_down_days(2);
    cout << "Good Friday is on:\t" << day << "/" << month << "/" << year << endl;

    cout << "Easter is on:\t\t" << easter_day(year) << "/" << easter_month(year) << "/" << year << endl;

    count_up_days(39);
    cout << "Ascension day is on:\t" << day << "/" << month << "/" << year << endl;

    count_up_days(49);
    cout << "Whitsuntide is on:\t" << day << "/" << month << "/" << year << endl;
}

int main()
{   show_holy_days();
    return 0;
}

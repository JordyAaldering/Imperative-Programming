#include <iostream>
#include <math.h>
using namespace std;
/********************************************************************
    Thomas van Harskamp   s1007576   Informatica & Wiskunde
    Jordy Aaldering       s1004292   Informatica
********************************************************************/
int year, month, day, daysToDo;

void user_input ()
{   cout << "Please enter the year (YYYY): ";
    while (true)
    {   cin >> year;
        if (year >= 1700 && year < 2400)
            break;
        else
            cout << "Please enter a year between 1700 and 2400: ";
    }
    cout << "Please enter the month  (MM): ";
    while (true)
    {   cin >> month;
        if (month >= 1 && month <= 12)
            break;
        else
            cout << "Please enter a month between 1 and 12: ";
    }
}

bool is_leap_year (int year)
{   if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return true;
    else
        return false;
}

int days_in_month (int year, int month)
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

int first_day_of_month (int year, int month)
{   int dayCode, yearCode, monthCode, centuryCode, leapCode;

    yearCode = static_cast<int>(year % 100 + floor(year % 100 / 4)) % 7;

    switch (month)
    {   case 1: case 10:         monthCode = 0; break;
        case 2: case 3: case 11: monthCode = 3; break;
        case 4: case 7:          monthCode = 6; break;
        case 5:                  monthCode = 1; break;
        case 6:                  monthCode = 4; break;
        case 8:                  monthCode = 2; break;
        default:                 monthCode = 5; break;
    }

    switch (static_cast<int>(floor(year / 100) - 16))
    {   case 1: case 5: centuryCode = 4; break;
        case 2: case 6: centuryCode = 2; break;
        case 3: case 7: centuryCode = 0; break;
        default:        centuryCode = 6; break;
    }

    if (is_leap_year(year) && month > 2)
        leapCode = 0;
    else
        leapCode = 1;

    return dayCode = (yearCode + monthCode + centuryCode + leapCode) % 7;
}

void fill_first_week()
{   switch (first_day_of_month(year, month))
    {   case 1:  cout << "1\t2\t3\t4\t5\t6\t7"; day = 7; break;
        case 2:  cout << "\t1\t2\t3\t4\t5\t6";  day = 6; break;
        case 3:  cout << "\t\t1\t2\t3\t4\t5";   day = 5; break;
        case 4:  cout << "\t\t\t1\t2\t3\t4";    day = 4; break;
        case 5:  cout << "\t\t\t\t1\t2\t3";     day = 3; break;
        case 6:  cout << "\t\t\t\t\t1\t2";      day = 2; break;
        default: cout << "\t\t\t\t\t\t1";       day = 1; break;
    }
}

void fill_weeks()
{   daysToDo = days_in_month(year, month) - day;
    day++;
    cout << endl;

    while (daysToDo > 0)
    {   int week;
        for (week = 7; week != 0; week--)
        {   if (daysToDo > 0)
            {   cout << day << "\t";
                day++;
                daysToDo--;
            }
        }
    cout << endl;
    }
}

void show_month()
{   cout << "Mon\tTue\tWed\tThu\tFri\tSat\tSun" << endl;
    fill_first_week();
    fill_weeks();
}

int main()
{   user_input();
    show_month();
    return 0;
}

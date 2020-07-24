#include <iostream>
#include <cmath>
using namespace std;

//Thomas van Harskamp / s1007576 / Study student 1: Informatica/Wiskunde
//Jordy Aaldering / s1004292 / Study student 2: Informatica

char input_x [4];
int numbertype_input;
int numbertype_output;
int w;
int x;
int y;
int z;
int decimal_outputnumber;
double binary_outputnumber;
double binary_outputvariable;
int binary_divider = 32768;
double binary_multiplier = 1000000000000000;
int octal_outputnumber;
int octal_outputvariable;
int octal_divider = 32768;
int octal_multiplier = 100000;
char hexadecimal_outputnumber [4];

void binary_input ()
{
    w = 8*w;
    x = 4*x;
    y = 2*y;
}

void octal_input ()
{
    w = 512*w;
    x = 64*x;
    y = 8*y;
}

void hexadecimal_input ()
{
    w = 4096*w;
    x = 256*x;
    y = 16*y;
}

void decimal_input ()
{
    w = 1000*w;
    x = 100*x;
    y = 10*y;
}

void binary_output ()
{
    for (int count1 = 0 ; count1<=15 ; count1++)
    {
        binary_outputvariable = decimal_outputnumber / binary_divider * binary_multiplier;
        decimal_outputnumber = decimal_outputnumber % binary_divider;
        binary_divider = binary_divider/2;
        binary_multiplier = binary_multiplier/10;
        binary_outputnumber = binary_outputnumber + binary_outputvariable;
    }
}

void octal_output ()
{
    for (int count2 = 0 ; count2<=5 ; count2++)
    {
        octal_outputvariable = decimal_outputnumber / octal_divider * octal_multiplier;
        decimal_outputnumber = decimal_outputnumber % octal_divider;
        octal_divider = octal_divider/8;
        octal_multiplier = octal_multiplier/10;
        octal_outputnumber = octal_outputnumber + octal_outputvariable;
    }
}

void hexadecimal_output ()
{
    hexadecimal_outputnumber [0] = decimal_outputnumber/4096;
    decimal_outputnumber = decimal_outputnumber%4096;
    hexadecimal_outputnumber [1] = decimal_outputnumber/256;
    decimal_outputnumber = decimal_outputnumber%256;
    hexadecimal_outputnumber [2] = decimal_outputnumber/16;
    decimal_outputnumber = decimal_outputnumber%16;
    hexadecimal_outputnumber [3] = decimal_outputnumber;

    if (hexadecimal_outputnumber [0] <= 9)
        hexadecimal_outputnumber [0] = hexadecimal_outputnumber [0] + 48;
    else
        hexadecimal_outputnumber [0] = hexadecimal_outputnumber [0] + 55;

    if (hexadecimal_outputnumber [1] <= 9)
        hexadecimal_outputnumber [1] = hexadecimal_outputnumber [1] + 48;
    else
        hexadecimal_outputnumber [1] = hexadecimal_outputnumber [1] + 55;

    if (hexadecimal_outputnumber [2] <= 9)
        hexadecimal_outputnumber [2] = hexadecimal_outputnumber [2] + 48;
    else
        hexadecimal_outputnumber [2] = hexadecimal_outputnumber [2] + 55;

    if (hexadecimal_outputnumber [3] <= 9)
        hexadecimal_outputnumber [3] = hexadecimal_outputnumber [3] + 48;
    else
        hexadecimal_outputnumber [3] = hexadecimal_outputnumber [3] + 55;
}

void number_calculator ()
{
    cout<<"Enter a four-digit number (for hexadecimal numbers, use capital letters A...F for 10...15)."<<endl;
    cin>>input_x;
    cout<<"If the number is binary, type 1. If the number is octal, type 2. If the number is hexadecimal, type 3. If the number is decimal, type any other number."<<endl;
    cin>>numbertype_input;

    if (input_x [0] >= 65)
        w = (input_x [0] - 55);
    else
        w = (input_x [0] - 48);

    if (input_x [1] >= 65)
        x = (input_x [1] - 55);
    else
        x = (input_x [1] - 48);

    if (input_x [2] >= 65)
        y = (input_x [2] - 55);
    else
        y = (input_x [2] - 48);

    if (input_x [3] >= 65)
        z = (input_x [3] - 55);
    else
        z = (input_x [3] - 48);

    switch (numbertype_input)
    {
        case 1: binary_input () ; break;
        case 2: octal_input () ; break;
        case 3: hexadecimal_input () ; break;
        default: decimal_input () ; break;
    }

    decimal_outputnumber = w+x+y+z;

    cout<<"To what do you want to convert the number? For binary, type 1. For octal, type 2. For hexadecimal, type 3. For decimal, type any other number."<<endl;
    cin>>numbertype_output;
    cout<<"The number is:"<<endl;

    switch (numbertype_output)
    {
        case 1: binary_output () ;
            cout.precision(17);
            cout<<binary_outputnumber<<fixed<<endl;
            break;
        case 2: octal_output () ;
            cout<<octal_outputnumber<<endl;
            break;
        case 3: hexadecimal_output() ;
            cout<<hexadecimal_outputnumber<<endl;
            break;
        default:
            cout<<decimal_outputnumber<<endl;
            break;
    }
}

int main()
{
    number_calculator ();
    return 0;
}

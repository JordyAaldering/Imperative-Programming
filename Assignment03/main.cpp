#include <iostream>
#include <cmath>
using namespace std;

//Thomas van Harskamp / s1007576 / Study student 1: Informatica/Wiskunde
//Jordy Aaldering / s1004292 / Study student 2: Informatica


//////////////////////////////////////////////////////////////Opgave 1.1////////////////////////////////////////////////////////////
// V = 0
// | Xn * Xn - V | <= 0.1
// Xn = 0
// | 0 * 0 - 0 | = 0
// 0 < 1
//
// V = 1
// | Xn * Xn - V | <= 0.1
// Xn = 1
// | 1 * 1 - 1 | = 0
// 0 < 1

// V = 0.4
// | Xn * Xn - V | <= 0.1
// Xn = 0.5
// | 0.5 * 0.5 - 0.4 | = 0.15
// 0.15 !<= 0.1
// Xn = 0.6
// | 0.6 * 0.6 - 0.4 | = 0.04
// 0.04 < 0.1

// V = 64
// | Xn * Xn - V | <= 0.1
// Xn = 8
// | 8 * 8 - 64 | = 0
// 0 < 1

// V = 69
// | Xn * Xn - V | <= 0.1
// Xn = 9
// | 9 * 9 - 69 | = 12
// 12 !<= 0.1
// Xn = 8.5
// | 8.5 * 8.5 - 69 | = 3.25
// 3.25 !<= 0.1
// Xn = 8.35
// | 8.35 * 8.35 - 69 | = 0.7225
// 0.7225 < 0.1

//////////////////////////////////////////////////////////Einde opgave 1.1///////////////////////////////////////////////////////

//////////////////////////////////////////////////////////Opgave 1.2 en 1.3///////////////////////////////////////////////////////
double e;
double v;
int c;
int n=0;
int i=0;
double x;
double a;
double b;

void inclusion ()
{
    while (n*n<=v)
        n++;
    a=n-1;
    b=n;
    if (a*a==v)
        x=a;
    else
        x=(a+b)/2;

    cout<<"i\ta\tb\tx"<<endl;
    cout<<i<<"\t"<<a<<"\t"<<b<<"\t"<<x<<endl;

    while (abs(x*x-v)>e)
    {
       if (x*x>=v)
            b=x;
       else
            a=x;
       x=(a+b)/2;
       i=++i;
       cout<<i<<"\t"<<a<<"\t"<<b<<"\t"<<x<<endl;
    }

    cout<<"The squareroot is:"<<endl;
    cout<<x<<endl;
}

void newtonraphson ()
{
    if (v>=1)
    {
        while (n*n<=v)
            n++;
        n--;
    }
    if (v>0 && v<1)
        n=1;
    x=n;

    cout<<"i\tx"<<endl;
    cout<<i<<"\t"<<x<<endl;

    while (abs(x*x-v)>e)
    {
        x = (x-(x*x-v)/(2*x));
        i++;
        cout<<i<<"\t"<<x<<endl;
    }

    cout<<"The squareroot is:"<<endl;
    cout<<x<<endl;
}


int main()
{
    cout << "Give desired squareroot"<<endl;
    cin >> v;
    cout << "Give desired precision"<<endl;
    cin >> e;
    cout << "Type 0 for Inclusion method or type any other number for Newton-Raphson method"<<endl;
    cin >> c;

    if (c==0)
        inclusion ();
    else
        newtonraphson ();
    return 0;
}
//////////////////////////////////////////////////////////Einde opgave 1.2 en 1.3////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////Opgave 1.4//////////////////////////////////////////////////////////////////////
//Precision e is set to 0.1 in the following tests
//v         Number of iterations for Inclusion method                   Number of iterations for Newton-Raphson method
//0         1                                                           1
//1         1                                                           1
//0.4       3                                                           2
//64        1                                                           1
//69        4                                                           2
//We can conclude that the Newton-Raphson is more efficient than the Inclusion method
//////////////////////////////////////////////////////////Einde opgave 1.4//////////////////////////////////////////////////////////////////

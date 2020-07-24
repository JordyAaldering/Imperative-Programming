// Thomas van Harskamp // s1007576 // Wiskunde & Informatica
// Jordy Aaldering     // s1004292 // Informatica

#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Items
{
    int price;
    string product;
};

bool read_file (vector<Items>& shopList)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      The prices and products in giftstore.txt are placed in a vector.
    */
    ifstream infile;
    infile.open("giftstore.txt");
    if (!infile)
    {   cout << "File 'giftstore.txt' could not be opened!";
        return false;
    }

    while (infile)
    {
        int price;
        string product, garbage;
        Items items;

        infile >> price;
        getline(infile, product);
        product.erase(0, 1);

        items.price   = price;
        items.product = product;
        shopList.push_back(items);
    }
    shopList.pop_back();

    infile.close();
    if (infile)
    {   cout << "File giftstore.txt could not be closed!";
        return false;
    }

    return true;
}

int read_person (vector<string>& wishList, string filename)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      Reads the wishlist and places it in a vector.
    */
    ifstream infile;
    int budget;
    string garbage, product;

    infile.open(filename);
    if (!infile)
        cout << "File '" << filename << "' could not be opened!";

    infile >> budget;
    getline (infile, garbage);

    while (infile)
    {   getline(infile, product);
        wishList.push_back(product);
    }
    wishList.pop_back();

    infile.close();
    if (infile)
        cout << "File '" << filename << "' could not be closed!";

    return budget;
}

int check_itemlist (vector<Items>& items, string wishListItem)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      The price is returned if an item is available in the store.
    */
    int itemsLength = static_cast<int>(items.size());
    for (int i = 0; i < itemsLength; i++)
        if (items[i].product == wishListItem)
            return items[i].price;
    return 0;
}

void make_wishlist (vector<Items>& giftstore, vector<Items>& wishList, vector<string>& personList)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      A new wishlist is made that contains the price of products that are available and on the wishlist.
    */
    Items items;
    int personLength = static_cast<int>(personList.size());

    for (int i = 0; i < personLength; i++)
    {
        int price = check_itemlist (giftstore, personList[i]);
        if (price > 0)
        {
            items.price   = price;
            items.product = personList[i];
            wishList.push_back(items);
        }
    }
}

bool is_better_solution (vector<Items>& currentSol, vector<Items>& bestSol)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      Returns true if currSol is a better solution than bestSol, else returns false.
    */
    int currentInt, bestInt;

    for (int i = 0; i < static_cast<int> (currentSol.size()); i++)
        currentInt += currentSol[i].price;

    for (int j = 0; j < static_cast<int> (bestSol.size()); j++)
        bestInt += bestSol[j].price;

    return currentInt > bestInt;
}

void gifts (int wishListLength, vector<Items>& wishList, vector<Items>& currentSol, vector<Items>& bestSol, int c, int budgetLeft)
{
    //Pre-conditions:
    assert (wishListLength >= 0);
    /*Post-conditions:
      The best choice of gifts is created.
    */
    if (budgetLeft == 0)
        bestSol = currentSol;
    else if (budgetLeft < 0)
        return;
    else if (is_better_solution(currentSol, bestSol))
        bestSol = currentSol;
    if (c < wishListLength - 1 && budgetLeft > 0)
    {
        currentSol.push_back(wishList[c + 1]);
        gifts (wishListLength, wishList, currentSol, bestSol, c + 1, budgetLeft - wishList[c + 1].price);
        currentSol.pop_back();
        gifts (wishListLength, wishList, currentSol, bestSol, c + 1, budgetLeft);
    }
}

void people (string personFile, vector<Items>& shopList)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      For every person 'gifts' is calculated and shown.
    */
    vector<Items> listPerson, currentSol, bestSol;
    vector<string> person;

    int budget = read_person (person, personFile);
    make_wishlist (shopList, listPerson, person);

//  cout << "Wishlist with available products in the store with the price:" << endl;
//  for (int i = 0; i <static_cast<int>(listPerson.size()); i++)
//      cout << listPerson[i].product << "  :  " << listPerson[i].price << endl;
//  cout << endl;

    int length = static_cast<int>(listPerson.size());
    gifts (length, listPerson, currentSol, bestSol, -1, budget);

    cout << "Budget: " << budget << endl;
    for (int i = 0; i < static_cast<int>(bestSol.size()); i++)
        cout << bestSol[i].product << " : " << bestSol[i].price << endl;
    //For some reason for Fabienne 'sport langlaufski' only shows if we put a for loop after make_wishlist (the commented part).
    //If we don't use the for loop, 'mens erger je niet' is shown instead. This for loop does nothing with the code however.
    //We were told by the SA to tell this here because it worked for everyone else and he didn't know why this happened either.
}

int main ()
{
    vector<Items> shopList;

    if (!read_file (shopList))
        return -1;

    cout << "Andrew: " << endl;
    people ("Andrew.txt",   shopList);
    cout << "\nBelle: " << endl;
    people ("Belle.txt",    shopList);
    cout << "\nChris: " << endl;
    people ("Chris.txt",    shopList);
    cout << "\nDesiree: " << endl;
    people ("Desiree.txt",  shopList);
    cout << "\nEdward: " << endl;
    people ("Edward.txt",   shopList);
    cout << "\nFabienne: " << endl;
    people ("Fabienne.txt", shopList);

    return 0;
}

/*
Andrew:
Budget: 5000
spel De kolonisten van Catan : 3999
boek In de ban van de ring - reisgenoten van J.R.R. Tolkien : 950

Belle:
Budget: 2500
speelgoed stiften : 500
speelgoed tekenblok : 899
spel Mens erger je niet! : 999

Chris:
Budget: 3000
cd Synthesized van Junkie XL : 599
cd Concrete and Gold van Foo Fighters : 1899
spel kaarten : 499

Desiree:
Budget: 7500
boek Het spel van de engel van C.R. Zafon : 995
make-up mascara : 991
make-up nagellak : 499
spel Mens erger je niet! : 999
spel De kolonisten van Catan : 3999

Edward:
Budget: 45000
spel Monopoly : 2999
spel De kolonisten van Catan : 3999
Playstation 4 : 35999
boek In de ban van de ring - reisgenoten van J.R.R. Tolkien : 950
boek In de ban van de ring - de twee torens van J.R.R. Tolkien : 950

Fabienne:
Budget: 20000
spel Mens erger je niet! : 999
spel De kolonisten van Catan : 3999
cd Evenwicht van Marco Borsato : 1699
sport handbal : 1199
*/

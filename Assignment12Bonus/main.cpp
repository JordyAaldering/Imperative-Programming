// Thomas van Harskamp // s1007576 // Wiskunde & Informatica
// Jordy Aaldering     // s1004292 // Informatica

#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

struct Items
{
    int price;
    string product;
};

struct shopItems
{
    int NrItems;
    int price;
    string product;
};

bool read_file (vector<shopItems>& shopList)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      The prices and products in giftstore_bounded.txt are placed in a vector.
    */
    ifstream infile;
    infile.open("giftstore_bounded.txt");
    if (!infile)
    {   cout << "File 'giftstore_bounded.txt' could not be opened!";
        return false;
    }

    while (infile)
    {
        int NrItems, price;
        string product;
        shopItems items;

        infile >> NrItems >> price;
        getline(infile, product);
        product.erase(0, 1);

        items.NrItems = NrItems;
        items.price   = price;
        items.product = product;
        shopList.push_back(items);
    }
    shopList.pop_back();
    infile.clear();

    infile.close();
    if (!infile)
    {   cout << "File giftstore_bounded.txt could not be closed!";
        return false;
    }
    infile.clear();
    return true;
}

int read_person (vector<string>& wishList, ifstream& infile)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      Reads the wishlist and places it in a vector.
    */
    int budget;
    string garbage, product;

    infile >> budget;
    getline (infile, garbage);

    while (infile)
    {   getline(infile, product);
        wishList.push_back(product);
    }
    wishList.pop_back();
    infile.clear();

    infile.close();
    if (!infile)
        cout << "Inputfile could not be closed!";

    return budget;
}

int check_itemlist (vector<shopItems>& giftstore, string wishListItem)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      The price is returned if an item is available in the store.
    */
    int giftstoreLength = static_cast<int>(giftstore.size());
    for (int i = 0; i < giftstoreLength; i++)
        if (giftstore[i].product == wishListItem && giftstore[i].NrItems > 0)
            return giftstore[i].price;
    return 0;
}

void make_wishlist (vector<shopItems>& giftstore, vector<Items>& wishList, vector<string>& personList)
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
      Returns true if currentSol is a better solution than bestSol, else returns false.
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

void update_shoplist (vector<shopItems>& shopList, vector<Items>& bestSol)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      The list with items in the giftstore is updated with the number of items of each item decreased by 1 if the product was chosen.
    */
    for (int i = 0; i < static_cast<int> (bestSol.size()); i++)
        for (int j = 0; j < static_cast<int> (shopList.size()); j++)
            if (bestSol[i].product == shopList[j].product)
                shopList[j].NrItems--;
}

void people (ifstream& personFile, vector<shopItems>& shopList)
{
    //Pre-conditions:
    assert (true);
    /*Post-conditions:
      For every person 'gifts' is calculated and shown.
    */
    vector<Items> listPerson, currentSol, bestSol;
    vector<string> personwishes;

    int budget = read_person (personwishes, personFile);
    make_wishlist (shopList, listPerson, personwishes);

    cout << endl;

    int length = static_cast<int>(listPerson.size());
    gifts (length, listPerson, currentSol, bestSol, -1, budget);

    cout << "Budget: " << budget << endl;
    for (int i = 0; i < static_cast<int>(bestSol.size()); i++)
        cout << bestSol[i].product << " : " << bestSol[i].price << endl;
    cout << endl;

    update_shoplist (shopList, bestSol);
}

int main ()
{
    vector<shopItems> shopList;

    if (!read_file (shopList))
        return -1;
    bool stop = false;

    while (!stop)
    {
        ifstream infile;
        string inputname;
        cout << "Enter a known person's name:" << endl;
        getline(cin, inputname);
        string inputfile = inputname + ".txt";
        infile.open(inputfile.c_str());
        if (infile)
        {
            cout << inputname << ": ";
            people (infile, shopList);
        }
        else
        {
            string answer;
            cout << "Terminate program? (y/n)" << endl;
            getline(cin, answer);
            if (answer == "y")
                stop = true;
            cout << endl;
        }
        infile.clear();
    }

    return 0;
}

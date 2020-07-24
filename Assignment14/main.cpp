#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

struct Length
{
	int minutes;							//Minuten
	int seconds;							//Seconden
};

struct Track
{
	string artist;                          //Naam van uitvoerende artiest
	string cd;                              //Titel van cd
	int    year;                            //Jaar van uitgave
	int    track;							//Nummer van track
	string title;                           //Titel van track
	string tags;                            //Tags van track
	Length time;							//Lengte van track
	string country;                         //Land van artiest
};


bool operator< (const Track& a, const Track& b)
{
    return a.track < b.track;
}

bool operator== (const Track& a, const Track& b)
{
    return a.artist == b.artist;
}


istream& operator>> (istream& in, Length& lengte)
{
    char colon ;
    in >> lengte.minutes >> colon >> lengte.seconds ;
    return in ;
}

istream& operator>> (istream& infile, Track& track)
{
    string dummy;
    getline(infile,track.artist);       // artist
    getline(infile,track.cd);           // cd
    infile >> track.year ;              // year
    getline(infile, dummy) ;            // verwijder t/m newline
    infile >> track.track ;             // track nr
    getline(infile, dummy) ;            // verwijder t/m newline
    getline(infile,track.title);        // track title
    getline(infile,track.tags);         // track tags
    infile >> track.time ;              // track time
    getline(infile, dummy) ;            // verwijder t/m newline
    getline(infile,track.country);      // country
    getline(infile, dummy) ;            // verwijder t/m newline
    return infile ;
}


int size (vector<Track> v)
{
    return static_cast<int> (v.size());
}

void swap (vector<Track>& v, int  i, int  j )
{
	//Pre-conditions:
	assert (i >= 0 && j >= 0 && i < size(v) && j < size(v));
	/*Postconditions:
  	  vector[i] = old vector[j]
  	  vector[j] = old vector[i]
	*/
	const Track help = v[i];
	v[i] = v[j] ;
	v[j] = help;
}

void lower_case_convertion (string& a)
{
    //Preconditions:
    assert (true);
    /*Postconditions:
      All letters in the string are converted to lower case, to ensure the alphabetic order is correct.
    */
    int l = a.length ();
    for (int i = 0; i < l; i++)
    {
        if (a [i] >= 65 && a [i] <= 90)
            a[i] += 32;
    }
}


int Read_Songs(ifstream& infile, vector<Track>& songs)
{
    int amount = 0;

    do {
        Track next;
        infile >> next;
        if (infile)
        {
            songs.push_back(next);
            amount++;
        }
    } while (infile);

    return amount ;
}

int Read_File ()
{
    ifstream songsDBS ("Nummers.txt");
    if (!songsDBS)
    {	cout << "Kon 'Nummers.txt' niet openen." << endl;
        return -1;
    }

	int aantal = Read_Songs (songsDBS, songs);
	songsDBS.close();
	return aantal;
}

void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
    red  = first - 1;
    blue = last + 1;
    int white = last + 1;
    const Track PIVOT = data[first + (last - first) / 2];

    while (red < white - 1)
    {
        const int NEXT = white - 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            swap (data, red, NEXT) ;
        }
        else if (data[NEXT] == PIVOT)
		{
			white--;
		}
        else
        {
            white--;
            blue--;
            swap (data, NEXT, blue);
        }
    }
}

void quicksort (vector<Track>& data, int first, int last)
{
    // Pre-conditions:
    assert (first >= 0 && last < size(data));
    /*Post-conditions:
      Data[first] ... data[last] is sorted.
    */
    if (first >= last)
        return;
    else {
        int red, blue;
        dnf       (data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort (data, blue, last);
    }
}

int main ()
{
    vector<Track> data;
    int first = 0,
        last  = size (data) - 1;

    quicksort (data, first, last);
    return 0;
}

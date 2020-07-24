#define NDEBUG
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

/*
//Jordy Aaldering      // s1004292 // Informatica
//Thomas van Harskamp  // s1007576 // Informatica en Wiskunde

Zie helemaal onderaan de code voor de comments met de uitleg
*/

struct Length
{
	int minutes;							// #minuten  (0..)
	int seconds;							// #seconden (0..59)
};

struct Track
{
	string artist;                          // naam van uitvoerende artiest
	string cd;                              // titel van cd
	int    year;                            // jaar van uitgave
	int    track;							// nummer van track
	string title;                           // titel van track
	string tags;                            // tags van track
	Length time;							// lengte van track
	string country;                         // land van artiest
};

int global_counter;
typedef Track El;

bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    else
        return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    return (a.minutes == b.minutes && a.seconds == b.seconds);
}


/////////////Album ordening://////////////////////

bool operator<(const Track& a, const Track& b)
{
    global_counter++;
    if (a.artist == b.artist)
    {
        if (a.cd == b.cd)
        {
            return a.track < b.track;
        }
        else
            return a.cd < b.cd;
    }
    else
        return a.artist < b.artist;
}

bool operator==(const Track& a, const Track& b)
{
    global_counter++;
    return (a.artist == b.artist && a.cd == b.cd && a.track == b.track);
}

/////////////////End album ordening////////////////////


/////////////Length ordening://////////////////
/*
bool operator<(const Track& a, const Track& b)
{
    global_counter++;
    return a.time < b.time;
}

bool operator==(const Track& a, const Track& b)
{
    global_counter++;
    return a.time == b.time;
}
*/
/////////////////End length ordening//////////////////////


//	afgeleide ordeningen op Track waarden:
bool operator>(const Track& a, const Track& b)
{
	return b < a;
}

bool operator<=(const Track& a, const Track& b)
{
	return !(b < a);
}

bool operator>=(const Track& a, const Track& b)
{
	return b <= a;
}

istream& operator>> (istream& in, Length& lengte)
{// Preconditie:
    assert (true) ;
/*  Postconditie:
    de waarde van lengte is ingelezen uit in: eerst minuten, daarna ':', daarna seconden.
*/
    char colon ;
    in >> lengte.minutes >> colon >> lengte.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length lengte)
{
    out << lengte.minutes << ':' ;
    if (lengte.seconds < 10)
        out << '0' ;
    out << lengte.seconds ;
    return out ;
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

ostream& operator<< (ostream& out, const Track track)
{
    out << track.artist << " " << track.cd << " [" << track.track << "] (" << track.time << ")" ;
    return out ;
}

int lees_liedjes(ifstream& infile, vector<El>& liedjes)
{
    int aantal_ingelezen_liedjes = 0;
    do {
        Track volgende;
        infile >> volgende;
        if (infile)
        {
            liedjes.push_back(volgende);
            aantal_ingelezen_liedjes++;
        }
    }
    while (infile);
    return aantal_ingelezen_liedjes ;
}

int lees_bestand (string bestandnaam, vector<El>& liedjes)
{
    ifstream nummersDBS (bestandnaam.c_str());
    if (!nummersDBS)
    {
        cout << "Kon '" << bestandnaam << "' niet openen." << endl;
        return -1;
    }
    cout << "Lees '" << bestandnaam << "' in." << endl;
	int aantal = lees_liedjes (nummersDBS, liedjes);
	nummersDBS.close();
	return aantal;
}

void toon_MuziekDB (vector<El> liedjes, int aantalLiedjes)
{
    for (int i = 0 ; i < aantalLiedjes; i++)
        cout << i+1 << ". " << liedjes[i] << endl ;
}

struct Slice
{
	int from; 	// 0    <= from
	int to; 	// from <= to
};

Slice mkSlice (int from, int to)
{
//	pre-condition:
	assert (0 <= from && from <= to);
	Slice s = { from, to };
	return s;
}

bool valid_slice (Slice s)
{
	return 0 <= s.from && s.from <= s.to;
}

void swap (vector<El>& trackvector, int  i, int  j)
{
//	pre-condition:
	assert ( i >= 0 && j >= 0 );
// Post-condition: array[i] = old vector[j] and vector[j] = old vector[i]
	const El help = trackvector [i];
	trackvector [i] = trackvector [j] ;
	trackvector [j] = help;
}

void dnf (vector<El>& data, int first, int last, int& red, int& blue)
{
//  Pre-condition:
    assert (0 <= first && last < static_cast<int> (data.size()));
//  Post-condition: the data is divided in 3 three areas: smaller than pivot (red), equal to pivot (white), bigger than pivot (blue)
    red = first - 1;
    blue = last + 1;
    int white = first - 1;
    const El PIVOT = data [first + (last - first)/2];
    while (white + 1 < blue)
    {
        const int NEXT = white + 1;
        if (data[NEXT] < PIVOT)
        {
            red++;
            white++;
            swap (data, red, NEXT) ;
        }
        else if (data[NEXT]  == PIVOT)
            white++;
        else
        {
            blue--;
            swap (data, NEXT, blue);
        }
    }
}

void quicksort (vector<El>& data, int first, int last)
{
//  Pre-condition:
    assert (0 <= first && last < static_cast<int> (data.size()));
//  Post-condition: data[first] ... data[last] is sorted
    if (first >= last)
        return;
    else
    {
        int red, blue;
        dnf (data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort (data, blue, last);
    }
}

void comparison_output (ofstream& outputfile)
{
    //  Precondition:
    assert (outputfile.is_open());
    /*  Postcondition:
        The comparison counter is shown in an output file written as stars for 100000's and dots for remainders.
    */
    int i;
    for (i = global_counter; i >= 100000; i -= 100000)
        outputfile.put('*');
    if (i > 0)
        outputfile.put('.');
    outputfile.put('\n');
}

bool is_sorted (vector<El> trackvector, Slice s)
{
//	pre-condition:
	assert (valid_slice(s));	// ...and s.to < size of array
//	post-condition:
//	result is true if	array[s.from]   <= array[s.from+1]
//						array[s.from+1] <= array[s.from+2]
//						...
//						array[s.to-1]   <= array[s.to]
	bool sorted = true;
	for (int i = s.from; i < s.to && sorted; i++)
		if (trackvector[i] > trackvector[i+1])
			sorted = false;
	return sorted;
}

int find_position (vector<El> trackvector, Slice s, El y)
{
//	pre-condition:
	assert (valid_slice(s) && is_sorted(trackvector,s));    // ...and s.to < size of array
//	post-condition: s.from <= result <= s.to+1
	for (int i = s.from ; i <= s.to ; i++)
		if (y <= trackvector [i])
			return i;
	return s.to+1;
}

int find_position2 (vector<El> trackvector, Slice s, El y)
{
//	pre-condition:
	assert (valid_slice(s) && is_sorted(trackvector,s));
//	post-condition: s.from <= result <= s.to+1
	for (int i = s.to ; i >= s.from ; i--)
		if (y >= trackvector [i])
			return i+1;
	return s.from;
}

void shift_right (vector<El>& trackvector, Slice s)
{
//	pre-condition:
	assert (valid_slice (s));	// ... and s.to < size (array) - 1
//	post-condition:  array[s.from+1]	= 	old array[s.from]
//			    	 array[s.from+2]	= 	old array[s.from+1]
//						...
//			    	 array[s.to+1]		= 	old array[s.to]
	for (int i = s.to+1; i > s.from ; i--)
		trackvector [i]  = trackvector [i-1];
}

void insert (vector<El>& trackvector, int& length, El y)
{
	const int pos = find_position (trackvector, mkSlice (0, length-1), y);
	if (pos < length)
		shift_right (trackvector, mkSlice (pos, length-1));
	trackvector [pos] = y;
	length++;
}

void insert2 (vector<El>& trackvector, int& length, El y)
{
	const int pos = find_position2 (trackvector, mkSlice (0, length-1), y);
	if (pos < length)
		shift_right (trackvector, mkSlice (pos, length-1));
	trackvector [pos] = y;
	length++;
}

//	array-based insertion sort:
void insertion_sort (vector<El>& trackvector, int length, ofstream& outputfile)
{
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( trackvector, sorted, trackvector[sorted] ) ;
        if (sorted % 100 == 99)
            comparison_output(outputfile);
    }
}

//Array-based insertion sort:
void insertion_sort2 (vector<El>& trackvector, int length, ofstream& outputfile)
{
	int sorted = 1;
    while (sorted < length)
    {   insert2 (trackvector, sorted, trackvector[sorted]);
        if (sorted % 100 == 99)
            comparison_output(outputfile);
    }
}

//	array-based selection sort:
int smallest_value_at (vector<El> trackvector, Slice s)
{
//	pre-condition:
	assert (valid_slice (s)) ;	// ... and s.to < size (s)
//	Post-condition: s.from <= result <= s.to and array[result] is
//	the minimum value of array[s.from] .. array[s.to]
	int  smallest_at = s.from ;
	for ( int index = s.from+1 ; index <= s.to ; index++ )
		if ( trackvector [index] < trackvector [smallest_at] )
			smallest_at = index ;
	return smallest_at ;
}

void selection_sort (vector<El>& trackvector, int length, ofstream& outputfile)
{	for ( int unsorted = 0 ; unsorted < length ; unsorted++ )
	{   const int k = smallest_value_at (trackvector, mkSlice (unsorted, length-1));
	    swap ( trackvector, unsorted, k ) ;
	    if ((length - 1 - unsorted) % 100 == 99)
            comparison_output(outputfile);
	}
}

bool bubble (vector<El>& trackvector, Slice s)
{
//	pre-condition:
	assert (valid_slice(s));	// ... and s.to < size(array)
//	Post-condition:
//	maximum of array[s.from]..array[s.to] is at array[s.to]
//	if result is true then sorted( array, s )
	bool is_sorted = true ;
	for ( int i = s.from ; i < s.to ; i++)
	    if (trackvector [i] > trackvector [i+1])
		{	swap ( trackvector, i, i+1 ) ;
			is_sorted = false ;
		}
	return is_sorted ;
}

void bubble_sort (vector<El>& trackvector, int length, ofstream& outputfile)
{
    int n;
    n = static_cast<int> (trackvector.size());
    while ( !bubble ( trackvector, mkSlice (0, length-1 ) ) )
    {
        if ((n - 1 - length) % 100 == 99)
            comparison_output(outputfile);
        length-- ;
    }
}

int main()
{
    vector <El> liedjes;
	int aantalLiedjes = lees_bestand ("Nummers.txt", liedjes);
	if (aantalLiedjes < 0)
	{
        cout << "Bestand inlezen mislukt. Programma termineert." << endl;
	    return aantalLiedjes;
    }

    ofstream outputfile;
    global_counter = 0;

    quicksort(liedjes, 0, aantalLiedjes - 1);
    //outputfile.open("insertion.txt"); insertion_sort(liedjes,aantalLiedjes,outputfile) ;
    //outputfile.open("insertion2.txt"); insertion_sort2(liedjes,aantalLiedjes,outputfile) ;
    //outputfile.open("selection.txt"); selection_sort(liedjes,aantalLiedjes,outputfile) ;
    //outputfile.open("bubble.txt"); bubble_sort   (liedjes,aantalLiedjes,outputfile) ;

    cout << "Bestand gesorteerd." << endl;
    toon_MuziekDB (liedjes,aantalLiedjes);

    cout << "Number of comparison operations: " << global_counter << endl;
	return 0;
}

/*
Number of comparison operations for:    Insertion sort      Alternative insertion sort      Selection sort      Bubble sort     Quicksort
Sorting by album                        15797254            17253                           15806253            402228          101069
Sorting by length                       7823428             7950312                         15806253            15800582        81468

These results are quite accurate, because insertion, alternative insertion, selection and bubble sort all have an average complexity of O(n^2),
while quicksort has an average complexity of n*2log(n). Quicksort is also the fastest by far in terms of average comparison operations, this only confirms
that quicksort is the champion of these sorting algorithms.

*/

//Jordy Aaldering     // s1004292 // Informatica
//Thomas van Harskamp // s1007576 // Informatica & Wiskunde

#define NDEBUG
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

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

struct Slice
{
	int from;
	int to;
};

vector <Track> liedjes;
int comparison_counter;
typedef Track El;


int size (vector<Track> v)
{
	//Precondition:
    assert (true);
    /*Postcondition:
      The size of the vector is returned.
    */
    return static_cast<int> (v.size());
}

int vSize (vector<int> v)
{
	//Precondition:
    assert (true);
    /*Postcondition:
      The size of the vector is returned.
    */
    return static_cast<int> (v.size());
}

void lower_case_convertion (string& a)
{
    //Precondition:
    assert (true);
    /*Postcondition:
      All letters in the string are converted to lower case, to ensure the alphabetic order is correct.
    */
    int l = a.length ();
    for (int i = 0; i < l; i++)
    {
        if (a [i] >= 65 && a [i] <= 90)
            a[i] += 32;
    }
}


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

///////////////This is the code for part 1.1///////////////
bool operator<(const Track& A, const Track& B)
{
    comparison_counter++;
    Track a = A, b = B;
    lower_case_convertion (a.artist);
    lower_case_convertion (b.artist);
    lower_case_convertion (a.cd);
    lower_case_convertion (b.cd);

    if (a.artist == b.artist)
    {
        if (a.cd == b.cd)
            return a.track < b.track;
        else
            return a.cd < b.cd;
    }
    else
        return a.artist < b.artist;
}
///////////////End code for part 1.1///////////////

/*//////////////This is the code for part 1.2///////////////
bool operator<(const Track& A, const Track& B)
{
    comparison_counter++;
    Track a = A, b = B;
    lower_case_convertion (a.artist);
    lower_case_convertion (b.artist);
    lower_case_convertion (a.cd);
    lower_case_convertion (b.cd);
	if (a.time == b.time)
	{
		if (a.artist == b.artist)
		{
			if (a.cd == b.cd)
				return a.track < b.track;
			else
				return a.cd < b.cd;
		}
		else
			return a.artist < b.artist;
	}
	else
		return a.time < b.time;
}
*///////////////End code for part 1.2///////////////


bool operator==(const Track& a, const Track& b)
{
	comparison_counter++;
	return (a.time == b.time && a.artist == b.artist && a.title == b.title && a.cd == b.cd);
}

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
{
    char colon;
    in >> lengte.minutes >> colon >> lengte.seconds;
    return in;
}

ostream& operator<< (ostream& out, const Length lengte)
{
    out << lengte.minutes << ':';
    if (lengte.seconds < 10)
        out << '0';
    out << lengte.seconds;
    return out;
}

istream& operator>> (istream& infile, Track& track)
{
    string dummy;
    getline(infile,track.artist);       //Artist
    getline(infile,track.cd);           //Cd
    infile >> track.year ;              //Year
    getline(infile, dummy) ;            //Verwijder t/m newline
    infile >> track.track ;             //Track nr
    getline(infile, dummy) ;            //Verwijder t/m newline
    getline(infile,track.title);        //Track title
    getline(infile,track.tags);         //Track tags
    infile >> track.time ;              //Track time
    getline(infile, dummy) ;            //Verwijder t/m newline
    getline(infile,track.country);      //Country
    getline(infile, dummy) ;            //Verwijder t/m newline
    return infile ;
}

ostream& operator<< (ostream& out, const Track track)
{
    out << track.artist << " - " << track.cd << " [" << track.track << "] (" << track.time << ")";
    return out;
}


int lees_liedjes(ifstream& infile, vector<Track>& liedjes)
{
	//Preconditions:
    assert (true);
    /*Postconditions:
      The songs are read.
    */
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
    return aantal_ingelezen_liedjes;
}

int lees_bestand (string bestandnaam)
{
	//Preconditions:
    assert (true);
    /*Postconditions:
      The file is read.
    */
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

void show_vector (vector<Track> liedjes, int aantalLiedjes)
{
	//Preconditions:
    assert (aantalLiedjes >= 0);
    /*Postconditions:
      The vector is shown.
    */
    for (int i = 0 ; i < aantalLiedjes; i++)
        cout << i+1 << ". " << liedjes[i] << endl ;
}

Slice mkSlice (int from, int to)
{
	//Preconditions:
    assert (from >= 0 && to >= from);
    /*Postconditions:
      A slice is made.
    */
	Slice s = { from, to };
	return s;
}

bool valid_slice (Slice s)
{
	//Preconditions:
    assert (true);
    /*Postconditions:
      The slice is checked.
    */
	return 0 <= s.from && s.from <= s.to;
}

void comparison_output (ofstream& outputfile)
{
    //  Precondition:
    assert (outputfile.is_open());
    /*  Postcondition:
        The comparison counter is shown in an output file written as stars for 100000's and dots for remainders.
    */
    int i;
    for (i = comparison_counter; i >= 100000; i -= 100000)
        outputfile.put('*');
    if (i > 0)
        outputfile.put('.');
    outputfile.put('\n');
}

bool is_sorted (vector<El> trackvector, Slice s)
{
    //Preconditions:
	assert (valid_slice(s));
	/*postconditions:
      Result is true if	array[s.from]   <= array[s.from+1]
						array[s.from+1] <= array[s.from+2]
                                       ....
						array[s.to-1]   <= array[s.to]
    */
	bool sorted = true;
	for (int i = s.from; i < s.to && sorted; i++)
		if (trackvector[i] > trackvector[i + 1])
			sorted = false;
	return sorted;
}

int find_position (vector<El> trackvector, Slice s, El y)
{
    //Preconditions:
	assert (valid_slice(s) && is_sorted(trackvector,s));
    /*Postconditions:
      s.from <= result <= s.to+1
    */
	for (int i = s.from ; i <= s.to ; i++)
		if (y <= trackvector [i])
			return i;
	return s.to+1;
}

void shift_right (vector<El>& trackvector, Slice s)
{
    //Preconditions:
	assert (valid_slice (s));
    /*Postconditions:
      array[s.from+1] = old array[s.from]
      array[s.from+2] = old array[s.from+1]
                     ...
      array[s.to+1]	  = old array[s.to]
    */
	for (int i = s.to+1; i > s.from ; i--)
		trackvector [i]  = trackvector [i-1];
}

void swap (vector<El>& trackvector, int  i, int  j)
{
	//Preconditions:
	assert ( i >= 0 && j >= 0 );
	/*Postconditions:
	array[i] = old array[j]
	array[j] = old array[i]
	*/
	const El help = trackvector [i];
	trackvector [i] = trackvector [j] ;
	trackvector [j] = help;
}

void insert (vector<El>& trackvector, int& length, El y)
{
	//Preconditions:
    assert (length >= 0);
    /*Postconditions:
      The vector is sorted.
    */
	const int pos = find_position (trackvector, mkSlice (0, length-1), y);
	if (pos < length)
		shift_right (trackvector, mkSlice (pos, length-1));
	trackvector [pos] = y;
	length++;
}

void insertion_sort (vector<El>& trackvector, int length, ofstream& outputfile)
{
	//Preconditions:
    assert (length >= 0);
    /*Postconditions:
      The vector is sorted.
    */
	int sorted = 1 ;
    while ( sorted < length )
    {   insert ( trackvector, sorted, trackvector[sorted] ) ;
        //if (sorted % 100 == 99)
        //    comparison_output(outputfile);
    }
}

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
	//Preconditions:
    assert (length >= 0);
    /*Postconditions:
      The vector is sorted.
    */
    int n;
    n = size(trackvector);
    while ( !bubble ( trackvector, mkSlice (0, length-1 ) ) )
    {
        if ((n - 1 - length) % 100 == 99)
            comparison_output(outputfile);
        length-- ;
    }
}

bool push_up (vector<El>& tree, int treeSize)
{
    //  Pre-condition:
    assert (true);
    /*  Post-condition:
        If a child is larger than its parent, the two are swapped.
    */
    bool isSorted = true;

    for (int childPos = 0; childPos < treeSize; childPos++)
    {
        int parentPos = 0;
        if  (childPos > 2)
            parentPos = (childPos - 1) / 2;

        if (tree[childPos] > tree[parentPos])
        {
            isSorted = false;
            swap (tree, childPos, parentPos);
        }
    }
    return isSorted;
}

void push_down (vector<El>& tree, int heapSize)
{
    //Preconditions:
    assert (heapSize >= 0);
    /*Postconditions:
      The parent keeps swapping with its largest child,
      as long as the value of the parent is lower than that child.
    */
    int parentPos = 0, child1Pos = 1, child2Pos = 2;

    while ((tree[parentPos] < tree[child1Pos] || tree[parentPos] < tree[child2Pos]) && child2Pos < heapSize)
    {
        if (tree[child1Pos] > tree[child2Pos])
        {
            swap (tree, parentPos, child1Pos);
            parentPos = child1Pos;
        }
        else
        {
            swap (tree, parentPos, child2Pos);
            parentPos = child2Pos;
        }
        child1Pos = 2 * parentPos + 1;
        child2Pos = child1Pos + 1;
    }
}

void show_heap (vector<El>& tree, int treeSize)
{
    //Preconditions:
    assert (true);
    /*Postconditions:
      The tree is shown to the user.
    */
    cout << "Heap:";
    for (int i = 0; i < treeSize; i++)
    	cout << tree[i].artist << endl;
}

void heap_sort (vector<El>& tree, int treeSize, ofstream& outputfile)
{
	//Preconditions:
    assert (treeSize >= 0);
    /*Postconditions:
      The vector is sorted.
    */
	while (!push_up(tree, treeSize));
	show_heap (tree, treeSize);
	for (int heapSize = treeSize - 1; heapSize > 1; heapSize--)
	{
		swap (tree, 0, heapSize);
		push_down (tree, heapSize - 1);
	}
	show_heap (tree, treeSize);
}


/*//////////////This is the code for part 1///////////////
void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
	//Preconditions:
	assert (first >= 0 && last >= 0 && red >= 0 && blue >= 0);
	//Postconditions:
	//The vector is sorted.

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
			white--;
        else
        {
            white--;
            blue--;
            swap (data, NEXT, blue);
        }
    }
}
*///////////////End code for part 1///////////////

///////////////This is the code for part 2///////////////
void dnf (vector<Track>& data, int first, int last, int& red, int& blue)
{
	//Preconditions:
    assert (first >= 0 && last >= 0 && red >= 0 && blue >= 0);
    //Postconditions:
    //The vector is sorted.

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
			white--;
        else
        {
            white--;
            blue--;
            swap (data, NEXT, blue);
        }
    }
}
///////////////End code for part 2///////////////


void quicksort (vector<Track>& data, int first, int last)
{
    // Pre-conditions:
    assert (first >= 0 && last < size(data));
    /*Post-conditions:
      Data[first] ... data[last] is sorted.
    */
    if (first >= last)
        return;
    else
	{
        int red, blue;
        dnf       (data, first, last, red, blue);
        quicksort (data, first, red);
        quicksort (data, blue, last);
    }
}

enum Sorteermethode {Insertion,Selection,Bubble,Heap,DNF,AantalMethoden};
string sorteermethode [] = {"insertion", "selection", "bubble", "heap", "DNF"} ;

Sorteermethode selecteer ()
{
	//Preconditions:
    assert (true);
    /*Postconditions:
      A sorting mode is selected.
    */
    cout << "Kies een sorteermethode: " << endl ;
    for (int m = 0; m < AantalMethoden; m++)
        cout << m+1 << ": " << sorteermethode[m] << " sort" << endl ;
    int keuze ;
    cin >> keuze ;
    return static_cast<Sorteermethode>(keuze - 1) ;
}

int main()
{
	int aantalLiedjes = lees_bestand ("Nummers.txt");
	if (aantalLiedjes < 0)
	{   cout << "Bestand inlezen mislukt. Programma termineert." << endl;
	    return aantalLiedjes;
    }

    ofstream outputfile;
    Sorteermethode m = selecteer ();
    cout << endl << "Sorteren bestand met " << sorteermethode[m] << " sort." << endl;
    comparison_counter = 0;

    switch (m)
    {
		case Insertion: outputfile.open("insertion.txt"); insertion_sort(liedjes,aantalLiedjes,outputfile); break;
        case Selection: outputfile.open("selection.txt"); selection_sort(liedjes,aantalLiedjes,outputfile); break;
        case Bubble:    outputfile.open("bubble.txt");    bubble_sort   (liedjes,aantalLiedjes,outputfile); break;
		case Heap:		outputfile.open("heap.txt");      heap_sort     (liedjes,aantalLiedjes,outputfile); break;
		case DNF:       outputfile.open("DNF.txt");		  quicksort     (liedjes,0,size(liedjes)-1);        break;
		default:        cout << "Huh?" << endl;
    }
    cout << "Bestand gesorteerd." << endl << endl;

    show_vector (liedjes,aantalLiedjes);
    cout << endl << "Number of comparison operations: " << comparison_counter << endl;
	return 0;
}


///////////////This is the code for part 3///////////////
int largest (vector<El>& v, int low, int up)
{
	if ( low >= up )
		return low;
	else
	{
		const int POS = largest (v, low + 1, up);
		if (v [low] > v [POS])
			return low;
		else
			return POS;
	}
}

void sort (vector<El>& v, int n)
{
	if (n > 1)
	{
		const int POS = largest (v, 0, n - 1);
		swap (v, POS, n - 1);
		sort (v, n - 1);
	}
}

int largest2 (vector<El>& v, int low, int up)
{
	vector<int> stack;

    while (low < up)
	{
        stack.push_back(low);
        low++;
    }
    int res = low;
    while (vSize(stack) == 0)
	{
        low = stack[vSize(stack) - 1];
        stack.pop_back();
		if (v[res] <= v[low])
			res = low;
    }
    return res;
}

void sort2 (vector<El>& v, int n)
{
	while (n > 1)
	{
		n--;
		const int POS = largest2 (v, 0, n);
		swap (v, POS, n);
	}
}
///////////////End code for part 3///////////////

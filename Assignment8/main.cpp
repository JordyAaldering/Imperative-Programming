// Jordy Aaldering      // s1004292 // Informatica
// Thomas van Harskamp  // s1007576 // Informatica en Wiskunde

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <iomanip>
using namespace std;

int amountOfSongs;
struct Length
{   int minutes;							// #minutes (0..)
	int seconds;							// #seconds (0..59)
};

struct Track
{   string artist;                          // name of artist
	string cd;                              // cd title
	int year;                               // year of appearance (if known)
	int track;							    // track number
	string title;                           // track title
	string tags;                            // tags
	string time;							// playing time
	string country;                         // main countr(y/ies) of artist
};

struct TrackDisplay
{   bool showArtist;				    // if true, show name of artist
	bool showAlbum;					// if true, show cd title
	bool showYear;					// if true, show year of appearance
	bool showTrack;					// if true, show track number
	bool showTitle;					// if true, show track title
	bool showTags;                   // if true, show tags
	bool showLength;				    // if true, show playing time
	bool showCountry;                // if true, show countr(y/ies) of artist
};

bool match (string sub, string source)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    Result is true only if sub is a literal (case sensitive) sub string of source.
*/  return source.find(sub) != string::npos ;
}

ostream& operator<< (ostream& out, const Length length)
{// Precondition:
    assert (length.minutes >= 0 && length.seconds >= 0) ;
/*  Postcondition:
    The value of length is shown via out in the format: minutes, ':', seconds (two digits)
*/  out.fill('0');
    out << setw (2) << length.minutes << ':' << setw (2) << length.seconds;
    return out;
}

istream& operator>> (istream& in, Length& length)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    The value of length has been read from in: first minutes, then ':', then seconds
*/  char colon;
    in >> length.minutes >> colon >> length.seconds;
    return in;
}

Length operator+ (const Length& a, const Length& b)
{// Precondition:
    assert (a.minutes >= 0 && a.seconds >= 0 && a.seconds < 60 && b.minutes >= 0 && b.seconds >= 0 && b.seconds < 60) ;
/*  Postcondition:
    Result is the sum of a and b.
*/  Length sum;
    sum.minutes = a.minutes + b.minutes;
    sum.seconds = a.seconds + b.seconds;
    if (sum.seconds >= 60)
    {   sum.minutes++;
        sum.seconds -= 60;
    }   return sum;
}

istream& operator>> (istream& in, Track& track)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    The content of the first 8 lines from in have been read and are stored in the corresponding members of track.
    The following (empty) line from in has also been read.
*/  in  >> track.artist
        >> track.cd
        >> track.year
        >> track.title
        >> track.tags
        >> track.time
        >> track.country;
    return in;
}

void user_input (TrackDisplay& td)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    All values from trackdisplay are either set to true or false.
    */
    string answer;

    cout << "y/n\nShow artist?: ";
    getline(cin, answer);
    if (answer == "n") td.showArtist = false;
    else td.showArtist = true;

    cout << "Show album?: ";
    getline(cin, answer);
    if (answer == "n") td.showAlbum = false;
    else td.showAlbum = true;

    cout << "Show year?: ";
    getline(cin, answer);
    if (answer == "n") td.showYear = false;
    else td.showYear = true;

    cout << "Show title?: ";
    getline(cin, answer);
    if (answer == "n") td.showTitle = false;
    else td.showTitle = true;

    cout << "Show tags?: ";
    getline(cin, answer);
    if (answer == "n") td.showTags = false;
    else td.showTags = true;

    cout << "Show track?: ";
    getline(cin, answer);
    if (answer == "n") td.showTrack = false;
    else td.showTrack = true;

    cout << "Show time?: ";
    getline(cin, answer);
    if (answer == "n") td.showLength = false;
    else td.showLength = true;

    cout << "Show country?: ";
    getline(cin, answer);
    if (answer == "n") td.showCountry = false;
    else td.showCountry = true;
}

void show_track (Track track, TrackDisplay td, vector<Track>& tracks, int i)
{// Precondition:
    assert (true) ;
/*  Postcondition:
    Only the members of track are shown for which the corresponding member in td is true.
*/
    if (td.showArtist)
        cout << "Artist: " << tracks[i].artist << endl;
    if (td.showAlbum)
        cout << "Album: " << tracks[i].cd << endl;
    if (td.showYear)
        cout << "Year: " << tracks[i].year << endl;
    if (td.showTrack)
        cout << "Track: " << tracks[i].track << endl;
    if (td.showTitle)
        cout << "Title: " << tracks[i].title << endl;
    if (td.showTags)
        cout << "Tags: " << tracks[i].tags << endl;
    if (td.showLength)
        cout << "Length: " << tracks[i].time << endl;
    if (td.showCountry)
        cout << "Country: " << tracks[i].country << endl;
    cout << endl;
}

void read_file (Track track, vector<Track>& tracks, ifstream& infile)
{   //Pre-conditions:
    assert (infile.is_open());
    /*Post-conditions:
    All content from Nummers.txt is read and placed in a vector.
    */
    string line;

    while (getline(infile, line))
    {
        track.artist = line;
        getline(infile, line);
        track.cd = line;
        getline(infile, line);
        track.year = atoi(line.c_str());
        getline(infile, line);
        track.track = atoi(line.c_str());
        getline(infile, line);
        track.title = line;
        getline(infile, line);
        track.tags = line;
        getline(infile, line);
        track.time = line;
        getline(infile, line);
        track.country = line;
        getline(infile, line);
        tracks.push_back(track);
    }
}

void match_track_user_input (string& trackinput, bool& display)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    The value of display is set to true if the user enters y and is set to false if the user enters n.
    */
    cout << "What word(s) would you like to search in the titles?: ";
    getline(cin, trackinput);
    cout << "Would you like to show these files? (y/n): ";
    string yn;
    getline (cin, yn);
    if (yn == "n")
        display = false;
    else
        display = true;
}

int match_tracks (Track track, vector<Track>& tracks, TrackDisplay td, string inputtrack, bool display)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    The tracks are compared to the user input and are shown if they are similar and display is true.
    */
    td.showArtist = true;
    td.showAlbum = true;
    td.showYear = true;
    td.showTrack = true;
    td.showTitle = true;
    td.showTags = true;
    td.showLength = true;
    td.showCountry = true;

    int matches = 0;
    for (int i = 0; i < amountOfSongs; i++)
    {
        if (match(inputtrack, tracks[i].title))
        {
            matches++;
            if (display)
                show_track(track, td, tracks, i);
        }
    }
    if (display)
        cout << "Amount of matches: " << matches << endl << endl;
    return matches;
}

void match_artist_user_input (string& artistinput, bool& display)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    The value of display is set to true if the user enters y and is set to false if the user enters n.
    */
    cout << "What word(s) would you like to search in the artists?: ";
    getline(cin, artistinput);
    cout << "Would you like to show these files? (y/n): ";
    string yn;
    getline (cin, yn);
    if (yn == "n")
        display = false;
    else
        display = true;
}

bool artist_not_double (string foundArtists[10000], string artist, int matches)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    The function checks if the artist has already been found and returns false if this is the case.
    */
    for (int i = 0; i < matches; i++)
    {
        if (foundArtists[i] == artist)
            return false;
    }
    return true;
}

int match_artists (Track track, TrackDisplay td, vector<Track>& tracks, string artist, bool display)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    The artists are compared to the user input and are shown if they are similar and display is true.
    If display is true the amount of matches is shown.
    */

    td.showArtist = true;
    td.showAlbum = false;
    td.showYear = false;
    td.showTrack = false;
    td.showTitle = false;
    td.showTags = false;
    td.showLength = false;
    td.showCountry = false;

    int matches = 0;
    string foundArtists[amountOfSongs];
    for (int i = 0; i < amountOfSongs; i++)
    {
        if (match(artist, tracks[i].artist) && artist_not_double(foundArtists, tracks[i].artist, matches))
        {
            foundArtists[matches] = tracks[i].artist;
            matches++;
            if (display)
                show_track(track, td, tracks, i);
        }
    }
    if (display)
        cout << "Amount of matches: " << matches << endl << endl;
    return matches;
}

void match_cd_user_input (string& cdinput, bool& display)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    The value of display is set to true if the user enters y and is set to false if the user enters n.
    */
    cout << "What artist(s) would you like to search cd's of?: ";
    getline(cin, cdinput);
    cout << "Would you like to show these files? (y/n): ";
    string yn;
    getline (cin, yn);
    if (yn == "n")
        display = false;
    else
        display = true;
}

bool find_artist (vector<Track>& tracks, string artistname)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    The artists are compared to the user input and are shown if they are similar and display is true.
    */
    for (int i = 0; i < amountOfSongs; i++)
        if (tracks[i].artist == artistname)
            return true;
    return false;
}

bool cd_not_double (string foundCds[10000], string cd, int matches)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    False is returned if cd is already in the list of found cds.
    Else true is returned.
    */

    for (int i = 0; i < matches; i++)
    {
        if (foundCds[i] == cd)
            return false;
    }
    return true;
}

int match_cds (Track track, TrackDisplay td, vector<Track>& tracks, string artistname, bool display)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    The artists are compared to the artist of the user input and their cds, artist name and cd year are shown if they are similar and display is true.
    */
    td.showArtist = true;
    td.showAlbum = true;
    td.showYear = true;
    td.showTrack = false;
    td.showTitle = false;
    td.showTags = false;
    td.showLength = false;
    td.showCountry = false;

    int matches = 0;
    string foundCds[amountOfSongs];
    if (find_artist (tracks, artistname))
    {
        for (int i = 0; i < amountOfSongs; i++)
        {
            if (cd_not_double(foundCds, tracks[i].cd, matches) && tracks[i].artist == artistname)
            {
                foundCds[matches] = tracks[i].cd;
                if (display)
                    show_track (track, td, tracks, i);
                matches++;
            }
        }
    }
    else
        cout << "No artist found!" << endl;
    if (display)
        cout << "Matches found: " << matches;
    return matches;
}

int number_of_cds (vector<Track>& tracks)
{   //Pre-conditions:
    assert (true);
    /*Post-conditions:
    The number of unique cds is counted and returned.
    */
    string foundCds[amountOfSongs];
    int matches = 0;

    for (int i = 0; i < amountOfSongs; i++)
    {
        if (cd_not_double(foundCds, tracks[i].cd, matches))
        {
            foundCds[matches] = tracks[i].cd;
            matches++;
        }
    }
    return matches;
}

int main()
{// Precondition:
    assert (true) ;
/*  Postcondition:
    the music database "Nummers.txt" has been read (if present and correctly formatted).
    The assignment queries have been executed and their result has been shown on screen.
    In case of the bonus assignment, the user has been able to query the database and has
    seen the results of these queries.
*/
 	cout << "fnijdsinfjsnkjfnskjkfsk" << endl;
	Track track;
    TrackDisplay td;
    vector<Track> tracks;
    string trackInput, artistInput, cdInput;
    bool trackDisplay, artistDisplay, cdDisplay;

    user_input (td);

    ifstream infile;
    infile.open("Nummers.txt");
    string line;
    read_file (track, tracks, infile);
    amountOfSongs = tracks.size();
    infile.close();
    if (!infile)
        cout << "File could not be closed.";

    for (int i = 0; i < amountOfSongs; i++)
        show_track (track, td, tracks, i);

    match_track_user_input (trackInput, trackDisplay);
    match_tracks(track, tracks, td, trackInput, trackDisplay);

    match_artist_user_input (artistInput, artistDisplay);
    match_artists (track, td, tracks, artistInput, artistDisplay);

    match_cd_user_input (cdInput, cdDisplay);
    match_cds (track, td, tracks, cdInput, cdDisplay);

    number_of_cds (tracks);

	return 0;
}

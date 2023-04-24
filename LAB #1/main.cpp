#include <iostream>
#include "Playlist.h"
using namespace std;


void optionScreen(Playlist*);

/* The main function allows the user to input their choice,
   whilst also calling the option screen recursively */
   
int main() {
    string playlistTitle;
    char option;
    
    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistTitle);
    cout << endl;
    
    Playlist* playlist = new Playlist(playlistTitle);

    optionScreen(playlist);

    cin >> option;

    while (option != 'q'){
        if (option == 'a'){
            playlist->addSong();
        } else if (option == 'd'){
            playlist->RemoveSong();      
        } else if (option == 'c'){
            playlist->SwitchPos();
        } else if (option == 's'){
            playlist->OutputSpecificArtist();
        } else if (option == 't'){
            playlist->TotalTime();
        } else if (option == 'o'){
            playlist->PrintPlaylist();
        } else {
            cout << "Enter valid option." << endl;
        }

        optionScreen(playlist);
        cin >> option;
    }
}

// optionScreen used to display options for user to choose for their playlist
void optionScreen(Playlist* playlist){
    cout << playlist->GetPlaylistName() << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:";
    cout << endl;
}



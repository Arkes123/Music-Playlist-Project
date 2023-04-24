#include <iostream>
using namespace std;

/** PlaylistNode class defines the structure and functions for
    the individual songs in the playlist. **/

class PlaylistNode { 
public:
    PlaylistNode();
    
    PlaylistNode(string, string, string, int);
    void InsertAfter(PlaylistNode*);
    void SetNext(PlaylistNode*);
    string GetID() const;
    string GetSongName() const;
    string GetArtistName() const;
    PlaylistNode* GetNext() const;
    int GetSongLength() const;
    void PrintPlaylistNode() const;
    
private:
    string unqiueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
};

/* Playlist class defines the structure and functions for the operations
   that the user will conduct on each song (e.g. adding a song, removing, etc.) */
class Playlist {
 public:
    Playlist(string);
    PlaylistNode* GetNode(string);
    string GetPlaylistName() const;
    void addSong();
    void PrintPlaylist();
    void SwitchPos();
    int GetSongCount();
    PlaylistNode* GetSong(int);
    void RemoveSong();
    void OutputSpecificArtist();
    void TotalTime() const;
    void optionScreen();
 private:
    PlaylistNode* head;
    PlaylistNode* tail;
    string playlistName;
};
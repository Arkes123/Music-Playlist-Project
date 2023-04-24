#include <iostream>
#include "Playlist.h"


//The constructor for each song in the playlist
PlaylistNode::PlaylistNode() {
    this->unqiueID = "none";
    this->songName = "none";
    this->artistName = "none";
    this->songLength = 0;
    this->nextNodePtr = nullptr;
}

//This is another constructor for a new PlaylistNode thats paramatized with characteristics to each song
PlaylistNode::PlaylistNode(string ID, string songName, string artistName, int length)
{
    this->unqiueID = ID;
    this->songName = songName;
    this->artistName = artistName;
    this->songLength = length;
    this->nextNodePtr = nullptr;
}

//Constructs a playlist object that is passed in a string that represents the name of the playlist
Playlist::Playlist(string playlistName){
    this->head = nullptr;
    this->tail = nullptr;
    this->playlistName = playlistName;
}

//InsertAfter passes in a song node and creates a new node to insert after it
void PlaylistNode::InsertAfter(PlaylistNode* nodeLoc) {
    PlaylistNode* temp = nullptr;
    temp = this->nextNodePtr;
    this->nextNodePtr = nodeLoc;
    nodeLoc->SetNext(temp);
}

//Sets the nextNodePtr to a another given song in the playlist
void PlaylistNode::SetNext(PlaylistNode* nodeLoc) {
    this->nextNodePtr = nodeLoc;
}

//Retuns the unique ID of a given song in the playlist
string PlaylistNode::GetID() const {
    return this->unqiueID;
}

//Returns the next node pointer of a given son in the playlist
PlaylistNode* PlaylistNode::GetNext() const {
    return this->nextNodePtr;
}

//Returns the name of a given song in the playlist
string PlaylistNode::GetSongName() const {
    return this->songName;
}

//Returns the name of an artist for a given song in the playlist
string PlaylistNode::GetArtistName() const {
    return this->artistName;
}

//Returns the song length of a given song in the playlist
int PlaylistNode::GetSongLength() const {
    return this->songLength;
}

//Simply prints the id, song name, artist name, and song length of a given song in the playlist
void PlaylistNode::PrintPlaylistNode() const {
    cout << "Unique ID: " << this->unqiueID << endl;
    cout << "Song Name: " << this->songName << endl;
    cout << "Artist Name: " << this->artistName << endl;
    cout << "Song Length (in seconds): " << this->songLength << endl;
    cout << endl;
}

//Returns the name of the playlist
string Playlist::GetPlaylistName() const {
    return this->playlistName;
}

//addSong adds a new song to the playlist
void Playlist::addSong() {
    string id;
    string nameOfSong;
    string nameOfArtist;
    PlaylistNode* newSong;
    int length;
    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin >> id;
    cin.ignore();
    cout << "Enter song's name:" << endl;
    getline(cin, nameOfSong);
    cout << "Enter artist's name:" << endl;
    getline(cin, nameOfArtist);
    cout << "Enter song's length (in seconds):" << endl;
    cin >> length;
    cout << endl;

    newSong = new PlaylistNode(id, nameOfSong, nameOfArtist, length);

    if (head == nullptr) {
        head = newSong;
        tail = newSong;
    } else {
        tail->InsertAfter(newSong);
        tail = newSong;
    }

}

//Returns the pointer to a given song in a playlist that utilizes a passed in position
PlaylistNode* Playlist::GetSong(int pos) {
    int counter = 1;
    PlaylistNode* tmp = head;
    while (counter != pos){
        tmp = tmp->GetNext();
        counter++;
    }

    return tmp;
}

//Returns the integer count of the amonut of songs in the playlist
int Playlist::GetSongCount() {
    int count = 1;
    PlaylistNode* countSong = head;

    while (countSong){
        countSong = countSong->GetNext();
        count++;
    }

    return count;
}

//Prints the entire playlist to stdout
void Playlist::PrintPlaylist() {
    cout << playlistName << " - OUTPUT FULL PLAYLIST" << endl;
    int counter = 1;
    if (head == nullptr) {
        cout << "Playlist is empty" << endl;
        cout << endl;
    } else {
        PlaylistNode* currSong = head;
        while (currSong) {
            cout << counter << "." << endl;
            currSong->PrintPlaylistNode();
            currSong = currSong->GetNext();
            counter++;
        }
    }
}

//This function switches the position of a given song to a target position inputted by the user
void Playlist::SwitchPos() {

    int NodeCount = GetSongCount();
    int prevPos;
    int newPos;

    cout << "CHANGE POSITION OF SONG" << endl;
    cout << "Enter song's position:" << endl;
    cin >> prevPos;
    cout << "Enter new position for song:" << endl;
    cin >> newPos;
    cin.ignore();

    PlaylistNode* currPosition = GetSong(prevPos); //Sets the pointer of the current position of a song
    PlaylistNode* targetSong = GetSong(newPos); //Sets the pointer to the song that is going to be switched
    
    //Corrects the user input if newPos is less than 1 or greater than the quantity of songs in list
    if (newPos > NodeCount){
        targetSong = tail;
    } else if (newPos < 1){
        targetSong = head;
    }

    
    if (prevPos == 1) { //Head to Node
        if (NodeCount == 2){ /*Case 1 for moving the head node when there are 2 nodes*/
            targetSong->SetNext(currPosition);
            currPosition->SetNext(nullptr);
            head =targetSong;
            tail = currPosition;
        } else if (currPosition == head && targetSong == tail) { //Case 2 (head to tail)
            PlaylistNode* temp = currPosition->GetNext();

            targetSong->SetNext(currPosition);
            currPosition->SetNext(nullptr);
            head = temp;
            tail = currPosition;
        } else { /*Case 3 for moving the head node (when head isn't being moved to tail)*/
            PlaylistNode* beforeTarget = GetSong(newPos - 1);
            PlaylistNode* afterTarget = GetSong(newPos + 1);

            currPosition->SetNext(afterTarget);
            targetSong->SetNext(currPosition);

            head = beforeTarget;
        }
        
    } else if (prevPos == NodeCount) { //Tail to node
        if (NodeCount == 2){ /*Case 1 tail to head when there are 2 nodes */
            currPosition->SetNext(targetSong);
            targetSong->SetNext(nullptr);
            head = currPosition;
            tail = targetSong;
        } else if (targetSong == head && currPosition == tail) { //Case when moving head to tail (nodes>2)
            PlaylistNode* beforeCurrent = GetSong(prevPos - 1);

            beforeCurrent->SetNext(nullptr);
            currPosition->SetNext(targetSong);
            tail = beforeCurrent;
            head = currPosition;
        } else { //Case 3 when moving tail to other position in playlist that's not head
            PlaylistNode* beforeCurrent = GetSong(prevPos - 1);
            PlaylistNode* beforeTarget = GetSong(newPos - 1);

            beforeCurrent->SetNext(nullptr);
            beforeTarget->SetNext(currPosition);
            currPosition->SetNext(targetSong);

            tail = beforeCurrent;
        }
    } else if ((currPosition != tail && currPosition != head) && targetSong == head) { /*Moving song to the head*/
            PlaylistNode* beforeTarget = GetSong(prevPos - 1);

            beforeTarget->SetNext(currPosition->GetNext());
            currPosition->SetNext(targetSong);
            head = currPosition;
    } else if ((currPosition != tail && currPosition != head) && targetSong == tail) { /*Move song to the tail*/
            PlaylistNode* beforeCurrent = GetSong(prevPos - 1);

            targetSong->SetNext(currPosition);
            beforeCurrent->SetNext(currPosition->GetNext());
            currPosition->SetNext(nullptr);
            tail = currPosition; 
    } else if ((prevPos != 1 &&  newPos > prevPos) && targetSong != tail){ /*Moving song up the list*/
            PlaylistNode* beforeCurrent = GetSong(prevPos - 1);

            beforeCurrent->SetNext(currPosition->GetNext());
            currPosition->SetNext(targetSong->GetNext());
            targetSong->SetNext(currPosition);
    } else if ((newPos != 1 && prevPos > newPos) && currPosition != tail){ /*Moving song down the list*/
            PlaylistNode* temp = head;
            PlaylistNode* beforeCurrent = GetSong(prevPos - 1);

            beforeCurrent->SetNext(currPosition->GetNext());
            currPosition->SetNext(targetSong);
            temp->SetNext(currPosition);
    }

    cout << "\"" << currPosition->GetSongName() << "\"" << " moved to position " << newPos << endl;
    cout << endl;

}


//This function removes a function based on the unique ID of the song
void Playlist::RemoveSong(){
    string id;
    string temp;
    
    PlaylistNode* currSong = head;
    PlaylistNode* next = currSong->GetNext();
    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    cin.ignore();
    getline(cin, id);

    if (currSong->GetID() == id) { //Case 1 when ID equals the head of the playlist
        temp = currSong->GetSongName();
        delete currSong;
        head = nullptr;
        tail = nullptr;

        cout << "\"" << temp << "\"" << " removed." << endl;
        cout << endl;
    } else if (tail->GetID() == id) { //Case 2 when ID equals the tail of the playlist
        PlaylistNode* currSong = head;
        while (currSong->GetNext() != tail){
            currSong = currSong->GetNext();
        }

        PlaylistNode* remove = currSong->GetNext();
        delete remove;
        tail = currSong;
        tail->SetNext(nullptr);

    } else { //Case 3 when ID is neither head nor tail
        while (next->GetID() != id){
            currSong = next;
            next = next->GetNext();
        }

        temp = next->GetSongName();
        currSong->SetNext(next->GetNext());
        delete next;

        cout << "\"" << temp << "\"" << " removed." << endl;
        cout << endl;
    }


}

//This function returns the specific artist by a given artist name
void Playlist::OutputSpecificArtist() {
    string artistName;
    int counter = 1;
    cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
    cout << "Enter artist's name:" << endl;
    cin.ignore();
    getline(cin, artistName);
    cout << endl;

    PlaylistNode* specificArtist = head;
    while (specificArtist) {
        if (specificArtist->GetArtistName() == artistName){
            cout << counter << "." << endl;
            specificArtist->PrintPlaylistNode();
        }
        specificArtist = specificArtist->GetNext();
        counter++;
    }
}

//This function prints the totalTime of the given playlist
void Playlist::TotalTime() const {
    cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
    cout << "Total time: ";
    int totalTime = 0;
    PlaylistNode* currSong = head;
    while (currSong) {
        totalTime += currSong->GetSongLength();
        currSong = currSong->GetNext();
    }
    cout << totalTime << " seconds" << endl;
    cout << endl;
}

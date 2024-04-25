// implement classes' member functions here...
#include "playlist.h"
#include <iostream>
#include <string>

using namespace std;

PlayList::PlayList(int playlistSize){
    playlist_size = playlistSize; 
    songs = new string[playlist_size]; //Dynamically allocate new array for our playlist
    cout << "success" << endl;
}

//Helper Function
bool PlayList::isSongPresent(string titleAndArtist){
    for (int i = 0; i < song_num; i++){
        if (songs[i].compare(titleAndArtist) == 0){ //If we find that string in the array, it's already present
            return true; 
        }
    }
    return false; //If we make it outside the loop, that means the song wasn't found
}

//Principle PlayList Methods/Operations
void PlayList::AddSong(string titleAndArtist){
    //Checks if the song is already in the playlist or if it is a disallowed song (per project requirements)
    if (PlayList::isSongPresent(titleAndArtist) || titleAndArtist.compare("Baby;Justin Bieber") == 0 || titleAndArtist.substr(0, 19).compare("My Heart Will Go On") == 0){
        cout << "can not insert " << titleAndArtist << endl; 
    } else {
        if (song_num == (playlist_size)) { //Can't insert if we reach the maximum songs for our playlist
            cout << "can not insert " << titleAndArtist << endl;  
        } else {
            /*Otherwise, set the song to be at the nearest available song 
            location, and update the playlist count*/
            songs[song_num] = titleAndArtist; 
            song_num++;
            cout << "success" << endl;  
        }
    }
}

void PlayList::PlaySong(int songPosition){
    if (songPosition < 0 || songPosition >= song_num){ //If playlist index is invalid, can't play song
        cout << "can not play " << songPosition << endl; 
    } else { 
        if (songs[songPosition].empty()) { //If there is no song available at the given index, we can't play anything
            cout << "can not play " << songPosition << endl;  
        } else {
            cout << "played: " << songPosition << " " << songs[songPosition] << endl; //Otherwise, play the song
        }
    }
}

void PlayList::EraseSong(int songPosition){
    if (songPosition < 0 || songPosition >= playlist_size){ //If playlist index is invalid, can't play song 
        cout << "can not erase " << songPosition << endl;
    } else {
        if (songs[songPosition].empty()){ //If there is no song at the index, we can't erase anything
            cout << "can not erase " << songPosition << endl;
        } else {
            int j = 0; 
            /*Update the playlist by moving all songs after
            the given index up 1 index, closer to the start of the queue*/
            for (int i = 0; i < playlist_size; i++){  
                if (i != songPosition){
                    songs[j] = songs[i];
                    j++;
                }
            }
            cout << "success" << endl; 
            song_num--; //We now have less songs occupying playlist spots, so decrement the count
        }
    }
}

PlayList::~PlayList(){
    delete [] songs; //De-allocate dynamic array to avoid any memory leaks
}
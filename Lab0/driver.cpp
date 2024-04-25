#include <iostream>
#include <string>
#include "playlist.h"

using namespace std;

int main() {
    string operation;
    /*We parse the first line containing the 'm' command to invoke constructor using parsed size value*/ 
    getline(cin, operation); 
    int size = stoi(operation.substr(2)); 
    PlayList p(size); //Initializing the playlist instance after parsing the 'm' command
    while (getline(cin, operation)){ //Now we read through the rest of the file
        if (operation.substr(0, 1) == "i"){ //We will call 'add' function if command is 'i'
            string titleAndArtist = operation.substr(2);
            p.AddSong(titleAndArtist); 
        } else if (operation.substr(0, 1) == "p"){ //We will call 'play' function if command is 'p'
            int songPosition = stoi(operation.substr(2)); 
            p.PlaySong(songPosition); 
        } else if (operation.substr(0, 1) == "e"){ //We will call 'erase' function if command is 'e'
            int songPosition = stoi(operation.substr(2)); 
            p.EraseSong(songPosition); 
        }
    }
    return 0;
}

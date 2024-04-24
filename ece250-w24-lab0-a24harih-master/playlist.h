// define your classes here...
#include <string>

using namespace std; 

class PlayList {
    public: 
        PlayList(int playlistSize); //Initialize the playlist of songs
        void AddSong(string titleAndArtist); //Add specific song given artist and title
        void PlaySong(int songPosition); //Play the specific song
        void EraseSong(int songPosition); //Erase a specific song
        bool isSongPresent(string titleAndArtist); //Check if the song is already in the playlist
        ~PlayList(); //Destory or Deallocate the playlist of songs
    private:
        int song_num = 0; //Tracks how much of the playlist has been taken up
        int playlist_size; //Track the size of the playlist 
        string* songs; //Pointer to dynamic array we'll use to store the songs
};
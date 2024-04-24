// define your classes here...
#include <cmath>

using namespace std; 

//GameList denotes the Linked List used to play the game
class GameList {
    private:
        /* PlayerNode is a Node in the Linked List containing player info
        (i.e. coordinates, distance, etc.) */ 
        class PlayerNode {
            public:
                PlayerNode(double xPos, double yPos){
                    x = xPos; 
                    y = yPos;
                    distance = ComputeDistance(xPos, yPos);
                    next = nullptr; 
                    prev = nullptr;  
                };
                double x; //x-coordinate of player
                double y; //y-coordinate of player
                double distance; //member variable to track distance from wolf (origin)
                //Helper function to compute current or updated distances with every change in coordinates
                double ComputeDistance(double xPos, double yPos){
                    return sqrt(pow(xPos, 2) + pow(yPos, 2)); 
                }; 
                PlayerNode* next; //Reference to the next player in the List
                PlayerNode* prev; //Reference to the previous player in the list 
        };
        PlayerNode* head; //Refers to first node in the list
        PlayerNode* tail; //Refers to last node in the list 
        int listSize; //Tracks the current number of players in the game

    public: 
        GameList();
        void SpawnPlayer(double xPos, double yPos); //Will add a new player with given coordinates to end of linked list
        void ModifyDistance(double t); //TIME function - modifies player coordinates based on formula and removes cheaters
        void Lunch(); //LUNCH function - eliminates players within distance of 1 from wolf
        void RemainingPlayers(); //Prints the number of players still left in the game
        void PrintRemaining(double d); //Prints the coordinates of all remaining players
        void Winner(); //Determines the result of the game - whether wolf wins or players win
        ~GameList();
};
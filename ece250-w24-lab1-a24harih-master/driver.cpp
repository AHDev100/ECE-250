// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include <sstream>
#include "game.h"

using namespace std; 

int main(){
    // your code goes here...  
    string operation; //String to store data in each line of input text
    GameList p; //Our linked list instance
    while(getline(cin, operation)){ //Allows us to check line by line until end of file
        stringstream read(operation); //Use string stream to extract values from the line
        string command; 
        read >> command; //The first string before a space will be the command and the value is stored in the variable
        if (command == "SPAWN") {
            double x, y;
            read >> x >> y; //Now we can read the string, and store the corresponding values into x and y based on the spacing
            p.SpawnPlayer(x, y); //If the command is SPAWN, we call the SpawnPlayer method
        } else if (command == "TIME") { 
            double t;
            read >> t; //Now we can read the time, and store the corresponding values into t
            p.ModifyDistance(t); //Now we can call our ModifyDistance/TIME method
        } else if (command == "LUNCH") {
            p.Lunch(); //We call the Lunch function since the command is LUNCH
        } else if (command == "PRT") { 
            double d;
            read >> d; //Now we can read the distance value and store it in the variable d
            p.PrintRemaining(d); //We call PrintRemaining to check players within a distance d from wolf
        } else if (command == "NUM"){
            p.RemainingPlayers(); //For NUM command call the method to check the remaining players in the game
        } else if (command == "OVER") {
            p.Winner(); //Method to determine the winner, as game is now OVER
        }
    }
    return 0;
}
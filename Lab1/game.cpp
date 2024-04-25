// implement classes' member functions here...
#include "game.h"
#include <cmath>
#include <iostream>

using namespace std; 

GameList::GameList(){
    //Initializing values for an empty list
    head = nullptr;
    tail = nullptr;
    listSize = 0;  
}

void GameList::SpawnPlayer(double xPos, double yPos){ //SPAWN function
    if (xPos <= 0 || yPos <= 0){ //If the player is not in quadrant 1, we can't add them to list
        cout << "failure" << endl; 
    } else { //Otherwise create a new node and add it to the list
        PlayerNode* newNode = new PlayerNode(xPos, yPos);
        if(listSize == 0){ //If the list was initially empty
            head = newNode; 
            tail = newNode; 
        } else { //Otherwise, simply modify just the tail for it to point to the newly created node
            newNode->prev = tail; 
            tail->next = newNode; 
            tail = newNode; 
        }
        listSize++; //Whenever we add to the list, the size of the list will grow by 1
        cout << "success" << endl;
    }
}

void GameList::ModifyDistance(double t){ //TIME function
    PlayerNode* curr = head; 
    PlayerNode* temp; 
    while (curr != nullptr){
        /* We apply the formulas as specified in order to modify the x and y 
        coordinates as required, and we'll then update the Node's x, y, and 
        distance values (the latter is updated using the helper function)*/
        double x_new = curr->x - t*cos(atan2(curr->y, curr->x)); 
        double y_new = curr->y - t*sin(atan2(curr->y, curr->x));
        curr->x = x_new; //Update x-coordinate
        curr->y = y_new; //Update y-coordinate
        curr->distance = curr->ComputeDistance(curr->x, curr->y); //Update distance
        if (curr->x <= 0 || curr->y <= 0){ //Remove the player if they are now cheating (not in Quadrant 1)
            if (curr == head){ //If the current player is the first in the list
                head = curr->next; //Set the second player in the list as the head now
                if (head != nullptr){ //If the head is not empty, then we can set its previous to null
                    head->prev = nullptr; 
                }
            } else if (curr == tail) { //If the current player is the last in the list
                tail = curr->prev; //We set the second-last player in the list to be the last-player now
                if (tail != nullptr){ //If the tail isn't empty, then we can make its next node null
                    tail->next = nullptr; 
                }
            } else { //Otherwise
                curr->prev->next = curr->next; //Set the next of the current node's previous node to be the next of the current node
                curr->next->prev = curr->prev; //Set the previous of the current node's next node to be the current node's previous node
            }
            temp = curr; //Store the node we want to delete in a temporary reference
            curr = curr->next; //Proceed to perform operation on the next node
            delete temp; //Delete the node stored in the temporary reference, as they are a cheater
            listSize--; //Since we are removing a node, the size of the list decreases by 1
        } else {
            /*If the player is still in Quadrant 1 after modifying the coordinates,
            proceed to the next node*/
            curr = curr->next; 
        }
    }
    cout << "num of players: " << listSize << endl; //Print out the number of players remaining after removal of possible cheaters
}

void GameList::Lunch(){ //LUNCH function
    PlayerNode* curr = head;  
    PlayerNode* temp;
    while (curr != nullptr){
        if(curr->distance < 1){ //If the distance between the current player node and the wolf is less than 1, then we'll remove the node from the linked list
            //The remove logic is the exact same as that used for the "ModifyDistance"/TIME function
            if (curr == head){
                head = curr->next;
                if (head != nullptr){
                    head->prev = nullptr; 
                }
            } else if (curr == tail) {
                tail = curr->prev;
                if (tail != nullptr){
                    tail->next = nullptr; 
                }
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }
            temp = curr; 
            curr = curr->next; 
            delete temp;
            listSize--;
        } else {
            curr = curr->next;
        }
    }
    cout << "num of players: " << listSize << endl; //Once the players too close to the wolf are removed, print out the number of remaining players
}

void GameList::RemainingPlayers(){ //NUM function
    cout << "num of players: " << listSize << endl; //Print the number of remaining players (size of the linked list)
}

void GameList::PrintRemaining(double d){ //PRT function
    PlayerNode* curr = head; 
    int numPlayers = 0; //Check the number of players within a distance d from the wolf
    while (curr != nullptr){
        if (curr->distance < d){ //If the distance from the current node to the wolf is less than d 
            cout << curr -> x << " " << curr->y << " "; //Print the x and y coordinates of the current node
            numPlayers++; //Increment the number of players satisfying the condition
        }
        curr = curr->next;
    }
    if (numPlayers == 0){ //No players within a distance d from the wolf
        cout << "no players found" << endl; 
    } else {
        cout << endl; 
    }
}

void GameList::Winner(){ //OVER function - to determine the winner
    //If there are no players remaining the wolf wins, otherwise the players win
    if (listSize == 0){
        cout << "wolf wins" << endl;
    } else {
        cout << "players win" << endl;
    }
}

GameList::~GameList(){
    PlayerNode* curr = head; 
    PlayerNode* temp; 
    /*We traverse the Linked List from the head node, 
    store each node in a temporary reference, delete the
    temporary node, and proceed to the next, eventually 
    de-allocating the entire Linked List*/
    while (curr != nullptr){
        temp = curr; 
        curr = curr->next;
        delete temp; 
    }
}
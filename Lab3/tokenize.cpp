// implement classes' member functions here...
#include "tokenize.h"
#include <iostream>
#include <fstream>

using namespace std; 

Dictionary::Dictionary(int size){
    this->size = size; 
    entries = 0; 
    load_factor = 0; 
    
    words_to_tok = new List*[size]; //Dynamically allocate an array of Linked Lists per the external chaining method
    
    for(unsigned int i = 0; i < size; i++){
        words_to_tok[i] = new List(); //Initializing each of the elements to be a new List for memory safety 
    } 
}

Dictionary::~Dictionary(){
    for(unsigned int i = 0; i < size; i++){
        delete words_to_tok[i]; //We destroy the Linked List at the given index (implicitly calling the ~List() destructor)
    }
    delete [] words_to_tok; //Once each of the Lists are deleted, delete the entire array
}

void Dictionary::insert(string &word){
    //If the "word" is already present in the table, or is not alphabetical, we can't insert it
    if(isPresent(word) || !isAlphabetic(word)){
        cout << "failure" << endl; 
        return; 
    } else {
        tok_to_words.push_back(word); //Add the word to the end of the vector
        entries++; //The number of entries increases by 1
        int index = hash(word); //Get the index for our array using the hash function on the word
        words_to_tok[index]->insert(word, entries); //We add a new Node containing the new word and its token to the end of the Linked List at the index
        
        load_factor = double(entries)/size; //We update the load factor as needed with each insertion
        if(load_factor >= 0.8){ //If it's >= 0.8, we need to rehash and resize the array
            solveCollision();
        }  
        
        cout << "success" << endl; 
        return; 
    }
}

bool Dictionary::insertWithoutPrint(string &word){ 
    //This is just the same as the "insert" function above, just no print statements - using it for the "load" command
    if(isPresent(word) || !isAlphabetic(word)){
        return false; 
    } else {
        tok_to_words.push_back(word);
        entries++;  
        int index = hash(word); 
        words_to_tok[index]->insert(word, entries); 
        
        load_factor = double(entries)/size; 
        if(load_factor >= 0.8){
            solveCollision();
        }  
        return true; 
    }
}

bool Dictionary::isPresent(string &word){
    int index = hash(word); //Retrieve the array index using the hash function on the passed word
    return (words_to_tok[index]->contains(word) != nullptr) ? true : false;  //If the word is already in the list, we return true. Otherwise, we return false
}

bool Dictionary::isAlphabetic(string &word){
    //We loop through each of the characters of the string, and if any one of them is not alphabetical, then we return false. Otherwise, return true
    for (char ch : word){
        if(!isalpha(ch)){
            return false; 
        }
    }

    return true; 
}

void Dictionary::solveCollision(){
    size*=2; //The size now doubles - our hash function is also modified as a result
    List** new_arr = new List*[size]; //We now allocate a larger array of Linked Lists that's double the size
    for(unsigned int i = 0; i < size; i++){
        new_arr[i] = new List(); //We set each of the elements of the new array to be a new List 
    }
    for(unsigned int i = 0; i < size/2; i++){
        //Now we go through each of the lists at each index of the old array
        List::Node* curr = words_to_tok[i]->getHead();
        /*We then loop within each of the lists, rehash each of the words in these lists 
        and insert them into the linked lists at their new indices in the larger array*/
        while (curr != nullptr){
            string word = curr->getWord();
            unsigned int token = curr->getToken();
            unsigned int index = hash(word); 
            new_arr[index]->insert(word, token);
            curr = curr->getNext();
        }
        delete words_to_tok[i]; //We delete the list once we're done looping through it
    }
    delete [] words_to_tok; //Once all the lists have been traversed through, delete the old array entirely  
    words_to_tok = new_arr; //Set the reference to the words to tokens mapping to be our larger array
    load_factor = double(entries)/size; //Update the load factor as needed
}

void Dictionary::load(string &filename){
    unsigned int num_insertions = 0; //Checking how many words were inserted
    ifstream file; 
    string word; 
    file.open(filename); 
    while(file){ //We read through each word in the file
        file >> word; 
        if(insertWithoutPrint(word)){ //If the current word was successfully inserted, we make note of that
            num_insertions++; 
        }
    }
    //If at least once was inserted, the operation was successful. Otherwise, it is a failure
    (num_insertions > 0) ? cout << "success" << endl : cout << "failure" << endl; 
}

void Dictionary::tok(string &word){
    unsigned int index = hash(word); //Get the index from the word's hash
    List::Node* node = words_to_tok[index]->contains(word); //Check if the word exists in the Linked List at that hash
    if(node != nullptr){ //If it does, print out the token of that node
        std::cout << node->getToken() << " ";
    } else {
        std::cout << "-1" << " "; //Otherwise the word wasn't found in that Linked List
    }
}


void Dictionary::ret(unsigned int token){
    if(token > 0 && token <= tok_to_words.size()){ //Check the vector if the token is within the range of the vector
        string word = tok_to_words[token-1]; //We get the word at token-1 instead of token because of our 1-indexed counting
        std::cout << word << " "; //Then print out the word
    } else {
        std::cout << "N/A" << " "; //If the token isn't present, just print N/A out
    }
}

void Dictionary::print(int k){
    if (k >= 0 && k < size){ //Check if k falls within the bounds of our words_to_tok array
        List* curr_chain = words_to_tok[k];  //Get the current Linked List at position k
        if(curr_chain != nullptr){ 
            curr_chain->printList(); //If the list is not empty, print out the words stored in all its nodes 
        }
    }
}
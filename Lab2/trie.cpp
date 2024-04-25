// implement classes' member functions here...
#include "trie.h"
#include <string>
#include <iostream>

using namespace std; 

Trie::Trie(){
    //Initially the Trie has no words and just a singular root node
    root = new TrieNode(); 
    numWords = 0; 
}

Trie::~Trie(){ 
    /*We call our helper function, and simply start deleting all 
    the nodes from the root, deallocating memory as needed*/
    depthFirstClear(root);
}

void Trie::erase(string& word){
    /*If the trie has no words or if the word is not 
    in the trie, then there's nothing for us to erase*/
    if (!inTrie(word) || numWords == 0){
        cout << "failure" << endl;
        return;   
    } else {
        /*Otherwise start at the root, and call the corresponding
        recursive helper function to traverse from the root until
        the end of the word we are trying to remove and then recursively
        remove*/
        TrieNode* curr = root; 
        depthFirstErase(curr, word, 0); 
        //We now have one less word in the trie once we've erased
        numWords--; 
        cout << "success" << endl; 
    }
}

void Trie::clear(){  
    /*We can clear all the nodes of the trie, including the root node
    and once we're done, reinstantiate the root to leave us at our 
    Trie's initial state as specified by the constructor*/
    depthFirstClear(root);
    root = new TrieNode();
    numWords = 0; //No words left after clearing the Trie
    cout << "success" << endl; 
}

void Trie::count(string& prefix){
    TrieNode* curr = root; 
    bool noWords = false; //Boolean to check if it's possible for there to be any words containing the prefix argument

    for(unsigned int i = 0; i < prefix.length(); ++i){
        //If the prefix isn't on the tree entirely as needed it's not possible for there to be any words containing it 
        if(curr->getChildren()[int(prefix[i] - 65)] == nullptr){
            noWords = true; 
            break; 
        } else { //Traverse down the trie to the child
            curr = curr->getChildren()[int(prefix[i] - 65)];
        }
    }

    if (noWords){ //No words are found containing the prefix
        cout << "not found" << endl; 
    } else {
        /* We use a recursive helper function that implements a depth first search to
        determine how many words end from where we left off with the prefix*/
        int count = searchTrie(curr); 
        if (count == 0){ //If there are no such words
            cout << "not found" << endl;
        } else { //There are such words containing the prefix
            cout << "count is " << count << endl; 
        }
    }
}

void Trie::empty(){
    if (numWords <= 0){ //If there's no words in the Trie
        cout << "empty 1" << endl; 
    } else { 
        cout << "empty 0" << endl;     
    }
}

void Trie::insert(string& word){
    TrieNode* curr = root; 
    //Start from the root node and iterate through all the characters of the word
    for(unsigned int i = 0; i < word.length(); ++i){
        /*Case in which the current character is not in the trie 
        (we insert a new character into the trie along the edges connecting 
        current and a new node called next)*/
        if (curr->getChildren()[int(word[i] - 65)] == nullptr){ 
            TrieNode* next = new TrieNode(); 
            next->setVal(word[i]);
            curr->setChild(next); 
            curr = next; 
        } else {
            //If it's already in the trie, just advance the current TrieNode to the child
            curr = curr->getChildren()[int(word[i] - 65)]; 
        }
    }
    //If the character we are at is already marked as the end of a word, then the word was already there to begin with
    if(curr->checkWordEnd() == true){
        cout << "failure" << endl; 
    } else { //Otherwise, we've just finished inserting a new word, so add that we've reached the end of a word and increase the number of words in the trie
        curr->updateWordEnd(true);
        numWords++;  
        cout << "success" << endl; 
    }
}

//Insert without print is the insert function used specifically to work with the corpus.txt file - we don't want additional print statements 
void Trie::insertWithoutPrint(string& word){
    TrieNode* curr = root; 
    for(unsigned int i = 0; i < word.length(); ++i){
        //Case in which the current character is not in the trie
        if (curr->getChildren()[int(word[i] - 65)] == nullptr){
            TrieNode* next = new TrieNode(); 
            next->setVal(word[i]);
            curr->setChild(next); 
            curr = next; 
        } else {
            //If it's already in the trie, just advance the current TrieNode to the child
            curr = curr->getChildren()[int(word[i] - 65)]; 
        }
    }
    //If the character we are at is already marked as the end of a word, then the word is already there
    if(curr->checkWordEnd() == true){
        return; 
    } else { //Otherwise, you've inserted a new word, so add that we've reached the end of a word and increase the number of words in the trie
        curr->updateWordEnd(true);
        numWords++; 
    }
}

void Trie::print(){
    if (numWords != 0){
        /*We call our helper function that implements 
        a depth first search to print out the trie, starting from our root*/
        string initial = ""; 
        depthFirstPrint(root, initial); 
        cout << endl;
    } else { //If there are no words in the Trie, we don't print anything
        return; 
    }
}

void Trie::size(){
    //Just prints out how many words are in the trie
    cout << "number of words is " << numWords << endl; 
}

void Trie::spellcheck(string& word){
    //If there's no words in the Trie, there's nothing to compare with
    if (numWords == 0){
        cout << endl; 
        return; 
    }
    //If the word is already in the Trie, then it's spelled correctly 
    else if (inTrie(word)){
        cout << "correct" << endl; 
        return;
    } else {
        TrieNode* curr = root; 
        unsigned int i;
        /*Start from the root node, and traverse through each of the characters of the word
        and through the trie*/
        for (i = 0; i < word.length(); ++i){
            //If the current word character is not in the trie, we break out of the loop
            if (curr->getChildren()[int(word[i] - 65)] == nullptr){
                break;
            } else { 
                //Otherwise, advance the current node to it's child corresponding to the current character
                curr = curr->getChildren()[int(word[i] - 65)]; 
            }
        }

        if (i == 0){ //If even the first character of the word is not in the trie, then there's nothing to compare in terms of prefixes
            cout << endl;
        } else {
            /*Otherwise, call recursive helper function to print out all the words
            starting off from where we ended in the traversal (curr). The word passed
            in is the substring from 0 to where we broke off in the loop (i), since this 
            is the maximum prefix which we are starting to print from.*/
            string prefix = word.substr(0, i);
            depthFirstPrint(curr, prefix);
            cout << endl; 
            return;
        }
    }
}

/*Recursive helper function implementing depth-first search to determine the number 
of words starting with our given prefix (essentially counting the number of end of words)*/
int Trie::searchTrie(TrieNode* start){
    int count = 0;
    
    if(start == nullptr){ //If the node we passed in is empty, then there are no words
        return 0;
    }

    if(start->checkWordEnd()){ //If we reach the end of the word, add one to the count
        count++;
    } 

    for(unsigned int i = 0; i < 26; ++i){ //Iterate through all the children of the given node
        if(start->getChildren()[i] != nullptr){
            /*We add the number of words we get from the subtrees of the respective children
            and add that to our overall count*/
            count += searchTrie(start->getChildren()[i]);
        }
    }

    return count;
}

//This is a helper function we used to determine if a given word is in the trie
bool Trie::inTrie(string& word){
    TrieNode* curr = root; 
    for(unsigned int i = 0; i < word.length(); ++i){
        //If the current character is not in the Trie, then it's impossible for the word itself to be in the Trie
        if(curr->getChildren()[int(word[i] - 65)] == nullptr){ 
            return false; 
        } else { //Otherwise advance to the child corresponding to the current character in the word
            curr = curr->getChildren()[int(word[i] - 65)]; 
        }
    }
    //If we've reach the end of a word in the Trie, return true, otherwise return false
    return curr->checkWordEnd(); 
}

//Helper function implementing depth-search to print out the words in the Trie
void Trie::depthFirstPrint(TrieNode* start, string& word){
    //If we've passed an empty node, then there's nothing to print and we simply return
    if (start == nullptr){
        return; 
    }

    //If we reach the end of a word (the word we build up in our loop), we print that word out 
    if (start->checkWordEnd()){
        cout << word << " "; 
    }

    //Check each of the children of the node we're starting from
    for (unsigned int i = 0; i < 26; ++i){
        if (start->getChildren()[i] != nullptr){
            /*If we have a child here, recursively call the print function at the child, appending 
            the current character to our pre-existing word*/
            string appended = word + char(65 + i); 
            depthFirstPrint(start->getChildren()[i], appended);
        }
    }
}

//Helper function implementing depth-search to clear out the words in the Trie
void Trie::depthFirstClear(TrieNode* start){
    //If the pointer we passed is null, there's nothing to delete
    if (start == nullptr) {
        return;
    }

    //Iterate through all the children 
    for(unsigned int i = 0; i < 26; ++i){
        //Recursively call the function to go through the children (as per depth-first approach)
        depthFirstClear(start->getChildren()[i]);
        //Once you're done deleting the child subtree recursively, set the child to null
        start->getChildren()[i] = nullptr;
    }
    
    //Once we reach a leaf node, we start deleting
    delete start;
}

//Helper function implementing depth-search to clear a given word from the Trie
void Trie::depthFirstErase(TrieNode* start, string& word, unsigned int depth){
    //If the Node is at the last level of the Trie, we have to update it so that it's no longer the end of a word
    if(depth == word.length()){
        start->updateWordEnd(false); 
        return; 
    }

    //Otherwise, we advance the Node to its corresponding child node
    TrieNode* child = start->getChildren()[int(word[depth] - 65)]; 

    if (child == nullptr){ //If the child is empty, then there's nothing to erase
        return;
    }

    //Recursively call the function again on the word, now one level lower at the child
    depthFirstErase(child, word, depth + 1); 

    //If the child isn't a leaf node or the end of a word, we can set it to a nullptr and delete
    if(!child->checkWordEnd() && !child->hasChildren()){
        start->getChildren()[int(word[depth] - 65)] = nullptr; 
        delete child; 
    }
}
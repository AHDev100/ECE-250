// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "trie.h"
#include <sstream>
#include <fstream>

using namespace std; 

int main(){
    Trie t; 
    string operation; 
    while (getline(cin, operation)){
        stringstream read(operation); 
        read >> operation;
        if (operation == "load"){
            ifstream file;
            string word;
            file.open("corpus.txt");
            while (file){
                file >> word;
                t.insertWithoutPrint(word);
            }
            std::cout << "success" << std::endl;
        }
        else if (operation == "i"){
            string insert; 
            read >> insert; 
            t.insert(insert);
        } else if (operation == "c") {
            string prefix; 
            read >> prefix; 
            t.count(prefix);
        } else if (operation == "e") {
            string erase; 
            read >> erase; 
            t.erase(erase); 
        } else if (operation == "p") {
            t.print(); 
        } else if (operation == "spellcheck") {
            string check; 
            read >> check; 
            t.spellcheck(check); 
        } else if (operation == "empty") {
            t.empty(); 
        } else if (operation == "clear") {
            t.clear(); 
        } else if (operation == "size") {
            t.size(); 
        }
    } 
    return 0; 
}
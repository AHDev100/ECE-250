// include libraries here (STL not allowed)
#include <iostream>
#include <string>
#include "tokenize.h"
#include <sstream>


int main(){
    // your code goes here... 
    string operation;
    getline(cin, operation); 
    unsigned int size = stoi(operation.substr(7));
    Dictionary* d = new Dictionary(size);
    std::cout << "success" << std::endl;
    while(getline(cin, operation)){
        stringstream read(operation); 
        read >> operation; 
        if(operation == "insert"){
            string word; 
            read >> word; 
            d->insert(word); 
        } else if (operation == "load") {
            string filename; 
            read >> filename; 
            d->load(filename);
        } else if (operation == "tok") {
            string word; 
            read >> word; 
            d->tok(word);
            std::cout << std::endl; 
        } else if (operation == "ret") {
            unsigned int token; 
            read >> token; 
            d->ret(token);
            std::cout << std::endl; 
        } else if (operation == "tok_all") {
            string word; 
            while(read >> word){
                d->tok(word);  
            }
            std::cout << std::endl; 
        } else if (operation == "ret_all") {
            string token; 
            while(read >> token){
                d->ret(stoi(token));  
            }
            std::cout << std::endl; 
        } else if (operation == "print") {
            string k; 
            read >> k; 
            d->print(stoi(k));     
        } else {
            break;
        }
    } 
    delete d;
    return 0; 
}
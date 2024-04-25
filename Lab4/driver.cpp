// include libraries here
#include <iostream>
#include <string>
#include "graph.h"
#include <sstream>

using namespace std; 

int main(){
    // your code goes here...
    Graph g; 
    string operation;
    while(getline(cin, operation)){
        stringstream read(operation); 
        read >> operation; 
        if (operation == "insert"){
            int a, b; 
            double d, s; 
            read >> a >> b >> d >> s; 
            bool success = g.insert(a, b, d, s);
            cout << (success ? "success" : "failure") << endl;  
        } else if (operation == "load") {
            string filename;
            read >> filename; 
            g.load(filename); 
        } else if (operation == "update") {
            string filename; 
            read >> filename; 
            g.update(filename); 
        } else if (operation == "traffic") {
            int a, b; 
            double A; 
            read >> a >> b >> A; 
            cout << (g.traffic(a, b, A) ? "success" : "failure") << endl; 
        } else if (operation == "print") {
            int a; 
            read >> a; 
            g.print(a); 
        } else if (operation == "delete") {
            int a; 
            read >> a; 
            g.remove(a); 
        } else if (operation == "path") {
            int a, b; 
            read >> a >> b; 
            g.path(a, b); 
        } else if (operation == "lowest") {
            int a, b; 
            read >> a >> b; 
            g.lowest(a, b); 
        } else {
            break; 
        }
    }   
    return 0; 
}
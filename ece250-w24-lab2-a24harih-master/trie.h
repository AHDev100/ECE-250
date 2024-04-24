#include <string>

using namespace std; 

class Trie {
private:
    class TrieNode {
        private:
            TrieNode* children[26]; //Array of 26 children (each index represents letters from A-Z)
            char value; //The value passed along the edges of the nodes
            bool end; //Marks if a node represents the end of a given word

        public:
            // TrieNode Constructor
            TrieNode(){
                //Initialize all the children references to be nullptr
                for(int i = 0; i < 26; i++){
                    children[i] = nullptr; 
                }
                value = '\0'; 
                end = false;
            }; 

            // Getter functions to retrieve the TrieNode member fields
            char getVal(){
                return value; 
            };
            bool checkWordEnd(){
                return end; 
            };
            TrieNode** getChildren(){
                return children; 
            };

            // Setter functions to update the TrieNode member fields
            void setVal(char newVal){
                value = newVal; 
            };
            void updateWordEnd(bool isEnd){
                end = isEnd; 
            };
            void setChild(TrieNode* c){
                children[int(c->getVal() - 65)] = c; 
            };

            //Additional Helper Functions
            bool hasChildren(){
                /*We check all the children of the node, if any one of 
                them is not null, then the node has children, otherwise it doesn't*/
                for(int i = 0; i < 26; i++){
                    if(this->getChildren()[i] != nullptr){
                        return true;
                    }
                }
                return false;
            }
    };

    TrieNode* root;
    int numWords;
    
    int searchTrie(TrieNode* start); //Recursive helper function used to count words beginning with given prefix
    bool inTrie(string& word); //Checks if a given word is already present in the Trie
    void depthFirstPrint(TrieNode* start, string& word); //Recursive helper function to print out all of the words in the Trie
    void depthFirstErase(TrieNode* start, string& word, unsigned int depth); //Recursive helper function to remove a give word form the trie
    void depthFirstClear(TrieNode* start); //Recursive helper function to clear out all the words from the Trie

public:
    // Trie constructor and destructor
    Trie();
    ~Trie();

    // Main lab functions
    void insert(string& word);
    void insertWithoutPrint(string& word); //Insert function without the print statements - used for 'load' command
    void count(string& prefix);
    void erase(string& word); 
    void print();
    void spellcheck(string& word);
    void empty();
    void clear();
    void size(); 
};

#include <vector>
#include <string>
#include <iostream>

using namespace std; 

// define your classes here...
class Dictionary {
    private: 
        class List{ //Linked List class for external chaining (collision resolution using Linked Lists)
            public: 
                class Node{ //Class definition for Linked List nodes
                    private: 
                        Node* next;
                        //Each Node will contain a word and its corresponding token (key-value pair)
                        string word; 
                        unsigned int token;
                    public:  
                        Node(string word, unsigned int token){
                            this->word = word; 
                            this->token = token; 
                            next = nullptr;
                        }
                        Node* getNext(){ //Getter for the next Node
                            return next; 
                        }
                        void setNext(Node* add){ //Helper later used for appending Nodes to end of a Linked List
                            this->next = add; 
                        }
                        string getWord(){ //Getter for the Node's word
                            return word; 
                        }
                        unsigned int getToken(){ //Getter for the Node's token
                            return token;
                        }
                };
                List(){
                    //Our list is initially empty - set the head and tail pointers to nullptr
                    head = nullptr; 
                    tail = nullptr;  
                }
                ~List(){
                    Node* curr = head; 
                    //Loop through the list iteratively and delete each node as we go, using temporary references
                    while(curr != nullptr){
                        Node* temp = curr; 
                        curr = curr->getNext(); 
                        delete temp; 
                    }
                }
                void insert(string &word, unsigned int token){
                    Node* add = new Node(word, token); //Create a new Node using the word and token passed in
                    if(head == nullptr){ //If the list is initially empty, set the new Node to be the head and the tail
                        head = add; 
                        tail = add; 
                    } else { //Otherwise, add to the back of the Linked List and modify the tail reference as needed
                        tail->setNext(add); 
                        tail = tail->getNext(); 
                    }
                }
                Node* getHead(){ //Return the head of the given Linked List
                    return head; 
                }
                Node* contains(string &word){
                    if (head == nullptr){ //If the list is empty, the word can't be found
                        return nullptr;
                    }
                    if(head->getWord() == word){ //If the word is at the head, just return the head Node
                        return head; 
                    }
                    if (tail->getWord() == word){ //If the word is at the tail node, just return the tail Node
                        return tail; 
                    }
                    Node* curr = head; 
                    //Otherwise loop through the list to see if any of the nodes have the given word
                    //If none of them have it, then we'll just return a nullptr
                    while (curr != nullptr){
                        if (curr->getWord() == word){
                            return curr; 
                        }
                        curr = curr->getNext(); 
                    }
                    return nullptr; 
                }
                void printList(){
                    if (head == nullptr){ //If the list is empty, don't print anything
                        return; 
                    }
                    //Otherwise, iteratively traverse through the list and print out the words at all the nodes sequentially
                    Node* curr = head; 
                    while(curr != nullptr){
                        cout << curr->getWord() << " ";
                        curr = curr->getNext();  
                    } 
                    cout << endl; 
                }
            private:
                Node* head;  
                Node* tail;
        };
        
        unsigned int hash(const string &str) { //The hash function as provided in the lab document
            unsigned int ans = 0;
            for (auto it = str.begin(); it != str.end(); ++it)
            ans = ans * 29 + *it;
            return ans % size;
        }
        
        void solveCollision(); //Helper function to resize and rehash the array when load_factor >= 0.8
        bool isPresent(string &word); //Helper to check if a word is already present in the table
        bool isAlphabetic(string &word); //Helper to check if the word is entirely alphabetical

        vector<string> tok_to_words; //Vector used to store the token to words mapping
        List** words_to_tok; //Dynamic Array used to store the words to tokens mapping
        
        unsigned int entries; //To keep track oF the number of unique words (key-value pairs - latest index in vector)
        unsigned int size; //Keeps track of the current size of hash table (update when resizing) 
        double load_factor; //Keep track of the load factor with each insertion to determine when to rehash and resize the table
    public: 
        Dictionary(int size); 
        ~Dictionary();
        //The functions as specified per the lab document
        void insert(string &word); 
        bool insertWithoutPrint(string &word); 
        void load(string &filename); 
        void tok(string &word); 
        void ret(unsigned int token);
        void print(int k);  
};
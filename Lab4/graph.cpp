// graph.cpp
#include "graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <set>
#include <vector>
#include <iomanip>

using namespace std;

bool Graph::insert(int a, int b, double d, double s) {
    Edge edge(a, b, d, s); //Make a new edge to add as needed
    if (adjacencies[a].count(b) && adjacencies[b].count(a)){ //If the edge between a and b exists both ways
        /*Since the edge already exists, we'll simply just update the d and s 
        fields of the existing edge as needed both ways*/
        adjacencies[a][b].d = d; 
        adjacencies[a][b].s = s;
        adjacencies[b][a].d = d; 
        adjacencies[b][a].s = s;
    } else {
        //Otherwise we add the edge between and b both ways in our adjacency list
        adjacencies[a][b] = edge;
        adjacencies[b][a] = edge;
    }
    return true; 
}

void Graph::load(string filename) {
    ifstream file(filename);
    int a, b;
    double d, s;
    string line;
    while (getline(file, line)) { //Go through the given file line by line
        istringstream iss(line);
        iss >> a >> b >> d >> s; //We parse each line to extract a, b, d, and s values
        insert(a, b, d, s); //Then call the insert function on the extracted values
    }
    cout << "success" << endl;
}

bool Graph::traffic(int a, int b, double A) {
    if (adjacencies.count(a) && adjacencies[a].count(b)) { //If the edge between a and b exists (we can assume if it exists 1 way, it'll exist the other way)
        //Otherwise, we update the edge both ways with the new value of A
        adjacencies[a][b].A = A;
        adjacencies[b][a].A = A; 
        return true;
    }
    return false;
}

void Graph::update(string filename) {
    ifstream file(filename);
    int a, b;
    double A;
    string line;
    bool success = false; //Checking if at least edge in the graph was successfully updated
    while (getline(file, line)) { //Read through each line of the file
        istringstream iss(line);
        iss >> a >> b >> A; //Extract the values of a, b, and A from the line 
        if (traffic(a, b, A)) { //If the traffic operation with the values is successful, at least one edge was updated successfully
            success = true;
        }
    }
    cout << (success ? "success" : "failure") << endl;
}

void Graph::print(int a) {
    if (!adjacencies.count(a)) { //If a isn't in the graph
        cout << "failure" << endl;
        return;
    }
    for (auto edge = adjacencies[a].begin(); edge != adjacencies[a].end(); edge++) {
        cout << edge->first << " "; //Otherwise, we traverse through the adjacencies of a, and print out all their values
    }
    cout << endl;
}

void Graph::remove(int a) {
    if (adjacencies.count(a)) { //If a is in our adjacency list 
        for (auto pair = adjacencies[a].begin(); pair != adjacencies[a].end(); pair++) {
            adjacencies[pair->first].erase(a); //We're going to loop through all the other node maps in our adjacency list, and remove a from all of them
        }
        adjacencies.erase(a); //Finally, erase entry a from the outer map of the adjacency list
        cout << "success" << endl;
    } else {
        cout << "failure" << endl;
    }
}

void Graph::path(int a, int b) {
    if (!adjacencies.count(a) || !adjacencies.count(b)) { //If neither a nor b are in the adjacency list, then there is no path
        cout << "failure" << endl;
        return;
    }

    //Priority queue implementing a min-heap for Dijkstra's algorithm
    priority_queue<pair<double, vector<int>>, vector<pair<double, vector<int>>>, greater<pair<double, vector<int>>>> pq; 

    set<int> visited; //A set used to keep track of all nodes we've already visited

    pq.push({0, vector<int>{a}}); //Pushing the source node a onto the priority queue with a weight of 0

    while (!pq.empty()) { 
        double currWeight = pq.top().first; //The total weight of the path being considered
        vector<int> currPath = pq.top().second; //The list of nodes comprising of the current path
        pq.pop();

        int currNode = currPath.back(); //Consider the current node in the path being considered

        if (currNode == b) { 
            //If the current node is the destination (b), we just print out all the nodes in the current path and our job is done
            for (int node : currPath) {
                cout << node << " ";
            }
            cout << endl;
            return;
        }

        if (visited.find(currNode) == visited.end()) { //Otherwise, if the current node has not already been visited
            visited.insert(currNode); //Add the node to the visited set
            for (auto it = adjacencies[currNode].begin(); it != adjacencies[currNode].end(); it++) {
                //Iterate through all the nodes adjacent to the current node
                int nextNode = it->first; //The iterator node
                Edge edge = it->second;
                if (edge.A == 0) continue; //If the edge between the current node and the iterator node has A = 0 => T = inf, the path is blocked, so move to the next adjacent node to the current node

                double weight = edge.d / (edge.s * edge.A); //Calculate the weight (T) between the current node and the iterator node

                if (visited.find(nextNode) == visited.end()) { //If the iterator node hasn't already been visited 
                    vector<int> newPath{currPath}; 
                    newPath.push_back(nextNode); //Add the iterator node to the end of the current path, thus forming a new path
                    pq.push({currWeight + weight, newPath}); //Push the updated path, and the total weight of this new path onto the priority queue
                }
            }
        }
    }

    cout << "failure" << endl;  //If no path from the start to the end node was found, then the operation failed
}

void Graph::lowest(int a, int b) {
    if (!adjacencies.count(a) || !adjacencies.count(b)) { //If neither the nodes a nor b are in the graph, then there's no lowest path
        cout << "failure" << endl;
        return;
    }

    unordered_map<int, double> distances; //A map to keep track of all the shortest distances from the source node a
    //Given a is the source, initialize the distance from a to a as 0, and the distance from a to all other nodes as inf (from convention)
    for (auto adj = adjacencies.begin(); adj != adjacencies.end(); adj++) {
        distances[adj->first] = numeric_limits<double>::infinity();
    }
    distances[a] = 0;

    //Implement a min-heap using a priority queue for Dijkstra's algorithm
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, a}); //Initially, add the source node a and a weight of 0 into the priority queue

    while (!pq.empty()) {
        int u = pq.top().second; //Extract the current node
        pq.pop();

        if (u == b) break; //If the current node is the destination, we don't need to proceed any further

        for (auto edge = adjacencies[u].begin(); edge != adjacencies[u].end(); edge++) {
            //We check all of the adjacencies of the current node
            int v = edge->first; //Keep track of the current vertex
            Edge e = edge->second; //Keep track of the current edge
            double weight = e.d / (e.s * e.A); //Calculate the weight of the given edge using its d, s, and A values

            if (distances[u] + weight < distances[v]) {
                /*If the current weight/distance is less than the pre-existing one to the vertex, 
                update the distance, then add the new vertex and the updated distance to the priority queue*/
                distances[v] = distances[u] + weight;
                pq.push({distances[v], v});
            }
        }
    }

    if (distances[b] == numeric_limits<double>::infinity()) { //If the path to the destination is blocked, then operation has failed
        cout << "failure" << endl;
        return;
    }

    cout << fixed << setprecision(3) << distances[b] << endl; //Print the shortest distance from a to b
}
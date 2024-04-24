#include <string>
#include <unordered_map>

using namespace std;

struct Edge {
    int a, b;
    double d, s;
    double A = 1; // Adjustment factor

    Edge() : a(0), b(0), d(0), s(0) {}
    Edge(int a, int b, double d, double s) : a(a), b(b), d(d), s(s) {}
};

class Graph {
private:
    unordered_map<int, unordered_map<int, Edge>> adjacencies;

public:
    bool insert(int a, int b, double d, double s);
    void load(string filename);
    bool traffic(int a, int b, double A);
    void update(string filename);
    void print(int a);
    void remove(int a);
    void path(int a, int b);
    void lowest(int a, int b);
};
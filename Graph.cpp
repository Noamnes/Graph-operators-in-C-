// id:212631071, mail:noamsayada1@gmail.com

#include "Graph.hpp"
#include <vector>
#include <stdexcept>
#include <iostream>
using std::vector;

ariel::Graph::Graph(const std::vector<std::vector<int>>& adjMat){
    ariel::Graph::loadGraph(adjMat);
}

void ariel::Graph::loadGraph(const std::vector<std::vector<int>>& adjMat){
    // checking valid shape of adjMat:
    for(int i = 0; i < adjMat.size(); i++){
        if(adjMat.size() != adjMat[i].size()){
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
    }
    // checking that there are no loops (edge from vertex to itself):
    for(int i = 0; i < adjMat.size(); i++){
        if(adjMat[i][i] != 0){
            throw std::invalid_argument("Invalid graph: The graph contains a loop.(edge from vertex to itself)");
        }
    }
    // initializing the isDirected to false:
    this->isDirected = false;
    // deep coping the adjMat:
    this->adjMat = adjMat;
    this->edges = 0;
    for(int i = 0; i < adjMat.size(); i++){
        for(int j = 0; j < adjMat[i].size(); j++){
            if(adjMat[i][j] != 0){
                this->edges++;
            }
            // if we found a non-symmetric edge, the graph is directed:
            if(adjMat[i][j] != adjMat[j][i]){
                this->isDirected = true;
            }
        }
    }
}

void ariel::Graph::printGraph()const{
    std::cout << (this->isDirected ? "Directed" : "undirected") << "Graph with " << this->adjMat.size() << " vertices and " << this->edges << " edges.";
}

ariel::Graph ariel::Graph::getReveresedGraph()const{
    // transposing the adjMat:
    vector<vector<int>> reversed(this->getSize(), vector<int>(this->getSize(), 0));
    for(int i = 0; i < this->getSize(); i++){
        for(int j = 0; j < this->getSize(); j++){
            reversed[i][j] = this->adjMat[j][i];
        }
    }
    // bulding the reversed graph and returning it:
    return ariel::Graph(reversed);
}

bool ariel::Graph::isContains(const Graph& g)const{
    // if g has more vex than *this - return false
    if(g.getSize() > this->getSize())
        return false;
    
    // go through all of g adjMat and ensure that every edge that 
    // exists in g is exists in *this.
    // meaning: if g.adjMat[i][j] != 0 then this->adjMat[i][j] != 0

    for(int i=0; i<g.getSize(); i++){
        for(int j=0; j<g.getSize(); j++){
            // if we found an edge that exists in g but not in
            // *this, *this doesn't contain g.
            if(g.adjMat[i][j] != 0 && this->adjMat[i][j] == 0)
                return false;
        }
    }
    
    return true;
}

//--------------------------------------------------------
// ? relation operators
//--------------------------------------------------------
bool ariel::Graph::operator>(const Graph& other)const{
    // i'll write before each condition what we know.

    // nothing at all!
    if(this->isStrictlyContains(other))
        return true;
    // *this isn't strictly contains other.
    if(other.isStrictlyContains(*this) || (other == *this))
        return false;
    // no graph contains the other(not even *unstrictly*)
    // and the graphs differ.
    if(other.edges < this->edges)
        return true;
    // no graph contains the other(not even *unstrictly*)
    // the graphs differ and e(*this) <= e(other)
    if(other.edges > this->edges)
        return false;
    // no graph contains the other(not even *unstrictly*)
    // the graphs differ, e(*this) == e(other) 
    if(other.getSize() < this->getSize())
        return true;
    
    // no graph contains the other(not even *unstrictly*)
    // the graphs differ, e(*this) == e(other) 
    // and v(*this) <= v(other).
    
    // those conditions entail that v(*this) > v(other)
    // hence *this < other !!
    return false;
}




//--------------------------------------------------------
// ? aritmetic operators
//--------------------------------------------------------

//--------------------------------------------------------
// ? addition operators
//--------------------------------------------------------
ariel::Graph ariel::Graph::operator+(const Graph& other) const{
    if(this->getSize() != other.getSize())
        throw std::invalid_argument("the graphs are not the same size!!");
    
    int commonSize = this->getSize();
    vector<vector<int>> newAdjMat(commonSize, vector<int>(commonSize, 0));
    for(int i=0; i<commonSize; i++){
        for(int j=0; j<commonSize; j++){
            newAdjMat[i][j] = this->adjMat[i][j] + other.adjMat[i][j];
        }
    }
    Graph newGraph(newAdjMat);
    return newGraph;
}

ariel::Graph& ariel::Graph::operator+=(const Graph& other){
    *this = *this + other; // using operator+
    return *this;
}

// my addition ;)
ariel::Graph& ariel::Graph::operator+=(const int num){
    // incrementing the all the edges there are (cell with 0 is not an edge)
    // and recalculate the number of edges (some have turned into 0!)
    int size = this->getSize();
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(this->adjMat[i][j] != 0){
                (this->adjMat[i][j]) += num;
                if(this->adjMat[i][j] == 0)
                    this->edges--;
            }
        }
    }
    return *this;
}

// prefix
ariel::Graph& ariel::Graph::operator++(){
    return *this+=1;
}

// postfix
ariel::Graph ariel::Graph::operator++(int){
    Graph temp = *this; // uses copy ctor to make a deep copy
    ++(*this);
    return temp;
} 

//--------------------------------------------------------
// ? subtraction operators:
//--------------------------------------------------------

ariel::Graph ariel::Graph::operator-() const{
    int vexNum = this->getSize();
    Graph newGraph(this->adjMat);
    for(int i=0; i<vexNum; i++){
        for(int j=0; j<vexNum; j++){
            newGraph.adjMat[i][j] = -1*(this->adjMat[i][j]);
        }
    }
    return newGraph;
}

ariel::Graph ariel::Graph::operator-(const Graph& other) const{
    return *this + (-other);
}

ariel::Graph& ariel::Graph::operator-=(const Graph& other){
    *this = *this - other;
    return *this;
}

// prefix
ariel::Graph& ariel::Graph::operator--(){
    return *this+=(-1);
}

ariel::Graph ariel::Graph::operator--(int){
    Graph temp = *this;
    --(*this);
    return temp;
}

// muliplication:
ariel::Graph ariel::Graph::operator*(const Graph& other) const{
    
    // name *this as left and other as right
    const Graph& left = *this;
    const Graph& right = other;
    
    if(left.getSize() != right.getSize())
        throw std::invalid_argument("the graphs are not the same size!!");
    
    // create a new adjMat and pass through all it's entries
    // in each entry - compute the value by the sum of the products
    int commonSize = right.getSize();
    vector<vector<int>> newAdgMat(commonSize, vector<int>(commonSize, 0));
    for(int i=0; i<commonSize; i++){
        for(int j=0; j<commonSize; j++){
            if(i == j)
                continue;
            int sum = 0;
            for(int k=0; k<commonSize; k++){
                sum += left.adjMat[i][k] * right.adjMat[k][j];
            } 
            newAdgMat[i][j] = sum;
        }
    }
    Graph newGraph(newAdgMat);
    return newGraph;
}
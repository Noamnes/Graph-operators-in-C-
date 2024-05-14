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
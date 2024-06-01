// id:212631071, mail:noamsayada1@gmail.com
#pragma once

#include <vector>

namespace ariel{
    class Graph{
        private:
            std::vector<std::vector<int>> adjMat;
            bool isDirected;
            int edges;
        public:
            // constructors:
                Graph():isDirected(false), edges(0) {};
                Graph(const std::vector<std::vector<int>>& adjMat); // IMPLEMENTED
                // copy ctor which uses the copy ctor of the vector class.
                Graph(const Graph& other):adjMat(other.adjMat), isDirected(other.isDirected), edges(other.edges){};
            // methods:
                void loadGraph(const std::vector<std::vector<int>>& adjMat); // IMPLEMENTED
                void printGraph()const; // IMPLEMENTED
                Graph getReveresedGraph()const; // IMPLEMENTED
                const std::vector<std::vector<int>>& getAdjMat()const{return this->adjMat;}
                int getSize()const{return this->adjMat.size();}
                bool IsDirected()const{return this->isDirected;}
                int getEdgesNum()const{return this->edges;}
                bool isContains(const Graph& g)const;
                bool isStrictlyContains(const Graph& g)const{return this->isContains(g) && (*this != g);}

            // operators:
                // aritmetic operators:
                    // addition operators:
                    Graph operator+(const Graph& other) const;
                    Graph& operator+=(const Graph& other);
                    Graph operator+()const{return *this;};
                    Graph& operator+=(const int num);// my addition ;)
                    // increment operators:
                    Graph& operator++(); // prefix
                    Graph operator++(int); // postfix 
                    
                    // subtraction operators:
                    Graph operator-() const;
                    Graph operator-(const Graph& other) const;
                    Graph& operator-=(const Graph& other);
                    Graph& operator--(); //prefix
                    Graph operator--(int); // postfix

                    // multiplication operator:
                    Graph operator*(const Graph& other) const; 

                    // levels of independence among operators:
                    // 1. g+g, +g, ++g, -g
                    // 2. g+=g, g++. g-g
                    // 3. g-=g
                // noam: check
                // relation operators:
                bool operator==(const Graph& other)const{
                    return (this->edges == other.edges) && (this->getSize() == other.getSize());
                }

                bool operator!=(const Graph& other)const{
                    return !(*this == other);
                }

                bool operator>(const Graph& other)const;

        };
}
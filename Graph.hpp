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
            Graph(){};
            Graph(const std::vector<std::vector<int>>& adjMat); // IMPLEMENTED
            void loadGraph(const std::vector<std::vector<int>>& adjMat); // IMPLEMENTED
            void printGraph()const; // IMPLEMENTED
            Graph getReveresedGraph()const; // IMPLEMENTED
            const std::vector<std::vector<int>>& getAdjMat()const{
                return this->adjMat;
            };
            int getSize()const{
                return this->adjMat.size();
            };
            bool IsDirected()const{
                return this->isDirected;
            };
        };
}
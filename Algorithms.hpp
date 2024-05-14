// id:212631071, mail:noamsayada1@gmail.com
#pragma once

#include "Graph.hpp"
#include <vector>
#include <string>
#include <stack>


namespace ariel{
    class Algorithms{
        private:
            static bool isRoot(const Graph& g, int vex); // IMPLEMENTED
            static std::vector<std::vector<int>> bellmanFord(const Graph& g, int src); // IMPLEMENTED
            static bool can2color(const Graph& g, int vex, int currColor, std::vector<int>& colors);
            static bool canConstructCycle(const Graph& g,int rootVex
                                            , std::vector<bool>& visited
                                            , std::vector<bool>& inCurrDNSTree
                                            , std::stack<int>& pathStack
                                            , bool isPositive); // IMPLEMENTED
            static bool canConstructCycleInDirectedGraph(const Graph& g,int rootVex
                                            , std::vector<bool>& visited
                                            , std::vector<bool>& inCurrDNSTree
                                            , std::stack<int>& pathStack
                                            , bool negativeOnly); // IMPLEMENTED
            static bool canConstructCycleInUnDirectedGraph(const Graph& g,int rootVex
                                            , std::vector<bool>& visited
                                            , std::stack<int>& pathStack
                                            , bool negativeOnly); // IMPLEMENTED
            static bool isNegativeCycle(const Graph& g, std::stack<int> pathStack, int connectingVex); // IMPLEMENTED
            static std::string isContainsSignedCycle(const Graph& g, bool negativeOnly); // IMPLEMENTED
        public:
            static bool isConnected(const Graph& g); // IMPLEMENTED
            static std::string shortestPath(const Graph& g, int src, int dest); // IMPLEMENTED
            static std::string isContainsCycle(const Graph& g); // IMPLEMENTED
            static std::string isBipartite(const Graph& g); // HAVE AID FUNCS
            static std::string getNegativeCycle(const Graph& g); // IMPLEMENTED
    };
}
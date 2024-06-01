// id:212631071, mail:noamsayada1@gmail.com
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;
TEST_SUITE("Test Graph.cpp"){
    TEST_CASE("Test invalid graph"){
        ariel::Graph g;
        vector<vector<int>> graph = {
            {0, 1, 2, 0},
            {1, 0, 3, 0},
            {2, 3, 0, 4},
            {0, 0, 4, 0},
            {0, 0, 0, 5}};
        // test loading graph which is not a squre metrix:
        CHECK_THROWS(g.loadGraph(graph));

        vector<vector<int>> graph2 = {{0, 1, 2, 0},
                                    {1, 0, 3, 0},
                                    {2, 3, 1, 4},
                                    {0, 0, 4, 0}};
        // test loading graph with loops (edge from vex to itself):
        CHECK_THROWS(g.loadGraph(graph2));
    }
}

TEST_SUITE("Test Algorithms.cpp"){
    TEST_CASE("Test isConnected"){
        ariel::Graph g({{0, 1, 0},
                        {1, 0, 1},
                        {0, 1, 0}});
        // simple undirected connected graph:
        CHECK(ariel::Algorithms::isConnected(g) == true);

        ariel::Graph g2({{0, 1, 1, 0, 0},
                        {1, 0, 1, 0, 0},
                        {1, 1, 0, 1, 0},
                        {0, 0, 1, 0, 0},
                        {0, 0, 0, 0, 0}});
        // simple undirected unconnected graph:
        CHECK(ariel::Algorithms::isConnected(g2) == false);

        ariel::Graph g3({{0, 1, 1, 0, 0}, 
                        {0, 0, 0, 1, 1}, 
                        {0, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 0}});
        // directed unconnected graph (where we start the search from a root):
        CHECK(ariel::Algorithms::isConnected(g3) == false);

        ariel::Graph g4({{0, 1, 0}, 
                        {0, 0, 1}, 
                        {0, 1, 0}});
        // directed unconnected with bidrectional edge (we start the search from the root):
        CHECK(ariel::Algorithms::isConnected(g4) == false);
        
        ariel::Graph g5({{0, 1, 1, 0, 0, 0}, 
                        {0, 0, 0, 1, 1, 0}, 
                        {0, 0, 0, 0, 0, 1}, 
                        {0, 0, 0, 0, 0, 1}, 
                        {0, 0, 1, 0, 0, 0}, 
                        {1, 0, 0, 0, 0, 0}});
        // directed connected graph without bidirectional edge:
        CHECK(ariel::Algorithms::isConnected(g5) == true);
    }
    
    TEST_CASE("Test shortestPath"){
        ariel::Graph g({{0, 1, 0},
                        {1, 0, 1},
                        {0, 1, 0}});
        // simple test, only one path:
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

        
        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        // test no path:
        CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
        // test multiple paths:
        CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->2->3");
        
        vector<vector<int>> graph3 = {{0, -3, 1, 1}, 
                                        {0, 0, 2, 0}, 
                                        {1, 2, 0, 1}, 
                                        {0, 0, 1, 0}};
        g.loadGraph(graph3);
        // test negative weights without negative cycles:
        CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

        vector<vector<int>> graph4 = {{0, -3, 1, 1}, 
                                        {0, 0, 1, 0}, 
                                        {1, 0, 0, 1}, 
                                        {0, 0, 1, 0}};
        g.loadGraph(graph4);
        // test with negative cycles: (when src is in the negative cycle)
        CHECK_THROWS(ariel::Algorithms::shortestPath(g, 0, 2));
        // test when src is not in the negative cycle, but can reach it:
        CHECK_THROWS(ariel::Algorithms::shortestPath(g, 3, 2));
        
        vector<vector<int>> graph5 = {{0, -1, 1, 1}, 
                                        {-1, 0, 3, 0}, 
                                        {1, 0, 0, 1}, 
                                        {0, 0, 1, 0}};
        g.loadGraph(graph5);
        
        // test when there is only a negative cycle with 2 vexes:
        CHECK_THROWS(ariel::Algorithms::shortestPath(g, 3, 2));
    }

    TEST_CASE("Test isContainsCycle"){
        ariel::Graph g;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g.loadGraph(graph);
        // test unDirected with edges but no cycle with 3 vexes or more:
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

        vector<vector<int>> graph2 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 0, 0},
            {1, 1, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        // test unDirected with cycle with 3 vexes:
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->2->0");

        vector<vector<int>> graph3 = {{0, 1, 1}, 
                                        {1, 0, 0}, 
                                        {0, 0, 0}};
        g.loadGraph(graph3);
        // test directed with bidirectional edge:
        CHECK(ariel::Algorithms::isContainsCycle(g) == "0->1->0");
        
        vector<vector<int>> graph4 = {{0, 1, 1, 0, 0, 0, 0}, 
                                      {0, 0, 0, 0, 0, 0, 0}, 
                                      {0, 0, 0, 1, 1, 0, 0}, 
                                      {0, 0, 0, 0, 0, 1, 0}, 
                                      {0, 0, 0, 0, 0, 0, 0}, 
                                      {0, 0, 0, 0, 1, 0, 1}, 
                                      {0, 0, 0, 1, 0, 0, 0}};
        g.loadGraph(graph4);
        // test directed with cycle with 3 vexes that 
        // doesn't start at the root of the dfs tree:
        CHECK(ariel::Algorithms::isContainsCycle(g) == "3->5->6->3");
        

        vector<vector<int>> graph5 = {{0, 1, 1, 0, 0, 0, 0}, 
                                      {1, 0, 0, 0, 0, 0, 0}, 
                                      {1, 0, 0, 1, 1, 0, 0}, 
                                      {0, 0, 1, 0, 0, 1, 1}, 
                                      {0, 0, 1, 0, 0, 1, 0}, 
                                      {0, 0, 0, 1, 1, 0, 1}, 
                                      {0, 0, 0, 1, 0, 1, 0}};
        g.loadGraph(graph5);
        // test unDirected with cycle with 3 vexes that 
        // doesn't start at the root of the dfs tree:
        CHECK(ariel::Algorithms::isContainsCycle(g) == "2->3->5->4->2");

    }
    
    TEST_CASE("Test isBipartite")
    {
        ariel::Graph g({{0, 0, 1, 1, 0}, 
                        {1, 0, 0, 0, 1}, 
                        {0, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 0}, 
                        {0, 0, 0, 0, 0}});
        // test directed bipartite graph:
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 4}, B={1, 2, 3}");

        vector<vector<int>> graph = {{0, 1, 0, 0}, 
                                    {1, 0, 1, 2}, 
                                    {0, 1, 0, 0}, 
                                    {0, 2, 0, 0}};
        g.loadGraph(graph);
        // test unDirected bipartite graph:
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 3}, B={1}");

        vector<vector<int>> graph2 = {{0, 1, 0, 0, 0}, 
                                    {0, 0, 1, 0, 0}, 
                                    {0, 0, 0, 1, 0}, 
                                    {0, 1, 0, 0, 0}, 
                                    {0, 0, 0, 0, 0}};
        g.loadGraph(graph2);
        // test directed with cycle with 3 vexes(the root is not in the cycle):
        CHECK(ariel::Algorithms::isBipartite(g) == "0");

        vector<vector<int>> graph3 = {{0, 1, 0, 0, 3}, 
                                        {1, 0, 1, 2, 0}, 
                                        {0, 1, 0, 5, 0}, 
                                        {0, 2, 5, 0, 0}, 
                                        {3, 0, 0, 0, 0}};
        g.loadGraph(graph3);
        // test undirected with 3 vexes cycle:(the root is not in the cycle)
        CHECK(ariel::Algorithms::isBipartite(g) == "0");

        vector<vector<int>> graph4 = {{0, 0, 1, 1, 0}, 
                                        {1, 0, 0, 0, 1}, 
                                        {0, 0, 0, 0, 0}, 
                                        {0, 0, 0, 0, 0}, 
                                        {0, 0, 0, 0, 0}};
        g.loadGraph(graph4);
        // test directed bipartite graph which it's coloring we'll start not from a root.
        // but from some node which has nodes that get to it but he can't get to them.
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 4}, B={1, 2, 3}");
        
        vector<vector<int>> graph5 = {{0, 0, 0, 0, 0, 1, 1, 0}, 
                                        {0, 0, 0, 3, 0, 0, 0, 0}, 
                                        {0, 0, 0, 0, 0, 0, 0, 1}, 
                                        {5, 0, 0, 0, 1, 0, 0, 0}, 
                                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                                        {0, 0, 0, 0, 0, 0, 0, 0}, 
                                        {0, 0, 0, 0, 0, 0, 0, 0}};
        g.loadGraph(graph5);
        // test like the one above but more complex:
        CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 1, 2, 4}, B={3, 5, 6, 7}");
    }

    TEST_CASE("Test getNegativeCycle"){
        ariel::Graph g({{0, -3, 1, 1}, 
                        {0, 0, 2, 0}, 
                        {1, 2, 0, 1}, 
                        {0, 0, 1, 0}});
        // test directed with no negative cycle but zero weight cycle:
        CHECK(ariel::Algorithms::getNegativeCycle(g) == "0");
    
        ariel::Graph g2({{0, 0, 1, 0}, 
                        {0, 0, 1, 0}, 
                        {1, 0, 0, 1}, 
                        {1, -3, 1, 0}});
        // test directed with negative cycle with 3 vexes (the cycle doesn't start at the root of the dfs tree):
        CHECK(ariel::Algorithms::getNegativeCycle(g2) == "2->3->1->2");

        ariel::Graph g3({{0, 1, 1, 0}, 
                        {1, 0, 0, 0}, 
                        {1, 1, 0, -1}, 
                        {3, 0, -1, 0}});
        // test directed with negative bidirectional edge but no negative cycle longer then 2 vexs(the edge isn't connected to the root of the dfs tree):
        CHECK(ariel::Algorithms::getNegativeCycle(g3) == "2->3->2");

        ariel::Graph g4({{0, 2, 1}, 
                        {2, 0, -3}, 
                        {1, -3, 0}});
        // test undirected with no negative cycle but zero weight cycle:
        CHECK(ariel::Algorithms::getNegativeCycle(g4) == "0");

        ariel::Graph g5({{0, 3, 0, 0}, 
                        {3, 0, 1, -4}, 
                        {0, 1, 0, 2}, 
                        {0, -4, 2, 0}});
        // test unDirected with negative cycle with 3 vexes (the cycle doesn't start at the root of the dfs tree):
        CHECK(ariel::Algorithms::getNegativeCycle(g5) == "1->2->3->1");

        ariel::Graph g6({{0, 0, -2}, 
                        {0, 0, -3}, 
                        {-2, -3, 0}});
        // test directed with negative bidirectional edge but no negative cycle:
        CHECK(ariel::Algorithms::getNegativeCycle(g6) == "0");
    }
}

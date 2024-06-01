#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

void checkGraphValues(const ariel::Graph& g, const vector<vector<int>>& expectedAdjMat
                        , const bool expectedIsDirected, const int expectedEdgeNum){
    CHECK(g.getAdjMat() == expectedAdjMat);
    CHECK(g.IsDirected() == expectedIsDirected);
    CHECK(g.getEdgesNum() == expectedEdgeNum);
}

TEST_SUITE("TEST addition operators"){
    TEST_CASE("Test: graph1+graph2"){
        ariel::Graph g1({{0, 1, 0},
                         {1, 0, 1},
                         {0, 1, 0}});
        ariel::Graph g2({{0, 1, 1},
                         {1, 0, 0},
                         {1, 1, 0}});
        ariel::Graph g3 = g1 + g2;// creating new graph object
        vector<vector<int>> expectedAdjMat = {{0, 2, 1},
                                            {2, 0, 1},
                                            {1, 2, 0}};
        // testing when need to update: the adjMat, 
        // the number of edges, and the isDirected bool.
        checkGraphValues(g3, expectedAdjMat, true, 6);
    }

    TEST_CASE("Test graph1 += graph2"){
        ariel::Graph g1({{0, 1, 0},
                         {1, 0, 1},
                         {0, 1, 0}});
        ariel::Graph g2({{0, 1, 1},
                        {1, 0, 0},
                        {1, 1, 0}});
        g1 += g2;// doesn't create new graph object.
        vector<vector<int>> expectedAdjMat = {{0, 2, 1},
                                            {2, 0, 1},
                                            {1, 2, 0}};
        // testing when need to update: the adjMat, 
        // the number of edges, and the isDirected bool.
        checkGraphValues(g1, expectedAdjMat, true, 6);
    }

    TEST_CASE("Test +graph"){
        ariel::Graph g1({{0, 1, 0},
                         {1, 0, 1},
                         {0, 1, 0}});
        ariel::Graph g2 = +g1;
        checkGraphValues(g2, g1.getAdjMat(), g1.IsDirected(), g1.getEdgesNum());
    }

    // test my addition: graph+=int
    TEST_CASE("TEST graph+=int"){
        ariel::Graph g({{0, 1, 0},
                        {1, 0, 1},
                        {0, 1, 0}});
        vector<vector<int>> incMat = {{0, 0, 0},
                                      {0, 0, 0},
                                      {0, 0, 0}};
        //testing when turning edges to 0:
        checkGraphValues(g+=(-1), incMat, false, 0);
        
        g.loadGraph({{0, 1, 0},
                     {1, 0, 1},
                     {0, 1, 0}});
        incMat = {{0, 2, 0},
                  {2, 0, 2},
                  {0, 2, 0}};
        checkGraphValues(g+=1, incMat, false, 4);
    }
    // noam: graph++ and ++graph only increment the adjMat cells which don't have
    //  0 in them(meaning there is an egde)

    TEST_CASE("TEST ++graph"){
        ariel::Graph g({{0, 1, 0},
                        {1, 0, 1},
                        {0, 1, 0}});
        vector<vector<int>> incMat = {{0, 2, 0},
                                      {2, 0, 2},
                                      {0, 2, 0}};
        checkGraphValues(++g, incMat, false, 4);
    }

    TEST_CASE("TEST graph++"){
        ariel::Graph g({{0, 1, 0},
                         {1, 0, 1},
                         {0, 1, 0}});
        vector<vector<int>> originalMat = g.getAdjMat();
        checkGraphValues(g++, originalMat, false, 4);
        vector<vector<int>> incMat = {{0, 2, 0},
                                      {2, 0, 2},
                                      {0, 2, 0}};
        checkGraphValues(g, incMat, false, 4);
    }
}

TEST_SUITE("TEST subtraction operators"){

    TEST_CASE("Test: graph1-graph2"){
        ariel::Graph g1({{0, 1, 0},
                         {1, 0, 1},
                         {0, 1, 0}});
        ariel::Graph g2({{0, 1, 1},
                         {1, 0, 0},
                         {1, 1, 0}});
        // testing when need to update: the adjMat, 
        // the number of edges.
        ariel::Graph g3 = g1 - g2;// creating new graph object
        vector<vector<int>> expectedAdjMat = {{0, 0, -1},
                                              {0, 0, 1},
                                              {-1, 0, 0}};
        checkGraphValues(g3, expectedAdjMat, true, 3);
    }

    TEST_CASE("Test graph1 -= graph2"){
        ariel::Graph g1({{0, 1, 0},
                         {1, 0, 1},
                         {0, 1, 0}});
        ariel::Graph g2({{0, 1, 1},
                         {1, 0, 0},
                         {1, 1, 0}});
        // testing when need to update: the adjMat, 
        // the number of edges.
        g1 -= g2;// doesn't create new graph object.
        vector<vector<int>> expectedAdjMat = {{0, 0, -1},
                                              {0, 0, 1},
                                              {-1, 0, 0}};
        checkGraphValues(g1, expectedAdjMat, true, 3);
    }

    TEST_CASE("Test -graph"){
        ariel::Graph g1({{0, 1, 0},
                         {1, 0, 1},
                         {0, 1, 0}});
        ariel::Graph g2 = -g1;
        vector<vector<int>> expectedAdjMat = {{0, -1, 0},
                                              {-1, 0, -1},
                                              {0, -1, 0}};
        checkGraphValues(g2, expectedAdjMat, false, 4);
    }

    TEST_CASE("TEST graph--"){
        ariel::Graph g({{0, 2, 0},
                        {2, 0, 2},
                        {0, 2, 0}});
        vector<vector<int>> originalMat = g.getAdjMat();
        checkGraphValues(g--, originalMat, false, 4);
        vector<vector<int>> decMat = {{0, 1, 0},
                                      {1, 0, 1},
                                      {0, 1, 0}};
        checkGraphValues(g, decMat, false, 4);
    }
    
    TEST_CASE("TEST --graph"){
        ariel::Graph g({{0, 2, 0},
                        {2, 0, 2},
                        {0, 2, 0}});
        vector<vector<int>> decMat = {{0, 1, 0},
                                      {1, 0, 1},
                                      {0, 1, 0}};
        checkGraphValues(--g, decMat, false, 4);
    }

}

TEST_SUITE("TEST relation operators"){

    TEST_CASE("Test: graph1 == graph2"){
        // test equal with different edges:
            ariel::Graph g1({{0,1,0},
                            {1,0,1},
                            {1,2,0}});
            ariel::Graph g2({{0,1,1},
                            {1,0,1},
                            {0,2,0}});
            
            CHECK((g1 == g2) == true);
        // endTest;

        // test v(gL) < v(gR) and e(gL) = e(gR):
            g1.loadGraph({{0,1,0},
                          {1,0,0},
                          {0,0,0}});
            g2.loadGraph({{0,1},
                          {1,0}});
            
            CHECK((g1==g2) == false);
        // endTest;
    }

    TEST_CASE("Test: graph1 != grpah2"){
        // test equal with different edges:
            ariel::Graph g1({{0,1,0},
                            {1,0,1},
                            {1,2,0}});
            ariel::Graph g2({{0,1,1},
                            {1,0,1},
                            {0,2,0}});
            
            CHECK((g1 != g2) == false);
        // endTest;

        // test v(gL) < v(gR) and e(gL) = e(gR):
            g1.loadGraph({{0,1,0},
                          {1,0,0},
                          {0,0,0}});
            g2.loadGraph({{0,1},
                          {1,0}});
            
            CHECK((g1!=g2) == true);
        // endTest;
    }

    TEST_CASE("Test: graph1.isContains(graph2)"){
        // test: equal isn't entails contains!
            ariel::Graph g1({{0,1,0},
                             {1,0,1},
                             {1,2,0}});
            ariel::Graph g2({{0,1,1},
                             {1,0,1},
                             {0,2,0}});
            
            CHECK(g1.isContains(g2) == false);
            CHECK(g2.isContains(g1) == false);
        // endTest;

        // test: same vex num
            g1.loadGraph({{0,1,0},
                          {1,0,1},
                          {1,2,0}});
            g2.loadGraph({{0,1,0},
                          {1,0,1},
                          {2,1,0}});
            
            CHECK(g1.isContains(g2) == true);

            g2.loadGraph({{0,1,2},
                          {0,0,1},
                          {0,1,0}});
            
            CHECK(g1.isContains(g2) == false);
        // endTest;

        // test: v(gLeft) > v(gRight)
            g1.loadGraph({{0,0,0},
                          {1,0,1},
                          {1,2,0}});
            g2.loadGraph({{0,0},
                          {1,0}});
            
            CHECK(g1.isContains(g2) == true);

            g2.loadGraph({{0,1},
                          {0,0}});
            CHECK(g1.isContains(g2) == false);
        // endTest;

        // test: v(gLeft) < v(gRight)
            g1.loadGraph({{0,0,0},
                          {1,0,1},
                          {1,2,0}});
            g2.loadGraph({{0,0},
                          {1,0}});

            CHECK(g2.isContains(g1) == false);
        // endTest;
    }

    TEST_CASE("Test: graph1.isStrictlyContains(graph2)"){
        
        ariel::Graph g1,g2;

        // test: stricly contains with only more vex
            g1.loadGraph({{0,1,0},
                          {1,0,0},
                          {0,0,0}});
            g2.loadGraph({{0,1},
                          {1,0}});
            CHECK(g1.isStrictlyContains(g2) == true);
        // test: stricly contains with only more edge
            g1.loadGraph({{0,1},
                          {1,0}});
            g2.loadGraph({{0,1},
                          {0,0}});
            CHECK(g1.isStrictlyContains(g2) == true);


        // test: contains but equal:
            g1.loadGraph({{0,1},
                          {1,0}});
            g2.loadGraph({{0,2},
                          {3,0}});
            CHECK(g1.isStrictlyContains(g2) == false);
        // test: not contains and equal
            g1.loadGraph({{0,1},
                          {0,0}});
            g2.loadGraph({{0,0},
                          {1,0}});
            CHECK(g1.isStrictlyContains(g2) == false);
    }

    TEST_CASE("Test: graph1>graph2"){
        ariel::Graph g1,g2;

        // condition 1 & 2:
            // test: *this strictly contains other: true!
                g1.loadGraph({{0,1,0},
                              {1,0,0},
                              {0,0,0}});
                g2.loadGraph({{0,1},
                              {1,0}});
                CHECK((g1 > g2) == true);
                
                g2.loadGraph({{0,0,0},
                              {1,0,0},
                              {0,0,0}});
                CHECK((g1 > g2) == true);
            // test: they are equal: false
                g1.loadGraph({{0,1},
                              {0,0}});
                g2.loadGraph({{0,0},
                              {1,0}});
                CHECK((g1 > g2) == false);
            // test: other strictly contains *this: false!
                g1.loadGraph({{0,1},
                              {1,0}});
                g2.loadGraph({{0,1,0},
                              {1,0,0},
                              {0,0,0}});
                CHECK((g1 > g2) == false);
                
                g1.loadGraph({{0,0,0},
                              {1,0,0},
                              {0,0,0}});
                CHECK((g1 > g2) == false);
        
        // condition 3 & 4:
            // test: e(*this) > e(other): true!
                g1.loadGraph({{0,1,1},
                              {0,0,0},
                              {0,0,0}});
                g2.loadGraph({{0,0,0},
                              {1,0,0},
                              {0,0,0}});
                CHECK((g1 > g2) == true);
            // test: e(*this) < e(other): false!
                g1.loadGraph({{0,1,1},
                              {0,0,0},
                              {0,0,0}});
                g2.loadGraph({{0,0,0},
                              {1,0,0},
                              {0,0,0}});
                CHECK((g2 > g1) == false);

        // condition 5 & 6:
            // test: v(*this) > v(other): true
                g1.loadGraph({{0,1,0},
                              {0,0,0},
                              {0,0,0}});
                g2.loadGraph({{0,0},
                              {1,0}});
                CHECK((g1 > g2) == true);
            // test: v(*this) < v(other): false
                g1.loadGraph({{0,1,0},
                              {0,0,0},
                              {0,0,0}});
                g2.loadGraph({{0,0},
                              {1,0}});
                CHECK((g2 > g1) == false);
    }

    // TEST_CASE("Test: graph1<graph2"){

    // }

    // TEST_CASE("Test: graph1<=graph2"){

    // }

    // TEST_CASE("Test: graph1>=graph2"){

    // }
}

TEST_SUITE("TEST multiplication operators"){
    TEST_CASE("Test graph1*graph2"){
        ariel::Graph g1({{0, 1, 0},
                         {1, 0, 1},
                         {0, 1, 0}});
        ariel::Graph g2({{0, 1, 1},
                         {1, 0, 2},
                         {1, 2, 0}});
        ariel::Graph g3 = g1 * g2;
        vector<vector<int>> expectedGraph = {{0, 0, 2},
                                             {1, 0, 1},
                                             {1, 0, 0}};
        checkGraphValues(g3, expectedGraph, true, 4);

        g1.loadGraph({{0,   1,-2,4},
                      {2,   0, 9,3},
                      {1,-100, 0,0},
                      {0,   0,-3,0}});
        g2.loadGraph({{0, -2, 0, 0},
                      {3, 0, 0, -4},
                      {2, 0, 0, 0},
                      {4, -1, 3, 0}});
        expectedGraph = {{0   ,-4,12, -4},
                         {30  , 0, 9,  0},
                         {-300,-2, 0,400},
                         {-6  , 0, 0,  0}};
        checkGraphValues(g1*g2, expectedGraph, true, 9);
    }

    // TEST_CASE("Test int*graph and graph*int"){
    //     ariel::Graph g({{0, 2, 0},
    //                     {1, 0, 1},
    //                     {0, 0, 0}});
    //     vector<vector<int>> expectedGraph1 = {{0, 4, 0},
    //                                           {2, 0, 2},
    //                                           {0, 0, 0}};
    //     checkGraphValues(2*g, expectedGraph1, true, 3);
    //     checkGraphValues(g*2, expectedGraph1, true, 3);
    // }
}

// TEST_SUITE("TEST output operator"){
//     TEST_CASE("Test cout<<graph"){
        
//     }
// }

// id:212631071, mail:noamsayada1@gmail.com
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <vector>
#include <queue>
#include <climits>
#include <stdexcept>
#include <stack>
#include <iostream>
#include <string>
#include <sstream>


// define INFINITY = INT_MAX:
#define INFINITY INT_MAX

using std::vector;
//! cycle search aid functions:

    bool ariel::Algorithms::canConstructCycle(const Graph& g,int rootVex
                            , std::vector<bool>& visited
                            , std::vector<bool>& inCurrDNSTree
                            , std::stack<int>& pathStack
                            , bool negativeOnly){
        // find cycle in a directed graph:
        if(g.IsDirected() == true)
            return canConstructCycleInDirectedGraph(g, rootVex, visited, inCurrDNSTree, pathStack, negativeOnly);
        // find cycle in an undirected graph:
        if(g.IsDirected() == false)
            return canConstructCycleInUnDirectedGraph(g, rootVex, visited, pathStack, negativeOnly);
        return false;
    }

    bool ariel::Algorithms::canConstructCycleInDirectedGraph(const Graph& g,int rootVex
                                                , std::vector<bool>& visited
                                                , std::vector<bool>& inCurrDNSTree
                                                , std::stack<int>& pathStack
                                                , bool negativeOnly){
        visited[rootVex] = true;
        inCurrDNSTree[rootVex] = true;
        pathStack.push(rootVex);

                // !recursive part:
        // base case of recursion: 
        //      rootVex found a back-edge that completes circle
        // check if can construct cycle 
        // from any of the neighbors of rootVex:
        for(int i=0; i<g.getSize(); i++){
            // if there is no edge
            if(g.getAdjMat()[rootVex][i] == 0) 
                continue;
            // if i is in the current search tree(even if i is the direct father of rootVex):
            if(inCurrDNSTree[i] && (negativeOnly == false || isNegativeCycle(g, pathStack, i))){
                pathStack.push(i); // pushing the connecting node.
                return true;
            }
            // if i isn't visited, check if you can construct cycle in it, if you can - return true:
            if(visited[i] == false && canConstructCycleInDirectedGraph(g, i, visited, inCurrDNSTree, pathStack, negativeOnly))
                return true;
            
            // else it's a cross edge and it can't complete a cycle.
        }
                // !end recursive part.

        // we didn't found a circle in the tree that spands from root vex
        // return false.
        inCurrDNSTree[rootVex] = false;
        if(pathStack.empty() == true)
            throw std::runtime_error("pathStack is empty");
        pathStack.pop();
        return false;
    }

    bool ariel::Algorithms::canConstructCycleInUnDirectedGraph(const Graph& g,int rootVex
                                                , std::vector<bool>& visited
                                                , std::stack<int>& pathStack
                                                , bool negativeOnly){
        visited[rootVex] = true;
        int parentOfRoot = -1;
        if(pathStack.empty() == false)
            parentOfRoot = pathStack.top();
        pathStack.push(rootVex);

                // !recursive part:
        // base case of recursion:
        // rootVex found a back-edge to his anscestor (not direct father!)
        for(int i=0; i<g.getSize(); i++){
            // if there is no edge - continue
            if(g.getAdjMat()[rootVex][i] == 0) 
                continue;
            // if i have already been visited, since the graph is undirected, 
            // it means that i is in the current search tree and is an ancestor of rootVex
            if(visited[i] && i != parentOfRoot && (negativeOnly == false || isNegativeCycle(g, pathStack, i))){
                pathStack.push(i); // pushing the connecting node.
                return true;
            }
            // if i isn't visited, check if you can construct cycle in it, if you can - return true:
            if(visited[i] == false && canConstructCycleInUnDirectedGraph(g, i, visited, pathStack, negativeOnly))
                return true;
        }
                // !end recursive part.
        // we didn't found a circle in the tree that spands from root vex
        // return false.
        if(pathStack.empty() == true)
            throw std::runtime_error("pathStack is empty");
        pathStack.pop();
        return false;                                                        
    }

bool ariel::Algorithms::isNegativeCycle(const Graph& g, std::stack<int> pathStack, int connectingVex){
    // if the pathStack is empty, there is no cycle
    if(pathStack.empty())
        return false;
    // if the pathStack has only one element, there is no cycle
    if(pathStack.size() == 1)
        return false;
    // if the pathStack has more then 1 element, check if the sum weight
    // is negative.
    // we assume that the pathStack contains a cycle that it's connecting node
    // is the connectingVex that we got in the function. and the other end of the cycle
    // (same node as connecting) appears somewhare deeper in the stack.
    // we need to reverse the pathStack to pathVec:
    vector<int> pathVec;
    pathVec.insert(pathVec.begin(), connectingVex);
    while(pathStack.top() != connectingVex){
        pathVec.insert(pathVec.begin(), pathStack.top());
        pathStack.pop();
        if(pathStack.empty())
            throw std::invalid_argument("pathStack doesn't contain the connecting node");
    }
    pathVec.insert(pathVec.begin(), connectingVex); // inserting the connecting node in the end.
    // now compute the sum using pathVec:
    int sum = 0;
    for(int i=0; i<pathVec.size()-1; i++){
        if(pathVec[i]>=g.getAdjMat().size() || pathVec[i+1]>=g.getAdjMat()[pathVec[i]].size())
            throw std::invalid_argument("pathVec contains vex that are out of the graph size");
        sum += g.getAdjMat()[pathVec[i]][pathVec[i+1]];
    }
    return sum < 0;
}

    std::string ariel::Algorithms::isContainsSignedCycle(const Graph& g, bool negativeOnly){
        vector<bool> visited(g.getSize(), false);
        vector<bool> inCurrDNSTree(g.getSize(), false);
        std::stack<int> pathStack;
        // for every vex, check if there is a cycle in any of the 
        // vertexes that are reachable from vex.
        bool hasCycle = false;
        for(int i=0; i<g.getSize(); i++){
            if(visited[i]==false && canConstructCycle(g, i, visited, inCurrDNSTree, pathStack, negativeOnly) == true){
                hasCycle = true;
                break;
            }
        }
        
        // if there is no cycle, return "0"
        if(hasCycle == false)
            return "0";
        
        // else, copy the reverse of the "pathStack"
        // to "cycleStack" stack but only the part of the cycle
        // the one who starts and endS in the connecting vex
        std::stack<int> cycleStack;
        int connectingVex = pathStack.top();
        pathStack.pop();
        cycleStack.push(connectingVex);
        // push from pathStack to cycleStack until encontering the
        // connectingVex 
        while(pathStack.top()!=connectingVex){
            cycleStack.push(pathStack.top());
            pathStack.pop();
            if(pathStack.empty() == true)
                throw std::runtime_error("pathStack is empty");
        }

        // build the cycle path string
        std::string cycleString; 
        cycleString += std::to_string(connectingVex);
        while(cycleStack.empty() == false){
            cycleString += "->" + std::to_string(cycleStack.top());
            cycleStack.pop();
        } 

        return cycleString;
    }

//! cycle search main functions:

std::string ariel::Algorithms::isContainsCycle(const Graph& g){
    return isContainsSignedCycle(g, false);
}

std::string ariel::Algorithms::getNegativeCycle(const Graph& g){
    return isContainsSignedCycle(g, true);
}

//! all is connected functions:

bool ariel::Algorithms::isRoot(const Graph& g, int vex){
    std::vector<int> enqueued(g.getSize(), 0);
    std::queue<int> q;
    q.push(vex);
    int curr;
    while(q.empty() == false){
        curr = q.front(); //get the first element in the q
        q.pop(); // remove the first element in the q
        
        // enter all the nighebors of curr, who wasn't enqueued, to the queue
        for(int i=0; i<g.getSize(); i++){
            // if:
            //    1. curr != i 
            //    2. there is an edge from curr to i 
            //    3. i wasn't enqueued
            // then: enter i to the queue
            if(curr!=i && g.getAdjMat()[curr][i] != 0 && enqueued[i]==false){
                q.push(i);
                enqueued[i] = true;
            }
        }
    }
    
    for(int i=0; i<g.getSize(); i++){
        if(enqueued[i] == false)
            return false;
    }
    
    return true;
}

bool ariel::Algorithms::isConnected(const Graph& g){
    // choose a random vex, and check if:
    // 1. it's a root in the original graph (meaning it can reach all the other vexes)
    // 2. it's a root in the reveresed graph (meaning all the other vexes can reach it)
    if(isRoot(g,0) && (g.IsDirected() == false || isRoot(g.getReveresedGraph(),0)))
        return true;
    return false;
}


//! all shortestPath functions:

vector<vector<int>> ariel::Algorithms::bellmanFord(const Graph& g, int src){

    // create a vector containing dist from src to each vex. and sets the values to INFINITY(INT_MAX)
    vector<int> Dist(g.getSize(),INFINITY);
    Dist[src] = 0;
    // for each vex, Prev stores the vertex privous to vex in the lightest path from
    // src to vex.
    vector<int> Prev(g.getSize(),-1);

    // loop vex_num - 1 times:
    for(int i=0; i<g.getSize()-1; i++){
        // relax all the edges in a random order:
        for(int u=0; u<g.getSize(); u++){
            for(int v=0; v<g.getSize(); v++){
                // if: 1. u != v
                //     2. there is an edge from u to v
                //     2. Dist[u] != INFINITY
                //     3. Dist[v] > Dist[u] + weight(u,v)
                // then: update Dist[v] and Prev[v]
                if(u!=v && g.getAdjMat()[u][v] != 0 && Dist[u]!=INFINITY && Dist[v] > Dist[u] + g.getAdjMat()[u][v]){
                    Dist[v] = Dist[u] + g.getAdjMat()[u][v];
                    Prev[v] = u;
                }
            }
        }
    }

    // check for negative cycles:
    for(int u=0; u<g.getSize(); u++){
        for(int v=0; v<g.getSize(); v++){
            if(u!=v && g.getAdjMat()[u][v] != 0 && Dist[u]!=INFINITY && Dist[v] > Dist[u] + g.getAdjMat()[u][v]){
                // there is a negative cycle
                throw std::invalid_argument("Graph contains a negative cycle! can't find shortest paths");
            }
        }
    }
    return {Dist, Prev};
}

std::string ariel::Algorithms::shortestPath(const Graph& g, int src, int dest){
    vector<vector<int>> res = bellmanFord(g, src);
    vector<int> Dist = res[0];
    vector<int> Prev = res[1];

    // if Dist == INFINITY, there is no path from src to dest
    if(Dist[dest] == INFINITY)
        return "-1";
    
    
    // build the path from src to dest using a stack
    std::stack<int> path;
    int curr = dest;
    while(curr != src){
        path.push(curr);
        curr = Prev[curr];
    }

    std::string pathStr = std::to_string(src);
    while (path.empty() == false){
        pathStr += "->" + std::to_string(path.top());
        path.pop();
    }

    return pathStr;
}

//! all isBipartite functions:

bool ariel::Algorithms::can2color(const Graph& g, int vex, int currColor, std::vector<int>& colors){
    colors[vex] = currColor;

	for (int i = 0; i < g.getSize(); i++){
        // if there is an edge from vex to i or from i to vex:
		if (g.getAdjMat()[vex][i] != 0 || g.getAdjMat()[i][vex] != 0){
			if (colors[i] == -1){
                // check if you can color the neighbor with the other color
                // and then he can color his neighbors recursively.
				if (can2color(g, i, ((currColor == 0) ? 1 : 0) , colors) == false)
					return false;
			}
            // if the neighbor is already colored with the same color, then we can't
            // color the graph with 2 colors
			else if (colors[i] == currColor) 
				return false;
		}
	}
	return true;
}

std::string ariel::Algorithms::isBipartite(const Graph& g){
    vector<int> colors(g.getSize(), -1);

	for (int i = 0; i < g.getSize(); i++){
		if (colors[i] == -1){
			if (can2color(g, i, 0, colors) == false)
				return "0";
		}
	}

	// build the sets string
	vector<int> setA, setB;
	for (int i = 0; i < colors.size(); i++)
	{
		if (colors[i] == 0)
			setA.push_back(i);
		else
			setB.push_back(i);
	}

	// "The graph is bipartite: A={0, 2}, B={1, 5, 7}."
	std::stringstream ss;
	ss << "The graph is bipartite: A={";
	for (int i = 0; i < setA.size(); i++)
	{
		ss << setA[i];
		if (i < setA.size() - 1)
			ss << ", ";
	}
	ss << "}, B={";
	for (int i = 0; i < setB.size(); i++)
	{
		ss << setB[i];
		if (i < setB.size() - 1)
			ss << ", ";
	}
	ss << "}";
	return ss.str();
}

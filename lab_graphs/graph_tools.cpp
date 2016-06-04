/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
void GraphTools::initializeGraph(Graph& graph)
{
	vector<Vertex> vertices = graph.getVertices();
    for(auto & it:vertices)
    {
    	graph.setVertexLabel(it, "UNEXPLORED");
    	vector<Vertex> adjacentVertices = graph.getAdjacent(it);
    	for(auto & adj:adjacentVertices)
    		graph.setEdgeLabel(it, adj, "UNEXPLORED");
    }


}

int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    // Initially label vertices and edges as unvisited.
    vector<Vertex> vertices = graph.getVertices();
    initializeGraph(graph);

    // BFS
    int minweight;
    int curweight;
    Vertex v = graph.getStartingVertex();
    vector<Vertex> adjacentVertices = graph.getAdjacent(v);
    minweight = graph.getEdgeWeight(v, adjacentVertices[0]); // initialize the minweight
    for(auto & it:vertices)
    {
    	if(graph.getVertexLabel(it) == "UNEXPLORED")
    	{
    		curweight = BFSFindMinWeight(graph, it);
    		if(curweight < minweight)
    			minweight = curweight;
    	}
    		
    }
    return minweight;
}

int GraphTools::BFSFindMinWeight(Graph& graph, Vertex v)
{
	int minweight;
    int curweight;
    vector<Vertex> adjacentVertices = graph.getAdjacent(v);
    minweight = graph.getEdgeWeight(v, adjacentVertices[0]);
    Vertex curMinSource = v;
    Vertex curMinDest =  adjacentVertices[0]; // initialize the minweight

	queue<Vertex> q;
	q.push(v);
	graph.setVertexLabel(v, "VISITED");
	while(!q.empty())
	{
		Vertex curVertex = q.front();
		q.pop();
		vector<Vertex> adjacentVertices = graph.getAdjacent(curVertex);
		for(auto & it:adjacentVertices)  // for all w in G.adjacentVertices(v)
		{
			if(graph.getVertexLabel(it) == "UNEXPLORED")  // if it is new
			{
				graph.setVertexLabel(it, "VISITED");
				graph.setEdgeLabel(curVertex, it, "DISCOVERY");
				q.push(it);
				curweight = graph.getEdgeWeight(curVertex, it);
				if(curweight < minweight)
				{
					minweight = curweight;
					curMinSource = curVertex;
					curMinDest = it;

				}	
			}
			else if(graph.getEdgeLabel(curVertex, it) == "UNEXPLORED")// if it is NOT new but the edge is UNEXPLORED
			{
				graph.setEdgeLabel(curVertex, it, "CROSS");
				curweight = graph.getEdgeWeight(curVertex, it);
				if(curweight < minweight)
				{
					minweight = curweight;
					curMinSource = curVertex;
					curMinDest = it;
				}	
			}
		}
	}
	graph.setEdgeLabel(curMinSource, curMinDest, "MIN");
	return minweight;
}


/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */

int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    vector<Vertex> vertices = graph.getVertices();
    unordered_map<Vertex, int> dist;
    unordered_map<Vertex, Vertex> parent;

    initializeGraph(graph);

    // initialize the dist map
    dist[start] = 0;

    queue<Vertex> q;
	q.push(start);
	graph.setVertexLabel(start, "VISITED");
	while(!q.empty())
	{
		Vertex curVertex = q.front();
		q.pop();
		vector<Vertex> adjacentVertices = graph.getAdjacent(curVertex);
		for(auto & it:adjacentVertices)  // for all w in G.adjacentVertices(curVertex)
		{
			if(graph.getVertexLabel(it) == "UNEXPLORED")  // if it is new
			{
				graph.setVertexLabel(it, "VISITED");
				graph.setEdgeLabel(curVertex, it, "DISCOVERY");
				q.push(it);
				dist[it] = dist[curVertex] + 1;
				parent[it] = curVertex;
				
			}
			else if(graph.getEdgeLabel(curVertex, it) == "UNEXPLORED")// if it is NOT new but the edge is UNEXPLORED
			{
				graph.setEdgeLabel(curVertex, it, "CROSS");
				int curDist = dist[curVertex] + 1;
				auto lookup = dist.find(it);
				if(lookup->second > curDist)
				{
					dist[it] = curDist;
					parent[it] = curVertex;
				}	
			}
		}
	}

	// set the edges in the shortest path
	Vertex curParent = end;
	while(curParent != start)
	{
		graph.setEdgeLabel(curParent, parent[curParent], "MINPATH");
		curParent = parent[curParent];
	}

	return dist[end];
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */

void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    initializeGraph(graph);

    // sort the edges
    vector<Edge> edges = graph.getEdges();
    sort(edges.begin(), edges.end());

    int count = 0;
    vector<Vertex> vertices = graph.getVertices();
    int numVert = vertices.size();
    DisjointSets verticeSet;
    verticeSet.addelements(numVert);

    for(auto & curEdge : edges)
    {
    	int source = verticeSet.find(curEdge.source);
    	int dest = verticeSet.find(curEdge.dest);
    	if( source != dest)
    	{
    		verticeSet.setunion(source, dest);
    		graph.setEdgeLabel(curEdge.source, curEdge.dest, "MST");
    		count++;
    	}
    	if(count == numVert - 1)
    		break;
    }

}


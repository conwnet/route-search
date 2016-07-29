/**
	
*/

#ifndef _route_edge_h
#define _route_edge_h 1

#include <stdlib.h>
#include "route_time.h"

// the edge
struct Edge {
	int to, cost, service_id, trip_id, next, type;
	Time departure_time, arrival_time;
};


/// the graph used Adj List
struct Graph {
	int max_vertex, max_edge, edge_count;
	char **stop_name;	/// save the Chinese stop name index by stop_id
	int *head;	/// Adj List's head
	Edge *edge;

	Graph(int max_vertex, int max_edge) {
		this->max_vertex = max_vertex;
		this->max_edge = max_edge;
		head = (int *)malloc(sizeof(int) * max_vertex);
		edge = (Edge *)malloc(sizeof(Edge) * max_edge);
		stop_name = (char **)malloc(sizeof(char *) * max_vertex);
		for(int i = 0; i < max_vertex; i++)
			stop_name[i] = (char *)malloc(sizeof(char) * 50);
		edge_count = 0;
	}

	/// create an edge, return the index in edge arrays
	int create_edge(int to, int service_id, int trip_id,
		const Time &departure_time, const Time &arrival_time) {
		edge[edge_count].to = to;
		edge[edge_count].service_id = service_id;
		edge[edge_count].trip_id = trip_id;
		edge[edge_count].type = 1;
		edge[edge_count].departure_time = departure_time;
		edge[edge_count].arrival_time = arrival_time;

	}

	/// add an edge into the Adj List
	void add_edges(int from, int edge_number) {
		edge[edge_number].next = head[from];
		head[from] = edge_number;
	}


};


#endif

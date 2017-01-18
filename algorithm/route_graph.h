/**
    
*/

#ifndef _route_graph_h
#define _route_graph_h 1

#include <stdlib.h>
#include <string.h>
#include "route_time.h"

// the answer
struct Route {
    Time time;
    int deep, prev, trip_id;
};

// the trip
struct Trip {
    int from, to, start, cost, trip_id, service_id, next;
};

// the Transfer
struct Transfer {
    int from, to, cost, next;
};

/// the graph used Adj List
struct Graph {
    int max_vertex, max_trip, max_transfer, stop_count, trip_count, transfer_count;
    char **stop_name;    /// save the Chinese stop name index by stop_id
    int *trip_head, *transfer_head, *stop_type;    /// Adj List's head
    Trip *trip;
    Transfer *transfer;

    Graph(int max_vertex, int max_trip, int max_transfer) {
        this->max_vertex = max_vertex;
        this->max_trip = max_trip;
        this->max_transfer = max_transfer;

        trip_head = (int *)malloc(sizeof(int) * max_vertex);
        memset(trip_head, -1, sizeof(int) * max_vertex);
        transfer_head = (int *)malloc(sizeof(int) * max_vertex);
        memset(transfer_head, -1, sizeof(int) * max_vertex);

        stop_name = (char **)malloc(sizeof(char *) * max_vertex);
        stop_type = (int *)malloc(sizeof(int) * max_vertex);
        trip = (Trip *)malloc(sizeof(Trip) * max_trip);
        transfer = (Transfer *)malloc(sizeof(Transfer) * max_transfer);

        for(int i = 0; i < max_vertex; i++)
            stop_name[i] = (char *)malloc(sizeof(char) * 50);

        stop_count = 0;
        trip_count = 0;
        transfer_count = 0;
    }

    /// create a trip, return the index in trip array
    int create_trip(int from, int to, 
        int start, int cost, int trip_id = 0, int service_id = 0) {
    
        trip[trip_count].from = from;
        trip[trip_count].to = to;
        trip[trip_count].start = start;
        trip[trip_count].cost = cost;;
        trip[trip_count].service_id = service_id;
        trip[trip_count].trip_id = trip_id;

        return trip_count++;
    }

    /// add a trip into the Adj List
    void add_trip(int trip_number) {
        trip[trip_number].next = trip_head[trip[trip_number].from];
        trip_head[trip[trip_number].from] = trip_number;
    }

    /// create a transfer, return the index in transfer array
    int create_transfer(int from, int to, int cost) {
        transfer[transfer_count].from = from;
        transfer[transfer_count].to = to;
        transfer[transfer_count].cost = cost;
        return transfer_count++;
    }

    /// add a transfer into the Adj List
    void add_transfer(int transfer_number) {
        transfer[transfer_number].next = transfer_head[transfer[transfer_number].from];
        transfer_head[transfer[transfer_number].from] = transfer_number;
    }


};


#endif


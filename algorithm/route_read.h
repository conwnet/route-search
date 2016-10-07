#ifndef _route_read_h
#define _route_read_h 1

#include "route_graph.h"

#define CALENDAR_PATH "../data/calendar.in"
#define STOPS_PATH "../data/stops.in"
#define STOP_TIMES_PATH "../data/stop_times.in"
#define TRANSFERS_PATH "../data/transfers.in"
#define TRIPS_PATH "../data/trips.in"

int file_read_stops(Graph *G)
{
    FILE *fp = fopen(STOPS_PATH, "r");
    int stop_id, stop_count = 0;
    double x, y;

    if(fp == 0) return 0;
    while(~fscanf(fp, "%d", &stop_id)) {
        fscanf(fp, "%s", G->stop_name[stop_id]);
        fscanf(fp, "%lf%lf", &x, &y);
        stop_count += 1;
    }
    fclose(fp);
    return G->stop_count = stop_count;
}

int file_read_stop_times(Graph *G)
{
    FILE *fp = fopen(STOP_TIMES_PATH, "r");
    int from, to, start, cost, trip_id, service_id, trip_count = 0;
    
    if(fp == 0) return 0;
    while(~fscanf(fp, "%d%d%d%d%d%d",
        &from, &to, &start, &cost, &trip_id, &service_id)) {
        int n = G->create_trip(from, to, start, cost, trip_id, service_id);
        G->add_trip(n);
        trip_count += 1;
    }
    fclose(fp);
    return trip_count;
}

int file_read_transfers(Graph *G)
{
    FILE *fp = fopen(TRANSFERS_PATH, "r");
    int from, to, cost, transfer_count = 0;
    
    if(fp == 0) return 0;
    while(~fscanf(fp, "%d%d%d", &from, &to, &cost)) {
        int n = G->create_transfer(from, to, cost);
        G->add_transfer(n);
        transfer_count++;
    }
    fclose(fp);
    return transfer_count;
}

int read_files(Graph *G)
{
    if(!file_read_stops(G)) return 0;
    if(!file_read_stop_times(G)) return 0;
    if(!file_read_transfers(G)) return 0;
    printf("read ok...\n");

    return 1;
}

#endif


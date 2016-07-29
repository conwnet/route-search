#include <stdio.h>
#include "route_time.h"
#include "route_edge.h"

#define CALENDAR_PATH "../data/calendar.in"
#define STOPS_PATH "../data/stops.in"
#define STOP_TIMES_PATH "../data/stop_times.in"
#define TRANSFERS_PATH "../data/transfers.in"
#define TRIPS_PATH "../data/trips.in"

Graph *G = new Graph(5000, 200000);

int file_read_stops()
{
	FILE *fp = fopen(STOPS_PATH, "r");
	int stop_id;
	double x, y;

	if(fp == 0) return 0;
	while(~fscanf(fp, "%d", &stop_id)) {
		fscanf(fp, "%s", G->stop_name[stop_id]);
		fscanf(fp, "%lf%lf", &x, &y);
	}
	fclose(fp);

	return 1;
}

int file_read_stop_times()
{
	
}

int read_files()
{
	if(!file_read_stops()) return 0;

	return 1;
}

int main()
{
	read_files();

	return 0;
}

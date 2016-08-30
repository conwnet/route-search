#include <stdio.h>
#include "route_read.h"


//int Dijkstra

int main()
{
	Graph *G = new Graph(5000, 200000, 10000);
	read_files(G);
	
	char s[2024];
	printf("%s\n\n", G->trip[0].departure_time.tostr(s));

	printf("%d %d %d\n", G->stop_count, G->trip_count, G->transfer_count);

	return 0;
}

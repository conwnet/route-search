#include <stdio.h>
#include "route_read.h"


int Dijkstra

int main()
{
	Graph *G = new Graph(5000, 200000, 10000);
	read_files(G);

	printf("%d %d %d\n", G->stop_count, G->trip_count, G->transfer_count);

	return 0;
}

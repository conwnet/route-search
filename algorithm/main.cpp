#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route_read.h"
#include "route_algorithm.h"

int main(int argc, char *argv[])
{
    //int from = 630;
    //int to = 2808;
    int from = 472;
    int to = 1186;
    const char *time = "2017-01-20 08:00:00";

    Graph *G = new Graph(8000, 200000, 10000);

    read_files(G);

    int n = SPFA(G, from, to, time, 186400, 7, 7);
    show_path(G, to);

    printf("耗时： %d s\n", n);
    printf("\n\n ---------------------- \n\n");

    int started = clock();
    Dijkstra(G, from, to, "2017-01-20 08:00:00");
    
    printf("\n\n程序运行时间: %lf\n", ((double)clock() - started) / CLOCKS_PER_SEC);


    return 0;
}











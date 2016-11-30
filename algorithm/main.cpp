#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route_read.h"
#include "route_algorithm.h"

int main(int argc, char *argv[])
{
    int from = 630;
    int to = 3112;
    const char *time = "2016-07-08 08:00:00";

    int started = clock();
    Graph *G = new Graph(8000, 200000, 10000);

    read_files(G);
    int readed = clock();

    SPFA(G, from, to, time, 864000, 7);
    //spfa(G, from, to);
    int searched = clock();

    show_path(G, to);

    printf("\nread time: %.6fs\nsearch time: %.6fs\n",
        (double)(readed - started) / CLOCKS_PER_SEC,
        (double)(searched - started) / CLOCKS_PER_SEC);

    return 0;
}


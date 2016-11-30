/**

*/

#ifndef _route_algorithm_h
#define _route_algorithm_h 1

#include <queue>
#include <stdlib.h>
#include <algorithm>

using namespace std;

Route *route;

void show_path(Graph *G, int to)
{
    printf("%s %s %d\n", G->stop_name[to], route[to].time.tostr(),
            route[to].trip_id);
    if(route[to].prev != -1) show_path(G, route[to].prev);
}

int SPFA(Graph *G, int from, int to, const char *time, int time_limit, int deep_limit)
{
    queue<int> que;
    //Time *dis = G->arrival;
    int maxv = G->max_vertex;
    //int *prev = G->pre_vertex;
    int *inq = (int *) malloc(sizeof(int) * maxv);
    route = (Route *) malloc(sizeof(Route) * maxv);

    for(int i = 0; i < maxv; i++) {
        route[i].time.inf();
        route[i].deep = 0;
        route[i].prev = -1;
        //dis[i].inf();
    }
    //memset(prev, -1, sizeof(int) * maxv);
    memset(inq, 0, sizeof(int) * maxv);

    que.push(from);
    inq[from] = 1;
    route[from].time = time;
    //dis[from] = time;

    while(!que.empty()) {
        int u = que.front(); que.pop(); inq[u] = 0;
        //if(dis[u] - time > time_limit)
            //continue;
        if(route[u].time - time > time_limit)
            continue;
        if(route[u].deep > deep_limit)
            continue;
        for(int i = G->trip_head[u]; i != -1; i = G->trip[i].next) {
            Trip &e = G->trip[i];
            //Time ti = dis[u].reset(e.start);
            Time ti = route[u].time.reset(e.start);
            if(ti + e.cost < route[e.to].time ||
                (ti + e.cost == route[u].time && e.trip_id == route[u].trip_id)) {
                if(e.trip_id != route[u].trip_id)
                    route[e.to].deep = route[u].deep + 1;
                else
                    route[e.to].deep = route[u].deep;
                route[e.to].time = ti + e.cost;
                route[e.to].trip_id = e.trip_id;
                //prev[e.to] = u;
                route[e.to].prev = u;
                if(!inq[e.to]) {
                    que.push(e.to);
                    inq[e.to] = 1;
                }
            }
        }
        for(int i = G->transfer_head[u]; i != -1; i = G->transfer[i].next) {
            Transfer &e = G->transfer[i];
            if(route[u].time + e.cost < route[e.to].time) {
                route[e.to].deep = route[u].deep;
                route[e.to].time = route[u].time + e.cost;
                route[e.to].trip_id = 0;
                //prev[e.to] = u;
                route[e.to].prev = u;
                if(!inq[e.to]) {
                    que.push(e.to);
                    inq[e.to] = 1;
                }
            }
        }
    }

    return 0;
}



/**
int spfa(Graph *G, int from, int to)
{
    typedef pair<int, Time> pit;
    queue<pit> que;
    int maxv = G->max_vertex;
    int *prev = G->pre_vertex;
    int *inq = (int *)malloc(sizeof(int) * maxv);
    long *dis = (long *)malloc(sizeof(long) * maxv);

    for(int i = 0; i < maxv; i++)
        G->arrival[i].inf();
    memset(prev, -1, sizeof(int) * maxv);
    memset(dis, 0x3f, sizeof(int) * maxv);
    memset(inq, 0, sizeof(int) * maxv);

    for(int i = G->trip_head[from]; i != -1; i = G->trip[i].next) {
        Trip &e = G->trip[i];
        que.push(pit(from, Time("2016-10-01 00:00:00").reset(e.start)));
    }
    inq[from] = 1;
    dis[from] = 0;

    while(!que.empty()) {
        pit p = que.front(); que.pop();
        int u = p.first; Time t = p.second; inq[u] = 0;
        for(int i = G->trip_head[u]; i != -1; i = G->trip[i].next) {
            Trip &e = G->trip[i];
            Time ti = t.reset(e.start);
            if(ti - t + dis[u] < dis[e.to]) {
                dis[e.to] = ti - t + dis[u];
                prev[e.to] = u;
                //if(!inq[e.to]) {
                    que.push(pit(e.to, ti));
                    inq[e.to] = 1;
                //}
            }
        }
        for(int i = G->transfer_head[u]; i != -1; i = G->transfer[i].next) {
            Transfer &e = G->transfer[i];
            if(dis[u] + e.cost < dis[e.to]) {
                dis[e.to] = dis[u] + e.cost;
                prev[e.to] = u;
                if(!inq[e.to]) {
                    que.push(e.to);
                    inq[e.to] = 1;
                }
            }
        }
    }
    printf("%ld\n", dis[to]);

    return 0;
}
*/

/**
int used[8000];
int Dijkstra(Graph *G, int from, int to, const char *time)
{
    priority_queue<pti, vector<pti>, greater<pti> > pq;
    for(int i = 0; i < maxn; i++)
        dis[i].inf();
    printf("%s\n", ctime(&dis[to].timer));
    memset(prev, -1, sizeof(prev));
    memset(used, 0, sizeof(used));
    pq.push(pti(time, from));
    dis[from] = time;
    while(!pq.empty()) {
        pti p = pq.top(); pq.pop();
        int u = p.second;
        if(p.second == to)
            break;
        if(dis[u] < p.first)
            continue;
        for(int i = G->trip_head[u]; i != -1; i = G->trip[i].next) {
            Trip &e = G->trip[i];
            Time ti = dis[u].reset(e.start);
            if(!used[e.to] && ti + e.cost < dis[e.to]) {
                dis[e.to] = ti + e.cost;
                prev[e.to] = u;
                pq.push(pti(dis[e.to], e.to));
            }
        }
    }
    
    show(G, to);
    printf("%s\n", ctime(&dis[to].timer));
    
}
*/

#endif


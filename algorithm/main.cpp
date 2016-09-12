#include <stdio.h>
#include <queue>
#include <algorithm>
#include "route_read.h"

using namespace std;

typedef pair<Time, int> pti;
const int maxn = 8000;
Time dis[8000];
int prev[maxn];

char time_str[80];
void show(Graph *G, int to)
{
    printf("%s %s\n", G->stop_name[to], dis[to].tostr(time_str));
    if(prev[to] != -1) show(G, prev[to]);
}

int used[8000];
int Dijkstra(Graph *G, int from, int to, const char *time)
{
    priority_queue<pti, vector<pti>, greater<pti> > pq;
    for(int i = 0; i < maxn; i++)
        dis[i].inf();
    memset(prev, -1, sizeof(prev));
    memset(used, 0, sizeof(used));
    pq.push(pti(time, from));
    dis[from] = time;
    while(!pq.empty()) {
        pti p = pq.top(); pq.pop();
        int u = p.second;
        
        used[u] = 1;
        if(p.second == to) {
        //    show(G, to);
            break;
        }
        if(dis[u] < p.first)
            continue;
        //printf("%s\n", G->stop_name[u]);
        for(int i = G->trip_head[u]; i != -1; i = G->trip[i].next) {
            Trip &e = G->trip[i];
            Time ti = dis[u].reset(e.start);
            //if(ti - dis[u] > 1200) continue;
            if(!used[e.to] && ti + e.cost < dis[e.to]) {
                dis[e.to] = ti + e.cost;
                prev[e.to] = u;
                pq.push(pti(dis[e.to], e.to));
            }
        }
/**
        for(int i = G->trip_head[u]; i != -1; i = G->transfer[i].next) {
            Transfer &e = G->transfer[i];
            //if(
        }
*/
    }
    
    //show(G, to, 0);
    printf("%s\n", ctime(&dis[to].timer));
    
}

int main()
{
    int c = clock();
    Graph *G = new Graph(5000, 200000, 10000);
    read_files(G);
    Dijkstra(G, 1651, 472, "2016-07-08 8:00:00");
    printf("%d\n", clock() - c);
/**
    Time b = "2016-07-08 12:00:00";
    Time t = Time(b.timer).reset(124);
    char s[80];
    printf("%d %s\n", t.timer, t.tostr(s));
*/    

    return 0;
}

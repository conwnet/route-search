#include <stdio.h>
#include <queue>
#include <algorithm>
#include "route_read.h"

using namespace std;


typedef pair<Time, int> pti;
const int maxn = 8000;
Time dis[8000];

int Dijkstra(Graph *G, int from, int to, const char *time)
{
	priority_queue<pti, vector<pti>, greater<pti> > pq;
	for(int i = 0; i < maxn; i++)
		dis[i].inf();
	pq.push(pti(time, from));
	dis[from] = time;
	while(!pq.empty()) {
		pti p = pq.top(); pq.pop();
		int u = p.second;

		if(dis[u] < p.first)
			continue;

		for(int i = G->trip_head[u]; i != -1; i = G->trip[i].next) {
			Trip &e = G->trip[i];
			if(dis[u] < e.departure_time
				&& e.arrival_time < dis[e.to]) {
				dis[e.to] = e.arrival_time;
				pq.push(pti(dis[e.to], e.to));
			}
		}

		for(int i = G->trip_head[u]; i != -1; i = G->transfer[i].next) {
			Transfer &e = G->transfer[i];
			if(
		}
	}
	
}

int main()
{
	Graph *G = new Graph(5000, 200000, 10000);
	read_files(G);
	
	Dijkstra(G, 1185, 472, "2016-07-08 12:00:00");

	return 0;
}

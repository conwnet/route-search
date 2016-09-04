#include <stdio.h>
#include <queue>
#include <algorithm>
#include "route_read.h"

using namespace std;

typedef pair<Time, int> pti;
const int maxn = 8000;
Time dis[8000];
int prev[maxn];

void show(Graph *G, int to, int deep)
{
	if(deep == 20) return ;
	printf("%s\n", G->stop_name[to]);
	if(prev[to] != -1) show(G, prev[to], deep + 1);
}

int Dijkstra(Graph *G, int from, int to, const char *time)
{
	priority_queue<pti, vector<pti>, greater<pti> > pq;
	for(int i = 0; i < maxn; i++)
		dis[i].inf();
	memset(prev, -1, sizeof(prev));
	pq.push(pti(time, from));
	dis[from] = time;
	while(!pq.empty()) {
		pti p = pq.top(); pq.pop();
		int u = p.second;

		if(p.second == to) {
			break;
		}
		if(dis[u] < p.first)
			continue;
		//printf("%s\n", G->stop_name[u]);
		for(int i = G->trip_head[u]; i != -1; i = G->trip[i].next) {
			Trip &e = G->trip[i];
			Time ti = dis[u].reset(e.start);
			//if(ti - dis[u] > 86400) continue;
			if(ti + e.cost < dis[e.to]) {
				dis[e.to] = ti + e.cost;
				//if(e.to == from) printf("error!\n");
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
	printf("%d\n", clock() - c);
	Dijkstra(G, 1185, 472, "2016-07-08 12:00:00");
	

	return 0;
}

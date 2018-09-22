#include <iostream>
#include <stack>
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <string>

using namespace std;

#define pb push_back
#define visitado 1

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

vi visit;
vi predecessor;
vector<vii> AdjList(100);
vector<int> topologia;


void dfs(int v){
	visit[v] = visitado;
	for(int i=0; i<(int)AdjList[v].size(); i++){
		if(visit[AdjList[v][i].first] != visitado){
			predecessor[AdjList[v][i].first] = v;
			dfs(AdjList[v][i].first);
		}
	}
	topologia.pb(v);
}

void bfs(int v){
	queue<int> q;
	q.push(v);
	predecessor[v] = -1;
	
	while(!q.empty()){
		int k = q.front();
		q.pop();
		for(int j=0; j<AdjList[k].size();j++){
			if(visit[AdjList[k][j].first] != visitado){
				visit[AdjList[k][j].first] = visitado;
				q.push(AdjList[k][j].first);
				predecessor[AdjList[k][j].first] = k;
			}
		}
		topologia.pb(k);
	}
}


int main(){
	int v1,v2;
	int n,m;
	scanf("%d %d", &n, &m);
	for(int i=0; i<n; i++) { //para todo os vertices
		visit.pb(-1); //marcando como nao  visitado
		predecessor.pb(-2);
	}
	while(scanf("%d %d", &v1, &v2) != EOF){
		if(v1 != 0 && v2 != 0){
			AdjList[v1].pb(make_pair(v2,0));
		//	AdjList[v2].pb(make_pair(v1,0));
		}
	}
	for(int i=1; i<n; i++){
		if(visit[i] != visitado)
			dfs(i);
	}
	for(int i=topologia.size()-1; i>=0; i--){
		printf("%d ", topologia[i]);
	}
	printf("\n");
	return 0;
}

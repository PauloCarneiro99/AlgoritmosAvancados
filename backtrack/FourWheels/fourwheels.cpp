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

typedef struct config
{
	int s1,s2,s3,s4;
	bool operator==(const config &b) const{
		if(s1 == b.s1 && s2 ==b.s2 && s3 == b.s3 && s4 == b.s4)
			return true;
		return false;
	}
}config;

typedef struct NO
{
	config atual;
	int peso;
	int qtd;
	bool operator<(const NO &a) const{
		return peso > a.peso;
	}
}NO;


char moves [8][4]= { {-1, 0, 0, 0 },
					 { 1, 0, 0, 0 },
					 { 0,-1, 0, 0 },
					 { 0, 1, 0, 0 },
					 { 0, 0,-1, 0 }, 
					 { 0, 0, 1, 0 },
					 { 0, 0, 0,-1 },
					 { 0, 0, 0, 1 } };

bool visitado [10][10][10][10];

priority_queue<NO> pq;

int distancia(int atual, int s){
	int aux = atual-s;
	int aux2 = s-atual;
	if(abs(aux) > abs(aux2))
		return abs(aux2);
	return abs(aux);
}

int heuristica(int cont, config atual, config desejada){
	int g = cont;
	int h = 0;
	h += distancia(atual.s1, desejada.s1);
	h += distancia(atual.s2, desejada.s2);
	h += distancia(atual.s3, desejada.s3);
	h += distancia(atual.s4, desejada.s4);
	return h +g;
}

int possivel_estado(config atual){
	return visitado[atual.s1][atual.s2][atual.s3][atual.s4];
}

void checa_estados(NO atual, config desejada){
	//montar os 8 estados e ver se eles sao possiveis;
	//calcula a distancia dos possiveis e enfileira
	config temp;
	for(int i=0; i<8; i++){
		temp.s1 = atual.atual.s1 + moves[i][0];
		if(temp.s1 == 10)
			temp.s1 = 0;
		else if(temp.s1 == -1)
			temp.s1 = 9;
		temp.s2 = atual.atual.s2 + moves[i][1];
		if(temp.s2 == 10)
			temp.s2 = 0;
		else if(temp.s2 == -1)
			temp.s2 = 9;
		temp.s3 = atual.atual.s3 + moves[i][2];
		if(temp.s3 == 10)
			temp.s3 = 0;
		else if(temp.s3 == -1)
			temp.s3 = 9;
		temp.s4 = atual.atual.s4 + moves[i][3];
		if(temp.s4 == 10)
			temp.s4 = 0;
		else if(temp.s4 == -1)
			temp.s4 = 9;
		if(!possivel_estado(temp)){
			visitado[temp.s1][temp.s2][temp.s3][temp.s4] = true;
			int peso = heuristica(atual.qtd, temp, desejada);
			NO aux;
			aux.peso = peso;
			aux.atual = temp;
			aux.qtd = atual.qtd + 1;
			pq.push(aux);
		}
	}
}


int wheels(config inic, config desejada){
	//insere o inic na pilha
	NO temp;
	temp.atual = inic;
	temp.peso = 0;
	temp.qtd = 0;
	pq.push(temp);
	while(!pq.empty()){
		NO aux = pq.top();
		if(aux.atual == desejada){
			return aux.qtd;
		}
		pq.pop();
		checa_estados(aux, desejada);
	}
	return -1;
}


int main(int argc, char const *argv[])
{
	int qtd;
	config inicial, desejada, proibido;
	int n;
	scanf("%d", &qtd);
	while(qtd>0){
		scanf("%d %d %d %d", &inicial.s1, &inicial.s2, &inicial.s3, &inicial.s4);
		scanf("%d %d %d %d", &desejada.s1, &desejada.s2, &desejada.s3, &desejada.s4);
		scanf("%d", &n);
		for(int i=0; i<10; i++){
			for(int j=0; j<10; j++){
				for(int k=0; k<10; k++){
					for(int m=0; m<10; m++){
						visitado[i][j][k][m] = false;
					}
				}
			}
		}
		for(int i=0; i<n; i++){
			scanf("%d %d %d %d", &proibido.s1, &proibido.s2, &proibido.s3, &proibido.s4);
			visitado[proibido.s1][proibido.s2][proibido.s3][proibido.s4] = true;
		}
		while(!pq.empty()){
			pq.pop();
		}
		int movimentos = wheels(inicial, desejada);
		printf("%d\n", movimentos);
		qtd--;
	}
	return 0;
}
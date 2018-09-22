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

int cont;
int linha(int *v, int lin){
	for(int i=0;i<8;i++){
		if(v[i] == lin)
			return 0;
	}
	return 1;
}

int coluna(int *v,int col){
	if(v[col] == -1){
		return 1;
	}
	return 0;
}

int diagonal(int *v, int lin, int col){
	for(int i=0; i<8; i++){
		if(v[i] != -1)
			if(abs(col-i) == abs(lin-v[i]))
				return 0;
	}
	return 1;
}

void eight_queens(int *v, int indice){
	if(indice == 8){
		printf("%2d      ",cont );
		for(int i=0; i<8; i++)
			printf("%1d ",v[i]+1);
		printf("\n");
		cont++;
	}
	else if(v[indice] == -1){
		for(int j=0;j<8;j++){
			if(linha(v,j) == 1 && coluna(v,indice) == 1 && diagonal(v,j,indice) == 1){
				v[indice] = j;
				eight_queens(v,indice+1);
				v[indice] = -1;
			}
		}
	}else{
		eight_queens(v,indice+1);
	}
}

int main(int argc, char const *argv[])
{
	int dataset;
	int lin,col;
	scanf("%d", &dataset);
	getchar();//tirando o blank line
	int v[8]; //uma posicao para cada coluna do tabuleiro, sendo que os valores correspondem a linha onde a rainha se encontra
	for(int i=0;i<8; i++)//inicializando o vetor
		v[i] = -1;
	//linha e coluna comecam de 1
	for(int i=0; i<dataset; i++){
		cont = 1;
		scanf("%d %d", &lin, &col);
		printf("SOLN	COLUMN\n");
		printf(" #		1 2 3 4 5 6 7 8\n\n");		v[col-1] = lin-1;
		eight_queens(v,0);
		if(i != dataset-1)
			printf("\n");
		v[col-1] = -1;
	}
	return 0;
}
#include <bits/stdc++.h>

using namespace std;

#define pb push_back

char **tabuleiro;
set< pair< pair<int, int> , int > > s; //set que armazenas todas as DIFERENTES possibilidades de vitoria
int contador = 0;

//essa matriz representa todos os possiveis movimentos no tabuleiro
char movimentos[4][2] = {1, 0, //indo para direita (movendo no eixo x -> eixo das colunas)
			-1, 0,	//indo para a esquerda (movendo no eixo x)
			0, 1,	//subindo (movendo no eixo y -> eixo das linhas)
			0, -1};	//descendo (movendo no eixo y)


/**
*	Funcao auxiliar que imprime a configuracao atual do tabuleiro para
*	acompanhar o decorrer do backtracking	
**/
void imprimeTabuleiro(int linha, int coluna){
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++)
			printf("%d ", tabuleiro[i][j]);
		printf("\n");
	}
}

/**
*	Funcao que checa se o movimento no tabuleiro eh valido, isto eh:
	1) esta dentro dos limites do tabuleiro
	2) esta se movimentando para um objeto nao vazio e de menor forca
**/
bool movimentoValido(int iAtual, int jAtual, int iProximo, int jProximo, int linha, int coluna){
	if((iProximo >= 0 && iProximo < linha) && (jProximo >= 0 && jProximo < coluna) && tabuleiro[iProximo][jProximo] != 0){
		if((tabuleiro[iAtual][jAtual] == 3 && tabuleiro[iProximo][jProximo] == 1) ||(tabuleiro[iAtual][jAtual] - tabuleiro[iProximo][jProximo] == -1)){
			return true;
		}
	}
	return false;
}


/**
*	Funcao que acha todas as diferentes configuracoes de vitoria atraves
*	de um algoritmo de backtracking
**/
void backtrack(int n, int linha, int coluna){
	if(n == 1){
		for(int i=0; i<linha; i++){ //procurando pelo vencedor
			for(int j=0; j<coluna; j++){
				if(tabuleiro[i][j] != 0){
					contador++;
					s.insert(make_pair(make_pair(i,j), tabuleiro[i][j]));		
				}
			} 
		}
	}else{
		for(int i=0; i< linha; i++){
			for(int j=0; j<coluna; j++){
				if(tabuleiro[i][j] != 0){
					for(int k=0; k<4; k++){
						if(movimentoValido(i,j, i + movimentos[k][0], j + movimentos[k][1], linha, coluna)){
							//modifica o tabuleiro
							int a, b;
							a = tabuleiro[i][j];
							tabuleiro[i][j] = 0;
							b = tabuleiro[i + movimentos[k][0]][j + movimentos[k][1]];
							tabuleiro[i + movimentos[k][0]][j + movimentos[k][1]] = a;
							backtrack(n-1, linha, coluna);
							//desmodifica o mapa para proximas interacoes
							tabuleiro[i][j] = a;
							tabuleiro[i + movimentos[k][0]][j + movimentos[k][1]] = b;
							
						}
					}
				}
			}
		}
	}
}

/**
*	Funcao de comparacao para ordenacao da saida
*	1) Ordenada de acordo com a linha do resultado
*	2) Desempata com a coluna
*	3) Desempata com o numero do objeto
**/
bool compara(pair <pair <int, int> , int> p1 , pair <pair <int, int> , int> p2){
	pair<int , int> temp1 = get<0>(p1);
	pair<int,int> temp2 = get<0>(p2);
	int a1 = get<0>(temp1), a2 = get<1>(temp1), a3 = get<1>(p1);
	int b1 = get<0>(temp2), b2 = get<1>(temp2), b3 = get<1>(p2);

	if(a1 < b1){
		return true;
	}else if(a1 == b1){
		if(a2 < b2){
			return true;
		}else if(a2 == b2){
			if(a3 < b3)
				return true;
			else
				return false;
		}
	}
	return false;
}	

void imprimeSaida(){
	vector<pair <pair <int, int> , int> > aux;
	for(auto u : s){
		aux.pb(u);
	}
	sort(aux.begin(), aux.end(), compara);
	for(auto u : aux){
		pair<int , int> temp1 = get<0>(u);
		int a1 = get<0>(temp1), a2 = get<1>(temp1), a3 = get<1>(u);
		printf("%d %d %d\n", a1+1, a2+1, a3);
	}	
}


int main(int argc, char const *argv[])
{
	int linha, coluna;
	int nroPecas = 0;

	scanf("%d %d", &linha, &coluna);

	//alocando o devido espaco para o tabuleiro	
	tabuleiro = (char**) malloc(sizeof(char*)*linha);
	for(int i=0; i<linha; i++)
		tabuleiro[i] = (char *) malloc(sizeof(char) * coluna);


	//lendo a configuracao inicial do tabuleiro
	for(int i =0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			int aux;
			scanf("%d", &aux);
			if(aux != 0)
				nroPecas++;
			tabuleiro[i][j] = aux;
		}
	}	
	

	backtrack(nroPecas, linha, coluna);
	printf("%d\n", contador);
	printf("%d\n", (int)s.size());	
	imprimeSaida();
	
	//liberando o espaco de memoria alocado para o tabuleiro
	for(int i=0; i<linha; i++)
		free(tabuleiro[i]);
	free(tabuleiro);
	return 0;
}

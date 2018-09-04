#include <bits/stdc++.h>

using namespace std;

#define pb push_back

char **tabuleiro;
set< pair< pair<int, int> , int > > s; //set que armazenas todas as DIFERENTES possibilidades de vitoria
vector< pair<int, int> > v; //vector que armazenas todas as possibilidades de vitoria

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
		//	printf("na funcao movimento valido: de (%d, %d) = %d para (%d, %d) = %d \n", iAtual, jAtual, tabuleiro[iAtual][jAtual] , iProximo, jProximo, tabuleiro[iProximo][jProximo]);
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
					v.pb(make_pair(i,j));
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
*	Essa funcao imprime a saida de acordo com as especificacoes, ordenando os resultados de acordo com a linha, desempatando pela coluna e depois pelo tipo do objeto
**/

void imprimeSaida(){
	vector<int> linhas;
	vector<int> colunas;
	vector<int> objetos;
	pair<int, int> aux;
	int  aux2;
	for(auto u : s){
		aux = u.first;
		aux2 = u.second;
		linhas.pb(aux.first);
		colunas.pb(aux.second);
		objetos.pb(aux2);
	}
	for(int i=0; i<(int)linhas.size()-1; i++){
		if(linhas[i] > linhas[i+1]){
			int temp = linhas[i+1];
			linhas[i+1] = linhas[i];
			linhas[i] = temp;
			temp = colunas[i+1];
			colunas[i+1] = colunas[i];
			colunas[i] = temp;
			temp = objetos[i+1];
			objetos[i+1] = objetos[i];
			objetos[i] = temp;
		}else if(linhas[i] == linhas[i+1]){
			if(colunas[i] > colunas[i+1]){			
				int temp = linhas[i+1];
				linhas[i+1] = linhas[i];
				linhas[i] = temp;
				temp = colunas[i+1];
				colunas[i+1] = colunas[i];
				colunas[i] = temp;
				temp = objetos[i+1];
				objetos[i+1] = objetos[i];
				objetos[i] = temp;

			}else if(colunas[i] == colunas[i+1]){
				if(objetos[i] > objetos[i+1]){			
					int temp = linhas[i+1];
					linhas[i+1] = linhas[i];
					linhas[i] = temp;
					temp = colunas[i+1];
					colunas[i+1] = colunas[i];
					colunas[i] = temp;
					temp = objetos[i+1];
					objetos[i+1] = objetos[i];
					objetos[i] = temp;
				}

			}

		}
		
	}
	for(int i=0; i< (int)linhas.size(); i++)
		printf("%d %d %d\n", linhas[i]+1, colunas[i]+1, objetos[i]);	
}

int main(int argc, char const *argv[])
{
	int linha, coluna;
	int nroPecas;

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
	printf("%d\n", (int)v.size());
	printf("%d\n", (int)s.size());	
	imprimeSaida();
	
	//liberando o espaco de memoria alocado para o tabuleiro
	for(int i=0; i<linha; i++)
		free(tabuleiro[i]);
	free(tabuleiro);
	return 0;
}

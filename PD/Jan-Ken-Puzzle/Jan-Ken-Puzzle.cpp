#include <bits/stdc++.h>

/**
*	COMPILE ESSE CODIGO USANDO:
*			g++ Jan-Ken-Puzzle.cpp -std=c++11 
**/


using namespace std;

#define pb push_back

unordered_map<long long,long long> m;

char tabuleiro[20][20];
set< pair< pair<int, int> , int > > s; //set que armazenas todas as DIFERENTES possibilidades de vitoria
set< pair< pair<int, int> , int > > temp;

long long contador = 0;

long long t = 0; //variavel que ira armazenar o conteudo do tabuleiro convertido para base 4
int conversion = 4; //variavel auxiliar na operacao de converter o tabuleiro para base 4

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
*	1) esta dentro dos limites do tabuleiro
*	2) esta se movimentando para um objeto nao vazio e de menor forca
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
*	Executa uma mini dfs afim de determinar se "eh um grafo bipartido", isto eh se possui ilhas ou nao
*	Se nao possuir ilhas, a partir de uma peca posso atingir todas as demais, caso a ilha exista o numero de pessas atingidas a partir de uma unica peca sera inferior
**/
void verificaIlha(int i, int j,int linha, int coluna, int n){
	for(int k=0; k<4; k++){
		if(i + movimentos[k][0] < linha && i + movimentos[k][0] >= 0 && j + movimentos[k][1] < coluna &&  j + movimentos[k][1] >= 0 && (tabuleiro[i + movimentos[k][0]][j + movimentos[k][1]] != 0) && temp.count(make_pair(make_pair(i + movimentos[k][0],j + movimentos[k][1]),tabuleiro[i + movimentos[k][0]][j + movimentos[k][1]])) == 0){
			temp.insert(make_pair(make_pair(i + movimentos[k][0], j + movimentos[k][1]),tabuleiro[i + movimentos[k][0]][j + movimentos[k][1]]));
			verificaIlha(i + movimentos[k][0], j + movimentos[k][1], linha, coluna, n);
		}
	}
}

/**
*	Return true indicando que esse nao eh um caminho viavel
*	Return false se nao foi formada nenhuma ilha nesse elemento
**/
bool isIlha(int i, int j,int linha, int coluna, int n){
	temp.clear();
	temp.insert(make_pair(make_pair(i,j),tabuleiro[i][j]));
	verificaIlha(i,j,linha,coluna,n);
	if((int)temp.size() != n){
		return true;
	}
	else
		return false;
}  

/**
*	Return true caso encontre alguma ilha
*	Return false se nao encontrou nenhum ilha no tabuleiro
*	Acha a primeira peca do tabuleiro e depois chama funcoes que irao verificar se eh uma ilha
**/
bool ilha(int linha, int coluna, int n){
	int i,j;
	bool f = false;
	for(i=0; i<linha; i++){
		for(j=0; j<coluna; j++){
			if(tabuleiro[i][j] != 0){
				f = true;
				break;
			}
		}
		if(f == true)
			break;
	}
	return isIlha(i,j, linha, coluna, n);
}

/**
*	Converte o tabuleiro para um numero inteiro em base 4
**/
void tabuleiroBase4(int linha, int coluna){
	t = 0;
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			t += tabuleiro[i][j]*pow(conversion, i*coluna + j);
		}
	}
}

/**
*	Funcao que acha todas as diferentes configuracoes de vitoria atraves
*	de um algoritmo de backtracking
**/
long long backtrack(int n, int linha, int coluna){
	long long aux =0;
	if(n == 1){
		for(int i=0; i<linha; i++){ //procurando pelo vencedor
			for(int j=0; j<coluna; j++){
				if(tabuleiro[i][j] != 0){
					contador++;
					s.insert(make_pair(make_pair(i,j), tabuleiro[i][j]));
					return 1;		
				}
			} 
		}
	}else if(m.count(t) != 0){
		contador += m[t];
		return m[t];
	}else{
		if(ilha(linha,coluna, n)){
			m[t] = 0;
			return m[t];
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
								t -= (a*pow(conversion, i*coluna + j) + b*pow(conversion, (i + movimentos[k][0])*coluna + j + movimentos[k][1]));
								t += (a*pow(conversion, (i + movimentos[k][0])*coluna + j + movimentos[k][1]));								
								
								aux += backtrack(n-1, linha, coluna);
						
								t -= (a*pow(conversion, (i + movimentos[k][0])*coluna + j + movimentos[k][1]));								
								t += (a*pow(conversion, i*coluna + j) + b*pow(conversion, (i + movimentos[k][0])*coluna + j + movimentos[k][1]));
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
	return m[t] = aux;
}

/**
*	Funcao de comparacao para ordenacao da saida
*	1) Ordenada de acordo com a linha do resultado
*	2) Desempata com a coluna
*	3) Desempata com o numero do objeto
**/
bool compara(pair <pair <int, int> , int> p1 , pair <pair <int, int> , int> p2){
	pair<int , int> temp1 = (p1).first;
	pair<int,int> temp2 = (p2).first;
	int a1 = (temp1).first, a2 = (temp1).second, a3 = (p1).second;
	int b1 = (temp2).first, b2 = (temp2).second, b3 = (p2).second;

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

/**
*	Funcao que imprime o Set contendo as diferentes respostas de maneira ordenada
**/
void imprimeSaida(){
	for(auto u : s){
		pair<int , int> temp1 = (u).first	;
		int a1 = (temp1).first, a2 = (temp1).second, a3 = (u).second;
		printf("%d %d %d\n", a1+1, a2+1, a3);
	}
}


int main(int argc, char const *argv[])
{
	int linha, coluna;
	int nroPecas = 0;
	scanf("%d %d", &linha, &coluna);


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
	
	tabuleiroBase4(linha,coluna);

	backtrack(nroPecas, linha, coluna);
	printf("%lld\n", contador);
	printf("%d\n", (int)s.size());	
	imprimeSaida();
	
	return 0;
}

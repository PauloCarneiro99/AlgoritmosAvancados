#include <bits/stdc++.h>

/**
*	COMPILE ESSE CODIGO USANDO:
*			g++ Jan-Ken-Puzzle.cpp -std=c++11 
**/


using namespace std;

#define pb push_back

unordered_map<int,int> m;

char **tabuleiro;
set< pair< pair<int, int> , int > > s; //set que armazenas todas as DIFERENTES possibilidades de vitoria
int contador = 0;

int t = 0; //variavel que ira armazenar o conteudo do tabuleiro convertido para base 4
int conversion = 0; //variavel auxiliar na operacao de converter o tabuleiro para base 4

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
*	Return true caso o contrario, indicando que esse nao eh um caminho viavel
*	Return false se nao foi formada nenhuma ilha nesse elemento
**/
bool isIlha(int iAtual, int jAtual,int linha, int coluna){
	if((iAtual+1 < linha && tabuleiro[iAtual + 1] != 0) ||  (iAtual-1 >= 0 && tabuleiro[iAtual -1] != 0) || (jAtual+1 < coluna && tabuleiro[jAtual + 1] != 0) || (jAtual-1 >= 0 && tabuleiro[jAtual - 1] != 0))
		return false;
	return true;
}

/**
*	Return true caso encontre alguhma ilha
*	Return false se nao encontrou nenhum ilha no tabuleiro
**/
bool ilha(int linha, int coluna){
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			if(tabuleiro[i][j] != 0){
				if(isIlha(i,j,linha,coluna))
					return true;
			}
		}
	}
	return false;
}

/**
*	Converte o tabuleiro para um numero inteiro em base 4
**/
int tabuleiroBase4(int linha, int coluna){
	conversion = 4;
	t = 0;
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			t += pow(conversion*tabuleiro[i][j], i*coluna + j);
		}
	}
}

/**
*	Funcao que acha todas as diferentes configuracoes de vitoria atraves
*	de um algoritmo de backtracking
**/
int backtrack(int n, int linha, int coluna){
	if(n == 1){
		for(int i=0; i<linha; i++){ //procurando pelo vencedor
			for(int j=0; j<coluna; j++){
				if(tabuleiro[i][j] != 0){
					contador++;
					s.insert(make_pair(make_pair(i,j), tabuleiro[i][j]));
					m[t]++;		
				}
			} 
		}
	}else{
		bool mov = false;
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
							if(!ilha(linha,coluna)){ //se formou uma ilha, nem devo insistir nessa chamada de backtraking
								t -= (pow(conversion*a, i*coluna + j) + pow(conversion*b, (i + movimentos[k][0])*coluna + j + movimentos[k][1]));
								t += (pow(conversion*a, (i + movimentos[k][0])*coluna + j + movimentos[k][1]));								
								
								//checando se essa configuracao de tabuleiro ja foi testada anteriormente
								if(m[t] == 0){ //essa configuracao ainda nao foi testada
									mov = true;
									m[t] += backtrack(n-1, linha, coluna);
								}else if(m[t] > 0){ //essa configuracao ja foi testada e chegou em uma resposta 
									mov = true;
									contador += m[t];
								}

								t -= (pow(conversion*a, (i + movimentos[k][0])*coluna + j + movimentos[k][1]));
								t += (pow(conversion*a, i*coluna + j) + pow(conversion*b, (i + movimentos[k][0])*coluna + j + movimentos[k][1]));
							}else{ //cheguei a uma ilha, essa configuracao nao tera respostas
								m[t] = -1;
							}
							//desmodifica o mapa para proximas interacoes
							tabuleiro[i][j] = a;
							tabuleiro[i + movimentos[k][0]][j + movimentos[k][1]] = b;
							
						}
					}
				}
			}
		}if(mov == false){ //nao realizou nenhum movimento nessa configuracao, logo ela nao tera resposta
			m[t] = -1;
			return 0;
		}
	}
	return m[t];
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
	
	tabuleiroBase4(linha,coluna);

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

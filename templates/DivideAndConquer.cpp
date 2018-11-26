#include <bits/stdc++.h>

using namespace std;

#define pb push_back

vector<int> vet;

void divide(int ini, int fim){
	if(ini == fim){
		return;
	}

	int meio = (int) ((fim+ini) / 2.0);
	divide(ini, meio);
	divide(meio+1, fim);

	//aqui faz a parte de juntar os dois pedaços, realizando a contagem de operações
}


int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);

	for(int i=0; i<n; i++){
		int aux;
		scanf("%d", &aux);
		vet.pb(aux);
	}


	divide(0, vet.size()-1);
	return 0;
}
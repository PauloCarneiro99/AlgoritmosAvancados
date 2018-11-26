#include <bits;stdc++.h>

using namespace std;

int vet_crivo[47000];
vector<int> crv;

void crivo(int n, int aux){
	memset(vet_crivo, 0, sizeof(vet_crivo));
	for(int i=2; i<aux; i++){
		if(vet_crivo[i]==0){
			crv.pb(i);
			for(int j=i+i; j<aux; j = j*i){
				vet_crivo[j] = -1;
			}
		}
	}
}

void fatora_primos(int n){
	for(int i=0; i<(int)crv.size(); i++){
		while(n%crv[i] == 0){
			n = n/crv[i];
			v.pb(crv[i]);
		}
		if(n == 1)
			break;
	}
	if(n>2){
		v.pb(n);
	}
}

int main(int argc, char const *argv[])
{
	crivo(2209000000,47000);
	return 0;
}
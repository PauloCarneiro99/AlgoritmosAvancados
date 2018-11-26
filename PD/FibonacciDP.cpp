#include <bits/stdc++.h>


using namespace std;

#define pb push_back

vector<int> memo;

//Complexidade numero de subproblemas . tempo de cada subproblema
//portanto no final fibDp eh O(n) de tempo e O(n) de memoria
int fibDp(int n){
	if(memo[n] != -1) return memo[n];
	if(n <2) return 1;
	else{
		memo[n] = fibDp(n-1) + fibDp(n-2);
		return memo[n]; 
	}
}
//fib recursivo sem DP , complixedade exponencial
int fib(int n){
	if(n < 2) return 1;
	else return fib(n-1) + fib(n-2);
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0; i<=n;i++)
		memo.pb(-1);
	printf("%d\n", fibDp(n));
	return 0;
}

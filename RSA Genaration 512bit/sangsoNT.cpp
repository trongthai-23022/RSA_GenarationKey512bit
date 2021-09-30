#include<bits/stdc++.h>
#include"Bigint.h"
using namespace std;
typedef long long ll;
ll data[1002];
bool isPrime[8000];
void sieve(ll N) {
	ll count = 1;
//    bool isPrime[N+1];
    for(ll i = 0; i <= N;++i) {
        isPrime[i] = true;
    }
    isPrime[0] = false;
    isPrime[1] = false;
    for(ll i = 2; i * i <= N; ++i) {
         if(isPrime[i] == true) {
             // Mark all the multiples of i as composite numbers
             for(ll j = i * i; j <= N; j += i){
                 isPrime[j] = false;
             }
        }
    }
    for(ll i = 0; i < N;i++){
    	if(isPrime[i] == true){
    		data[count] = i;
    		count++;
//   		cout<<"A"<<endl;
		}
	}  		
}
int main(){
	sieve(8000);
	for(ll i = 1; i < 1001; i++){
		cout<<data[i]<<" ";
		}
	ofstream file1 ("giatriNT.txt");
	for(ll i = 1; i < 1001; i++){
		file1<<data[i]<<endl;
	}
	file1.close();
	return 0;
}


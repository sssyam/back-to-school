#include<iostream>
using namespace std;

#define ll long long
#define M 1000000007

ll** create(){
	ll **temp = new ll*[2];
	for( int i=0; i<2; i++)
		temp[i] = new ll[2];
	return temp;
}

void fill (ll **x, int i=0){
	x[0][0] = 1;
	x[1][0] = x[0][1] = 1 - i;
	x[1][1] = i;
}

ll** multiply( ll** a, ll** b){
	ll** t = create();
	
	for( int i=0; i<2; i++){
		for( int j=0;j<2;j++){
			t[i][j] = 0;
			for(int k=0; k<2; k++)
				t[i][j] = ( t[i][j] % M + ( ( a[i][k] % M ) * ( b[k][j] % M ) ) % M ) % M;
		}
	}
	
	return t;
}

int* break_l(ll n){
	int *t = new int [41];
	for( int i=0; i<40; i++)
		t[i] = n & 1 << i ? 1 : 0;
	return t;
}

void print( int index, ll **a){
	cout << "Array for 2^" << index << " : " << endl;
	for( int i=0;i<2; i++){
		for( int j=0; j<2; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

int main2(){
	ll **a = create(), **b = create();
	fill(a,1); fill(b);
	print(1,a); print(1,b);
	print(1,multiply(a,b));
}

int main(){
	
	ll **a[41];
	ll **t = create();
	fill(t);
	a[0] = t;

	for( int i=1; i < 41; i++){
		a[i] = multiply(a[i-1], a[i-1]);
	}
	
	int k;
	cin >> k;
	
	while ( k-- ){
		
		ll n;
		cin >> n;
		
		ll **ans = create();
		fill(ans, 1);
		
		int c = 0;
		while ( n > 0 ){
			if (n & 1){
				ans = multiply(ans, a[c]);
			}
			c = c + 1;
			n = n >> 1;
		}
		
		cout << ans[1][0] << endl;
	}
}

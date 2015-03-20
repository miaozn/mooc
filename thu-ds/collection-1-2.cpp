#include <iostream>

using namespace std;



long long gcd(long long a, long long b){
	if(a == b) return a;
	if(a > b) return gcd(a- b, b);

	return gcd(a, b - a);
}

int main(){
	
	long long a,b;
	cin >> a >> b;

	cout << gcd(a,b) << endl;

	return 0;
}
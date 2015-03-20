#include <iostream>

using namespace std;

int main(){
	

	long long a,b, result;
	char op;

	cin >> a >> op >> b;
	switch(op){

		case '+': result = a + b; break;
		case '-': result = a - b; break;
		default : result = a * b;


	}

	cout << result << endl;


	return 0;
}
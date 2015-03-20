#include <iostream>
#include <cstdio>

using namespace std;



int main(){

	long h1, m1, s1;
	long h2, m2, s2;
	scanf("%ld:%ld:%ld %ld:%ld:%ld", &h1, &m1, &s1, &h2, &m2, &s2);
	long result = 3600* (h2-h1) + 60* (m2-m1)+ s2- s1;
	if(result < 0) result += 24 * 3600;
	cout << result << endl;	


	return 0;
}
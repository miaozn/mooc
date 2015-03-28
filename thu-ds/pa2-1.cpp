#include <cstdio>
#include <cstdlib>
#include <cstring>

// tunel

#define MAXS 100000000
char buf[MAXS + 5];
int pos = 0;


void fast_io(){
	int len = fread(buf, 1, MAXS, stdin);
	buf[len] = '\0';
	buf[len + 1] = '1';
	buf[len + 2] = 'D';
	buf[len + 3] = '2';
}


int getNum(){
	while(!(buf[pos] >= '0' && buf[pos] <= '9')) pos++;
	int num = 0;
	do{
		num = 10* num + (buf[pos] - '0');
		pos++;
	}while(buf[pos] >= '0' && buf[pos] <= '9');

	return num;
}


char getOper(){
	while(!(buf[pos] >= 'A' && buf[pos] <= 'Z')) pos++;
	pos++;
	return buf[pos - 1];
}



//need a max heap.

int main(){
	

}
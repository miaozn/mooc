#include <cstdio>
#include <cstdlib>



//train

#define MAXS 30000000
char buf[MAXS + 5];
int pos = 0;


void fast_io(){
	int len = fread(buf, 1, MAXS, stdin);
	buf[len] = '\0';
	buf[len + 1] = '1';
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

int n, m;
int B[1600001];
int S[1600001];
int sp = 0;
int A = 1;

char ans[10000000]; //0:push , 1:pop
int ap = 0;

void push(){
	S[sp] = A;
	sp++;
	if(sp > m){
		printf("No\n");
		exit(0);
	}
	A++;
	ans[ap] = 0;
	ap++;	
}

void pop(){
	sp--;
	ans[ap] = 1;
	ap++;
}


int main(){
	
	fast_io();
	n = getNum();
	m = getNum();
	int i, j;

	for(i=0; i<n; i++){
		B[i] = getNum();
	}


	for(i=0; i<n; i++){
		if(B[i] >= A){
			for(j=A; j<=B[i]; j++){
				//printf("1\n");
				push();
			}
			//printf("2\n");
			pop();
		}
		else{
			//printf("%d %d %d\n", sp, S[sp], B[i]);
			if(S[sp - 1] == B[i]){
				//printf("3\n");
				pop();
			}
			else{
				printf("No\n");
				exit(0);
			}
		}
	}


	for(i=0; i<ap; i++){
		if(ans[i]) printf("pop\n");
		else printf("push\n");
	}



	return 0;
}


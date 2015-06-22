/*
Cycle
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>



/*
io helper
*/
const int SZ = 1 << 24;
struct fastio{
	char inbuf[SZ];
	char outbuf[SZ];

	fastio(){
		setvbuf(stdin, inbuf, _IOFBF, SZ);
		setvbuf(stdout, outbuf, _IOFBF, SZ);
	}

}io;


char c1[100002] = {0};
char c2[100002] = {0};
int len1;
int len2;

bool cycle(){
	len1 = strlen(c1);
	len2 = strlen(c2);

	if(len1 != len2) return false;

	int i;
	int j;
	int k;
	int m;
	int n;
	for(i=0;i<len1;i++){

		k = 0;
		for(j=i;j<len1;j++){
			if(c1[j] == c2[k]) k++;
			else break;
		}

		n = 0;
		if(j == len1){
			for(m=k;m<len2;m++){
				if(c2[m] == c1[n]) n++;
				else break;
			}
		}
		
		if( n == len1 - k) return true;

	}


	return false;
}



int main(){
	
	while( scanf("%s %s\n", c1, c2) != EOF ){
		if(cycle()){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}

		memset(c1, 0, len1);
		memset(c2, 0, len2);
	}		


	return 0;
}
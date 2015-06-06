/*
Broadcast
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>



/*
io helper
*/
const int SZ = 1 << 20;
struct fastio{
	char inbuf[SZ];
	char outbuf[SZ];

	fastio(){
		setvbuf(stdin, inbuf, _IOFBF, SZ);
		setvbuf(stdout, outbuf, _IOFBF, SZ);
	}

}io;




int main(){
	int n, m;
	scanf("%d", &n);
	char edge[n+1][n+1];
	memset(edge, 0, (n+1)*(n+1));

	scanf("%d", &m);

	int e1, e2;
	while(m--){
		scanf("%d", &e1);
		scanf("%d", &e2);
		edge[e1][e2] = 1;
		edge[e2][e1] = 1;
	}

	int i,j,k;
	for(i=1;i<n+1;i++){
		for(j=i+1;j<n+1;j++){
			if(edge[i][j]){
				for(k=j+1;k<n+1;k++){
					if(edge[i][k] && edge[j][k]){
						printf("-1\n");
						return 0;
					}
				}
			}
		}
	}

	printf("1\n");

	return 0;
}



/*
Deduplicate
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>


/*
bucket size
*/
#define BKSIZE (98981)


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



typedef struct Node{
	int done;
	char v[41];
	struct Node *next;
}Node;


int prime[41] = {2 , 3  , 5  , 7  , 11 , 13 , 17 , 19 , 23 , 29 , \
				31 , 37 , 41 , 43 , 47 , 53 , 59 , 61 , 67 , 71 , \
				73 , 79 , 83 , 89 ,	97 , 101, 103, 107, 109, 113, \
				127, 131, 137, 139,	149, 151, 157, 163, 167, 173, \
				179};



struct Node* NewNode( char *inp ){
	Node* r = (Node *) malloc(sizeof(Node));
	strcpy(r->v, inp);

	r->done = 0;
	r->next = 0;

	return r;
}



int hashcode( char *inp ){
	int p;
	int i;
	int len = strlen(inp);
	
	int hash = 0;

	for(i=0; i<len; i++){
		p = (int) inp[i];
		hash += p * prime[i]; 
	}

	return hash % BKSIZE;

}


Node* bucket[BKSIZE] = {0};




/*
check if already have inp
return true if yes.
otherwise store it and return false
*/
bool check( char *inp ){
	int pos = hashcode(inp);
	if(bucket[pos] == 0){
		bucket[pos] = NewNode(inp);
		return false;
	}

	Node *nd = bucket[pos];
	bool res;
	while( nd->next != 0 ){
		if( strcmp(nd->v, inp) == 0 ){
			res = (nd->done == 0);
			if(res) nd->done = 1;
			return res;
		}
		nd = nd->next;
	}

	if( strcmp(nd->v, inp) == 0 ){
		res = (nd->done == 0);
		if(res) nd->done = 1;
		return res;
	}
	else{
		nd->next = NewNode(inp);
	}

	return false;
}



int main(){
	
	int n;
	scanf("%d", &n);
	char inp[41];

	while(n--){

		memset(inp, 0, 41);
		scanf("%s", inp);

		if( check(inp) ){
			printf("%s\n", inp);
		}

	}

	return 0;
}


/*
Schedule
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



/*
Heap element
*/
class Node{
public:
	long long nice;
	char task[9];

	Node( long long, char* );	

};

Node::Node( long long n, char *c ){
	nice = n;
	strcpy(task, c);
}


Node* nd[4000001] = {0};
int pos = 0;

/*
compare:
return true if nd1 is better than nd2. o.w., return false
*/
bool cmp( Node* nd1, Node* nd2 ){
	if(nd2 == 0) return true;
	if(nd1 == 0) return false;
	if( nd1->nice < nd2->nice ) return true;
	if( nd1->nice > nd2->nice ) return false;
	return strcmp(nd1->task, nd2->task) < 0; 
}




int heap_sz = 0;

void swap( int &a, int &b ){
	int t = a;
	a = b;
	b = t;
}

/*
heap add
*/
void add( int *hp, int p ){

	heap_sz++;
	hp[heap_sz] = p;

	/*
	adjust to heap property
	*/
	int i = heap_sz;
	while( i > 1 && cmp(nd[ hp[i] ], nd[ hp[i/2] ]) ){

		swap(hp[i], hp[i/2]);
		i = i/2;

	}


}


void heap_show( int *hp ){
	int i;
	printf("heap : ");
	for(i=1;i<=heap_sz;i++){
		printf("%d ", hp[i]);
	}

	printf("\n");
}

/*
heap remove
*/
void del( int *hp ){
	
	heap_show(hp);

	int del_p = hp[1];
	swap(hp[1], hp[heap_sz]);
	heap_sz--;
	
	/*
	adjust to heap property
	*/
	int i = 1;
	int lc, rc;
	while(i < heap_sz){

		lc = i*2;
		rc = lc + 1;
		if( nd[hp[lc]] == 0 && nd[hp[rc]] == 0) break;

		if( nd[hp[rc]] == 0){

			if(cmp( nd[hp[lc]], nd[hp[i]] )){
				swap(hp[lc], hp[i]);
			}

			break;
		}


		if(cmp( nd[hp[lc]], nd[hp[rc]] )){
			if(cmp( nd[hp[lc]], nd[hp[i]] )){
				swap(hp[lc], hp[i]);
				i = lc;
			}
			else break;
		}
		else{
			if(cmp( nd[hp[rc]], nd[hp[i]] )){
				swap(hp[rc], hp[i]);
				i = rc;
			}
			else break;

		}

	}



	/*
	add back
	*/
	nd[del_p]->nice *= 2;
	add(hp, del_p);
	/*
	if(nd[del_p]->nice < 4294967296){
		add(hp, del_p);
	}
	*/

	printf("%s\n", nd[del_p]->task);	
}



int main(){
	

	int n, m;
	scanf("%d %d", &n, &m);
	if(n < 1 || m < 1) return 0;

	int nc;
	char tk[9];
	int heap[n + 1];

	while(n--){

		memset(tk, 0, 9);

		scanf("%d %s", &nc, tk);
		nd[pos] = new Node(nc, tk);

		add(heap, pos);

		pos++;
	}



	/*
	output
	*/
	while(m-- && heap_sz > 0){

		del(heap);

	}





	return 0;
}
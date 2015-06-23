/*
Schedule
un-oop
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





/*
Heap element
*/
class Node{
public:
	char task[9];
	unsigned int nice;

	Node( unsigned int, char* );	

};

Node::Node( unsigned int n, char *c ){
	nice = n;
	strcpy(task, c);
}



Node* elm[4000002] = {0};
int size = 0;



void put( Node* nd ){
	size++;
	elm[size] = nd;
}


/*
compare two nodes
*/
bool cmp( Node* nd1, Node* nd2 ){
	if( nd1->nice < nd2->nice ) return true;
	if( nd1->nice > nd2->nice ) return false;

	return strcmp( nd1->task, nd2->task );
}




/*
floyd heap construction
*/
void build(){
	int i;

	for(i=size/2; i>=1; i--){
		Node* y = elm[i];
		int ci = i + i;

		while( ci <= size ){
			if( ci < size && cmp( elm[ci+1], elm[ci] ) ){
				ci++;
			}
			if( cmp(y, elm[ci]) ) break;

			elm[ci/2] = elm[ci];

			ci = ci + ci;
			elm[ci/2] = y;
		}
	}

}



void insert( Node* nd ){
	
	int i = ++size;

	while( i != 1 && cmp(nd, elm[i >> 1]) ){
		elm[i] = elm[i >> 1];
		i = i >> 1;
	}

	elm[i] = nd;
}


void delMin(){
	Node* x = elm[1];

	Node* y = elm[size--];

	int i =1, ci = 2;
	while( ci <= size ){

		if(ci < size && cmp( elm[ci+1], elm[ci] )) ci++;

		if(cmp( y, elm[ci])) break;

		elm[i] = elm[ci];
		i = ci;
		ci = ci << 1;
	}

	elm[i] = y;



	/*
	add back x?
	*/
	unsigned int t = x->nice;
	x->nice = t + t;
	if( x->nice > t ){
		insert(x);
	}



	printf("%s\n", x->task );	
}


int main(){
	
	int n, m;
	scanf("%d %d", &n, &m);

	if( n < 1 || m < 1 ) return 0;

	unsigned int nc;
	char tk[9];

	while(n--){

		memset(tk, 0, 9);

		scanf("%u %s", &nc, tk);

		put( new Node(nc, tk) );

	}

	build();

	while(m-- && size > 0){
		delMin();
	}


	return 0;
}
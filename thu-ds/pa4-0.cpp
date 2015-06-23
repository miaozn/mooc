/*
Schedule
pass 80%
TLE
need to optimize
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>



/*
io helper
*/
const int SZ = 1 << 25;
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



class Heap{
public:
	Node** elm;
	int size;

	Heap( int );

	bool cmp( Node*, Node* );
	void insert( Node* );
	void delMin();


	/*
	floyd heap construction
	O(n)
	*/
	void put( Node* );
	void build();


};


Heap::Heap( int n ){
	size = 0;
	elm = (Node **) malloc(sizeof(Node *) * (n+2));

}


void Heap::put( Node* nd ){
	size++;
	elm[size] = nd;
}


void Heap::build(){
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


/*
return True if nd1 is better than nd2
*/
bool Heap::cmp( Node* nd1, Node* nd2 ){
	if( nd1->nice < nd2->nice ) return true;
	if( nd1->nice > nd2->nice ) return false;

	return strcmp( nd1->task, nd2->task ) < 0; 
}


void Heap::insert( Node* nd ){
		
	//printf("1\n");

	int i = ++size;

	while( i != 1 && cmp( nd, elm[i >> 1] ) ){
		
		elm[i] = elm[i >> 1];
		i = i >> 1;
	}

	elm[i] = nd;
	//printf("2\n");
}


void Heap::delMin(){
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
	if(n < 1 || m < 1) return 0;

	unsigned int nc;
	char tk[9];

	Heap* hp = new Heap(n);


	while(n--){

		memset(tk, 0, 9);

		scanf("%u %s", &nc, tk);
		hp->put( new Node(nc, tk) );
	}


	hp->build();



	/*
	output
	*/
	while(m-- && hp->size > 0){

		hp->delMin();

	}





	return 0;
}
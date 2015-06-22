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



class Heap{
public:
	Node* elm[4000001];
	int size;

	Heap();

	bool cmp( Node*, Node* );
	void swap( int, int );
	void insert( Node* );
	void delMin();
};


Heap::Heap(){
	size = 0;
	int i;
	for(i=0;i<4000001;i++) elm[i] = 0;
}

/*
return True if nd1 is better than nd2
*/
bool Heap::cmp( Node* nd1, Node* nd2 ){
	if( nd1->nice < nd2->nice ) return true;
	if( nd1->nice > nd2->nice ) return false;

	return strcmp( nd1->task, nd2->task ) < 0; 
}


void Heap::swap( int a, int b ){
	Node* t = elm[a];
	elm[a] = elm[b];
	elm[b] = t;
}


void Heap::insert( Node* nd ){
	size++;
	elm[size] = nd;

	int i = size;
	while( i > 1 && cmp( elm[i], elm[i/2] ) ){
		swap(i, i/2);
		i /= 2;
	}
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
		ci *= 2;
	}

	elm[i] = y;



	/*
	add back x?
	*/
	x->nice *= 2;
	if( x->nice < 4294967296 ){
		insert(x);
	}
	else{
		delete x;
	}

	printf("%s\n", x->task );
}






int main(){
	

	int n, m;
	scanf("%d %d", &n, &m);
	if(n < 1 || m < 1) return 0;

	int nc;
	char tk[9];

	Heap hp = new Heap();


	while(n--){

		memset(tk, 0, 9);

		scanf("%d %s", &nc, tk);
		hp->insert( new Node(nc, tk) );
	}



	/*
	output
	*/
	while(m-- && hp->size > 0){

		hp->delMin();

	}





	return 0;
}
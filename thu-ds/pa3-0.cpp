/*
TSP
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
list node
*/
class ListNode{
public:
	int v;
	ListNode *next;
	ListNode( int );
};

ListNode::ListNode( int num ){
	v = num;
	next = 0;
}




ListNode* nd0[1000001] = {0};
char has_in_edge[1000001] = {0};
int path_v[1000001] = {0};
int max_path = 0;


void list_add( int a, int b ){
	if(nd0[a] == 0){
		nd0[a] = new ListNode(b);
		return;
	}

	ListNode *nx = nd0[a]->next;
	nd0[a]->next = new ListNode(b);
	nd0[a]->next->next = nx;

}


void traverse( int id ){
	if( path_v[id] > max_path ){
		max_path = path_v[id];
	}

	if( nd0[id] == 0 ) return;

	ListNode *nd = nd0[id];

	while( nd != 0 ){
		if( path_v[id] + 1 > path_v[nd->v] ){
			path_v[nd->v] = path_v[id] + 1;

			traverse( nd->v );
		}

		nd = nd->next;
	}


}


int main(){
	
	int n, m;
	scanf("%d%d", &n, &m);


	/*
	edge : a-->b
	*/
	int i, a, b;
	while(m--){
		scanf("%d%d", &a, &b);

		/*
		add edge
		*/
		list_add(a, b);
		has_in_edge[b] = 1;

	}


	for(i=1;i<n+1;i++){
		if(has_in_edge[i] == 0){
			traverse( i );
		}
	}


	printf("%d\n", max_path + 1);

	return 0;
}
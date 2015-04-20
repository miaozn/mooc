#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

/*proper rebuild
  passed 95%
*/
#define MAXS 100000000
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

typedef struct TreeNode{
	int v;
	struct TreeNode *left, *right;
}TreeNode;



TreeNode* build(int h1[], int h2[], int h1_lo, int h1_hi, int h2_lo, int h2_hi){
	TreeNode* P = (TreeNode *) malloc(sizeof(TreeNode));
	P->v = h1[h1_lo];

	if(h1_lo >= h1_hi || h2_lo >= h2_hi){
		P->left = NULL;
		P->right = NULL;
		return P;
	}

	int i, j;
	for(i=h2_hi-1; i>=h2_lo; i--){
		if(h2[i] == h1[h1_lo + 1]){
			break;
		}
	}

	for(j=h1_hi; j>=h1_lo; j--){
		if(h1[j] == h2[h2_hi - 1]){
			break;
		}
	}

	P->left  = build(h1, h2, h1_lo + 1, j - 1, 0, i);
	P->right = build(h1, h2, j, h1_hi, i + 1, h2_hi - 1); 

	return P;
}


void inorder_trav(TreeNode* nd){
	if(nd == NULL) return;
	inorder_trav(nd->left);
	printf("%d ", nd->v);
	inorder_trav(nd->right);
}


int main(){

	fast_io();
	
	int n = getNum();
	int h1[n];
	int i, j;
	for(i=0; i<n; i++){
		h1[i] = getNum();
	}
	int h2[n];
	for(i=0; i<n; i++){
		h2[i] = getNum();
	}


	TreeNode* root = build(h1, h2, 0, n-1, 0, n-1);


	inorder_trav(root);

	return 0;
}
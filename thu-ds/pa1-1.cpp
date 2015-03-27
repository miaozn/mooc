#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>


//zuma

#define LEN 200000000





int size = 0;

typedef struct List{
	struct List *pred, *next;
	char val;
}List, *pList;

pList head = (pList) malloc(sizeof(List));
pList tail = (pList) malloc(sizeof(List));


char ans[LEN + 5] = {0};
int ans_pos = 0;




void init(){
	//read input line
	char a[10005];
	gets(a);
	int i, n = strlen(a);
	
	pList pt = head;
	tail->pred = head;
	tail->next = NULL;
	head->next = tail;
	head->pred = NULL;
	head->val = tail->val = '-';
	
	for(i=0; i<n; i++){
		pList pNew = (pList) malloc(sizeof(List));
		pNew->val = a[i];
		pNew->pred = pt;
		pNew->next = pt->next;
		pt->next->pred = pNew;
		pt->next = pNew;
		pt = pNew;
		size++;
	}
	
	
}




void put_ans(){
	if(!size){
		ans[ans_pos++] = '-';
		ans[ans_pos++] = '\n';
		return;
	}
	pList nd = head->next;
	while(nd != tail){
		ans[ans_pos++] = nd->val;
		nd = nd->next;
	}

	ans[ans_pos++] = '\n';
}





void del_near(pList nd){
	
	if(nd == NULL || nd == head || nd == tail || !size) return;
	pList pred_nd = nd->pred, next_nd = nd->next;
	int pred_cnt = 0, next_cnt = 0;
	char c = nd->val;
	
	while(pred_nd->val == c){
		pred_cnt++;
		pred_nd = pred_nd->pred;
	}
	
	while(next_nd->val == c){
		next_cnt++;
		next_nd = next_nd->next;
	}
	
	if(pred_cnt + next_cnt > 1){
		size -= (pred_cnt + next_cnt + 1);
		pred_nd->next = next_nd;
		next_nd->pred = pred_nd;
		
		if(pred_nd != head){
			del_near(pred_nd);
		}
		else{
			del_near(next_nd);
		}
		
	}
	
}



void insert(int pos, char c){
	pList nd = head;
	int i = -1;
	while(i++ < pos) nd = nd->next;
	
	pList pNew = (pList) malloc(sizeof(List));
	pNew->val = c;
	pNew->next = nd;
	pNew->pred = nd->pred;
	nd->pred->next = pNew;
	nd->pred = pNew;
	size++;
	
	del_near(pNew);
	

}


int main(){

	init();
	int n, m;
	scanf("%d\n", &n);
	char c;
	while(n--){
		scanf("%d ", &m);
		do{
			c = getchar();
		}while(!(c >= 'A' && c <= 'Z'));
		insert(m, c);
		put_ans();
	}
	
	printf("%s", ans);

	return 0;
}




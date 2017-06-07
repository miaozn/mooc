#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>

/*tunel*/
#define MAXS 20000000
char buf[MAXS + 5];
int pos = 0;

void fast_io(){
	int len = fread(buf, 1, MAXS, stdin);
	buf[len] = '\0';
	buf[len + 1] = '1';
	buf[len + 2] = 'D';
	buf[len + 3] = '2';
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


char getOper(){
	while(!(buf[pos] >= 'A' && buf[pos] <= 'Z')) pos++;
	pos++;
	return buf[pos - 1];
}


typedef struct qList{
	int data;
	struct qList *pred, *next;	
}qList;

typedef struct pList{
	int data;
	int cnt;
	struct pList *pred, *next;
}pList;


int main(){
	
	fast_io();
	int n, x;
	char op;
	n = getNum();

	/*init*/
	qList *Q_head = (qList *)malloc(sizeof(qList));
	qList *Q_tail = (qList *)malloc(sizeof(qList));
	Q_head->data = -1;
	Q_tail->data = -2;
	Q_head->pred = NULL;
	Q_head->next = Q_tail;
	Q_tail->next = NULL;
	Q_tail->pred = Q_head;

	pList *P_head = (pList *)malloc(sizeof(pList));
	pList *P_tail = (pList *)malloc(sizeof(pList));
	P_head->data = INT_MAX;
	P_tail->data = -2;
	P_head->pred = NULL;
	P_head->next = P_tail;
	P_tail->next = NULL;
	P_tail->pred = P_head;


	qList *qt, *qt2;
	pList *pt, *pt2;

	while(n--){
		op = getOper();
		switch(op){
		case 'E':{
			x = getNum();
			/*enqueue q*/
			qt = (qList *)malloc(sizeof(qList));
			qt->data = x;
			qt->next = Q_tail;
			qt->pred = Q_tail->pred;
			Q_tail->pred->next = qt;
			Q_tail->pred = qt;

			/*insert new p*/
			pt = (pList *)malloc(sizeof(pList));
			pt->data = x;
			pt->cnt = 1;
			pt->next = P_tail;
			pt->pred = P_tail->pred;
			P_tail->pred->next = pt;
			P_tail->pred = pt;
	
			/*updata p list*/
			pt2 = pt->pred;
			while(pt2->data < pt->data){
				pt2->data = pt->data;
				pt2->cnt += pt->cnt;
				pt2->next = pt->next;
				pt->next->pred = pt2;
				delete pt;
				pt = pt2;
				pt2 = pt2->pred;
			}

			break;
		}
		case 'D':{
			/*update q list*/
			x = Q_head->next->data;
			printf("%d\n", x);
			Q_head->next = Q_head->next->next;
			Q_head->next->pred = Q_head;

			/*update p list*/
			pt = P_head->next;
			pt->cnt--;
			if(pt->cnt == 0){
				P_head->next = pt->next;
				pt->next->pred = P_head;
				delete pt;
			}

			break;
		}
		case 'M':{
			
			/*query p list*/
			x = P_head->next->data;
			printf("%d\n", x);

			break;
		}
		default: break;
		}
	}


	return 0;

}
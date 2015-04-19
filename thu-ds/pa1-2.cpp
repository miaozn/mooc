#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

//light house, pass 95%

#define L 10000005
#define MAXS 100000000


int x[L] = {0}, y[L] = {0};
char buf[MAXS + 5];
int pos = 0;
long long ans = 0;


void fast_io(){
	int len = fread(buf, 1, MAXS, stdin);
	buf[len] = '\0';
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


void swap(int &a, int &b){
	int t = a;
	a = b;
	b = t;
}

void quicksort(int lo, int hi){

	int i = lo, j = hi;
	int pivot = x[(lo + hi) >> 1];

	while(i <= j){
		while(x[i] < pivot) i++;
		while(x[j] > pivot) j--;

		if(i <= j){
			swap(x[i], x[j]);
			swap(y[i], y[j]);
			i++;
			j--;
		}

	}

	if(lo < j) quicksort(lo, j);
	if(i < hi) quicksort(i, hi);

}



void merge(int lo, int hi){
	int mid = (lo + hi) >> 1;

	int a[hi - lo + 1];
	int i = lo, j = mid + 1, k = 0;

	while( k < hi - lo + 1){
		if(y[i] < y[j]){
			a[k] = y[i];
			i++;
			ans += (hi - j + 1);
		}
		else{
			a[k] = y[j];
			j++;
		}
		k++;
		if(i > mid || j > hi) break;
	}

	while(i < mid + 1){
		a[k] = y[i];
		i++;
		k++;
	}
	while(j < hi + 1){
		a[k] = y[j];
		j++;
		k++;
	}

	for(i = lo; i < hi+1; i++){
		y[i] = a[i - lo];
	}

}


void mergesort(int lo, int hi){
	if(lo >= hi) return;
	int mid = (lo + hi) >> 1;

	mergesort(lo, mid);
	mergesort(mid + 1, hi);

	merge(lo, hi);
}





int main(){
	
	fast_io();

	int n = getNum();

	for(int i=0; i<n; i++){
		x[i] = getNum();
		y[i] = getNum();
	}

	quicksort(0, n-1);

	mergesort(0, n-1);

	//printf("%ld\n", ans);

	std::cout << ans << std::endl;

}
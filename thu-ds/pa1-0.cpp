#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

//range query


#define L 500005

int a[L];


//merge sort
void mergesort(int h[], int start, int end){
	if(start == end) return;
	int mid = start + (end - start)/2;
	mergesort(h, start, mid);
	mergesort(h, mid + 1, end);

	int a[end - start +1];
	int i_a = 0;
	int i_h1 = start;
	int i_h2 = mid + 1;

	while (i_a < end - start + 1){

		if(h[i_h1] < h[i_h2]){

			a[i_a] = h[i_h1];
			i_h1++;

		}
		else{

			a[i_a] = h[i_h2];
			i_h2++;

		}

		i_a++;
		if (i_h1 > mid || i_h2 > end){
			break;
		}

	}

	while (i_h1 < mid + 1){
		a[i_a] = h[i_h1];
		i_h1++;
		i_a++;
	}

	while(i_h2 < end + 1){
		a[i_a] = h[i_h2];
		i_h2++;
		i_a++;
	}

	for(int i = start; i < end + 1; i++){
		h[i] = a[i - start];
	}

}



int find(int start, int end, int goal){
	int mid;
	while( start < end + 1){
		mid = start + ((end - start) >> 1);
		if(a[mid] >= goal){
			end = mid - 1;
		}
		else{
			start = mid + 1;
		}
	}

	return start;
}


int main(){
	
	int n, m, i;
	scanf("%d %d\n", &n, &m);

	for(i = 0; i < n; i++){
		scanf("%d", &a[i]);
	}


	mergesort(a, 0, n-1);


	for(i = 0; i < m; i++){

		int l, r, ans, lf, rt;
		scanf("%d %d", &l, &r);


		rt = find(0, n - 1, r);
		lf = find(0, n - 1, l);

		ans = rt - lf;
		if(a[rt] == r) ans++;


		printf("%d\n", ans);

	}



	return 0;
}
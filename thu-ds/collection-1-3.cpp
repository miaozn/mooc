#include <iostream>

using namespace std;



int main(){
	
	string inp;
	getline(cin, inp);
	int cnt[26] = {0};

	char c;
	for(size_t i=0;i<inp.size();i++){
		c = inp[i];
		if(c >= 'a' && c <= 'z'){
			cnt[c - 'a']++;
			continue;
		}
		if(c >= 'A' && c <= 'Z'){
			cnt[c - 'A']++;
		}
	}

	for(int i=0;i<26;i++){
		if(cnt[i]){
			cout << (char)('A'+ i) << ": " << cnt[i] << endl;
		}
	}

	return 0;
}
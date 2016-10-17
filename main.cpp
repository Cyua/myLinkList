#include "myLinkList.h"
#include <iostream>
using namespace std;

int main(void){
	linkList<int> a;
	int b;
	a.insert(0, 1);
	a.insert(1, 3);
	a.insert(1, 4);
	a.pushTail(2);
	a.pushTail(5);
	a.pushTail(16);
	a.pushTail(7);
	a.sort(0);
	for(int i = 0; i < a.size(); i ++){
		a.getValue(i, &b);
		cout<<b<<endl;
	}
	return 0;
}

#include "myLinkList.h"
#include <iostream>
using namespace std;

int main(void){
	linkList<int> a;
	a.pushHead(4);
	cout<<a.size()<<endl;
	a.pushHead(3);
	a.clear();
	cout<<a.size()<<endl;
	return 0;
}

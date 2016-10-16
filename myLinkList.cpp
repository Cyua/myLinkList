#include "myLinkList.h"
#include <iostream>

linkList::linkList(){
    count = 0;
    elementSize = 0;
    head = NULL;
    tail = NULL;
}


bool linkList::init(int elementSize){
    cout<<elementSize<<endl;
    return true;
}
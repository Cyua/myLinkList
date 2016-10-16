#ifndef _MY_LINK_LIST_
#define _MY_LINK_LIST_

typedef struct myListNode{
	void* data;
	struct myListNode* next;
	struct myListNode* prev;
}LIST_NODE;

class linkList{
public:
	linkList();
	bool init(int elementSize);
	

private:
	int count;
	int elementSize;
	struct LIST_NODE* head;
	struct LIST_NODE* tail;
}

#endif
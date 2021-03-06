#ifndef _MY_LINK_LIST_
#define _MY_LINK_LIST_

#include <iostream>
#include <assert.h>

template <typename T>
struct listNode{
	T data;
	struct listNode* next;
	struct listNode* prev;
	listNode(){
		data = 0;
		next = nullptr;
		prev = nullptr;
	}
};

template <typename T>
class linkList{
public:
	linkList();
	~linkList();
	bool pushHead(T element);
	bool pushTail(T element);
	bool popHead();
	bool popTail();
	int size();
	bool clear();
	bool insert(const int position, T element);
	bool remove(const int position);
	bool isEmpty();
	int findElement(const T element);
	bool getValue(const int position, T* pdata);
	bool sort(int start=0, int end=-1, bool (*)(const T&, const T&)=less);

private:
	int count;
	static bool less(const T& a, const T& b){return a < b;}
	struct listNode<T>* mergeSort(struct listNode<T>* head, bool (* cmp)(const T& a, const T& b));
	struct listNode<T>* merge(struct listNode<T>* head1, struct listNode<T>* head2, bool (* cmp)(const T& a, const T& b));
	struct listNode<T>* head;
	struct listNode<T>* tail;
};

template <typename T>
linkList<T>::linkList(){
	count = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
linkList<T>::~linkList(){
	clear();
}

template <typename T>
bool linkList<T>::pushHead(T element){
	struct listNode<T>* tmpNode;
	try{
		tmpNode = new listNode<T>;
	} catch(const std::bad_alloc& e) {
		return false;
	}
	tmpNode->data = element;
	if (head == nullptr){
		head = tmpNode;
		tail = tmpNode;
	} else {
		tmpNode->next = head;
		head->prev = tmpNode;
		head = tmpNode;	
	}
	count++;
	return true;
}

template <typename T>
bool linkList<T>::pushTail(T element){
	struct listNode<T>* tmpNode;
	try{
		tmpNode = new listNode<T>;
	} catch(const std::bad_alloc& e) {
		return false;
	}
	tmpNode->data = element;
	if (tail == nullptr){
		head = tmpNode;
		tail = tmpNode;
	} else {
		tmpNode->prev = tail;
		tail->next = tmpNode;
		tail = tmpNode;
	}
	count++;
	return true;
}

template <typename T>
bool linkList<T>::popHead(){
	if (head == nullptr)
		return false;
	if (head == tail){
		delete head;
		tail = nullptr;
		head = nullptr;
		count--;
		return true;
	} 
	struct listNode<T>* tmp = head->next;	
	delete head;
	head = tmp;
	head->prev = nullptr;
	count--;	
	return true;
}

template <typename T>
bool linkList<T>::popTail(){
	if (tail == nullptr)
		return false;
	if (head == tail){
		delete tail;
		tail = nullptr;
		head = nullptr;
		count--;
		return true;
	}
	struct listNode<T>* tmp = tail->prev;
	delete tail;
	tail = tmp;
	tail->next = nullptr;
	count--;
	return true;
}

template <typename T>
int linkList<T>::size(){
	assert(count >= 0);
	return count;
}

template <typename T>
bool linkList<T>::clear(){
	while(popTail()){
		continue;
	}	
	if(head == nullptr && tail == nullptr){
		count = 0;
		return true;
	} else {
		return false;
	}
}

template <typename T>
bool linkList<T>::insert(const int position, T element){
	if(position < 0 || position > size()){
		std::cerr<<"[ERROR] position "<<position<<" is out of limit"<<std::endl;
		return false;	
	}
	if(position == 0){
		return pushHead(element);
	}
	if(position == size()){
		return pushTail(element);
	} 
	int cnt = 1;
	struct listNode<T>* tmp = head; 
	while(cnt != position){
		tmp = tmp->next;
		cnt++;
	}	
	struct listNode<T>* newNode = new struct listNode<T>;
	newNode->data = element;
	newNode->next = tmp->next;
	newNode->prev = tmp;
	newNode->next->prev = newNode;
	tmp->next = newNode;
	count++;
	return true;
}

template <typename T>
bool linkList<T>::remove(const int position){
	if(position < 0 || position >= size()){
		std::cerr<<"[ERROR] position "<<position<<" is out of limit"<<std::endl;
		return false;	
	}	
	if(position == 0){
		return popHead();
	} 
	if (position == size()-1){
		return popTail();
	}
	int cnt = 0;
	struct listNode<T>* tmp = head;
	while(cnt != position){
		tmp = tmp->next;
		cnt++;
	}
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	delete tmp;
	tmp = nullptr;
	count--;
	return true;
}

template <typename T>
bool linkList<T>::isEmpty(){
	return size() == 0;
}

template <typename T>
int linkList<T>::findElement(const T element){
	struct listNode<T>* tmp = head;
	int cnt = 0;
	while(tmp != nullptr){
		if(tmp->data == element)
			return cnt;
		tmp = tmp->next;
		cnt++;
	}
	return -1;
}

template <typename T>
bool linkList<T>::getValue(const int position, T* pdata){
	using namespace std;
	if(position < 0 || position >= size()){
		std::cerr<<"[ERROR] position "<<position<<" is out of limit"<<std::endl;
		return false;
	}
	struct listNode<T>* tmp;
	if(position < size()/2){
		tmp = head;
		int cnt = 0;
		while(cnt != position){
			tmp = tmp->next;
			cnt++;
		}	
		*pdata = tmp->data;
		return true;
	} else {
		tmp = tail;
		int cnt = size() - 1;
		while(cnt != position){
			tmp = tmp->prev;
			cnt--;
		}
		*pdata = tmp->data;
		return true;
	}
}

template <typename T>
bool linkList<T>::sort(int start, int end, bool (* cmp)(const T& a, const T& b)){
	if(start < 0 || start >= size()){
		std::cerr<<"[ERROR]start position "<<start<<" is out of limit"<<std::endl;
		return false;
	}
	if(end >= size()){
		std::cerr<<"[ERROR]end position "<<end<<" is out of limit"<<std::endl;
		return false;
	}
	if(end < 0)
		end = size() - 1;
	if(start > end){
		std::cerr<<"[ERROR]start position is larger than end position"<<std::endl;
		return false;
	}
	if(start == end)
		return true;

	struct listNode<T>* pstart = head;
	int cnt = 0;
	while(cnt != start){
		pstart = pstart->next;
		cnt++;
	}
	struct listNode<T>* pend = pstart;
	while(cnt != end){
		pend = pend->next;
		cnt++;
	}
	struct listNode<T>* pfront = pstart->prev;
	struct listNode<T>* pafter = pend->next;
	pend->next = nullptr;
	//apply merge sort
	pstart = mergeSort(pstart, cmp);
	if(pfront != nullptr){
		pfront->next = pstart;
		pstart->prev = pfront;
	} else {
		pstart->prev = nullptr;
		head = pstart;	
	}
	pend = pstart->next;
	while(pend != nullptr){
		pend->prev = pstart;
		pstart = pend;
		pend = pend->next;		
	}
	if(pafter != nullptr){
		pstart->next = pafter;
		pafter->prev = pstart;
	} else {
		tail = pstart;
	}
	return true;
}

template <typename T>
struct listNode<T>* linkList<T>::mergeSort(struct listNode<T>* head, bool (* cmp)(const T& a, const T& b)){
	if(head == nullptr || head->next == nullptr) 
		return head;
	struct listNode<T>* slow = head;
	struct listNode<T>* fast = head->next;
	while(fast != nullptr && fast->next != nullptr){
		slow = slow->next;
		fast = fast->next->next;
	}
	fast = slow->next;
	slow->next = nullptr;
	struct listNode<T>* head1 = mergeSort(head, cmp);
	struct listNode<T>* head2 = mergeSort(fast, cmp);	
	return merge(head1, head2, cmp);
}

template <typename T>
struct listNode<T>* linkList<T>::merge(struct listNode<T>* head1, struct listNode<T>* head2, bool (* cmp)(const T& a, const T& b)){
	struct listNode<T>* ret = nullptr;
	if (head1 == nullptr)
		return head2;
	else if(head2 == nullptr)
		return head1;
	if(cmp(head1->data, head2->data)){
		ret = head1;
		ret->next = merge(head1->next, head2, cmp);
	} else {
		ret = head2;
		ret->next = merge(head1, head2->next, cmp);
	}
	return ret;
}

#endif

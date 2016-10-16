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
	//TODO

private:
	int count;
	struct listNode<T>* head;
	struct listNode<T>* tail;
};

/************ definition begin ************/

template <typename T>
linkList<T>::linkList(){
	count = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename T>
linkList<T>::~linkList(){

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

#endif

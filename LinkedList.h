#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <cstddef>

// contains an implementation of a linked list
namespace custom_container{

	// node stucture for the linked list 
	template<typename T>
	struct node{
		T value;
		node<T> *next;
		node<T> *previous;
	};

	// forward declaration
	template<typename T>
	class LinkedList;

	// iterator for the LinkedList class
	template<typename T>
	class ListIterator{
		public:
			ListIterator();
			ListIterator(LinkedList<T>& l);
			bool is_null();
			void set_null();
			void operator++(int);
			void operator--(int);
			T& operator*();
		private:
			node<T> *my_node;
	};

	// templated circular double linked list class
	template<typename T>
	class LinkedList{
		friend class ListIterator<T>;
		public:
			LinkedList();
			LinkedList(LinkedList& other);
			~LinkedList();
			void push_front(T val);
			void push_back(T val);
			void pop_front();
			void pop_back();
			void clear();
			ListIterator<T> begin();
			ListIterator<T> end();
			T get_front();
			T get_back();
			int size();
			void print_list();
			unsigned int get_bytes(); 
			T& operator[](int index);
			LinkedList& operator=(LinkedList& l);
		private:
			node<T> *back;
			node<T> *front;
			int length;
	};

}

/**************************************************************************************************/

// construct an empty circular doubly linked list
// O(1)
template<typename T>
custom_container::LinkedList<T>::LinkedList(){
	length = 0;
	front = NULL;
	back = NULL;
}

// copy constructor
// O(n)
template<typename T>
custom_container::LinkedList<T>::LinkedList(custom_container::LinkedList<T>& other){
	length = 0;
	node<T> *ptr = other.front;
	for (int i = 0; i < other.size(); i++){
		this->push_back(ptr->value);
		ptr = ptr->next;
	}
}

// free all memory allocated by the list
// O(n)
template<typename T>
custom_container::LinkedList<T>::~LinkedList(){
	//std::cout << "Deleting list..." << std::endl;
	this->clear();
}

// push an element to the front of the list
// O(1)
template<typename T>
void custom_container::LinkedList<T>::push_front(T val){
	if (length == 0){
		front = new node<T>;
		back = front;
		front->next = front;
		front->previous = back;
		front->value = val;
	} else{
		node<T> *new_front = new node<T>;

		front->previous = new_front;
		back->next = new_front;

		new_front->next = front;
		new_front->previous = back;
		new_front->value = val;

		front = new_front;
	}
	length++;
}

// push an element to the back of the list
// O(1)
template<typename T>
void custom_container::LinkedList<T>::push_back(T val){
	if (length == 0){
		back = new node<T>;
		front = back;
		back->next = back;
		back->previous = back;
		back->value = val;
	} else{
		node<T> *new_back = new node<T>;

		front->previous = new_back;
		back->next = new_back;

		new_back->next = front;
		new_back->previous = back;
		new_back->value = val;

		back = new_back;
	}
	length++;
}

// delete the element at the front of the list
// O(1)
template<typename T>
void custom_container::LinkedList<T>::pop_front(){
	if (length == 1){
		delete front;
		front = NULL;
		back = NULL;
		length--;
	} else if (length > 0){
		node<T> *new_front = front->next;
		new_front->previous = back;
		back->next = new_front;
		delete front;
		front = new_front;
		length--;
	}
}

// delete the element at the back of the list
// O(1)
template<typename T>
void custom_container::LinkedList<T>::pop_back(){
	if (length == 1){
		delete front;
		front = NULL;
		back = NULL;
		length--;
	} else if (length > 0){
		node<T> *new_back = back->previous;
		new_back->next = front;
		front->previous = new_back;
		delete back;
		back = new_back;
		length--;
	}
}

// clear the contents of the list by deleting the allocated elements
// O(n)
template<typename T>
void custom_container::LinkedList<T>::clear(){
	int count = 0;
	while (length > 0){
		node<T>* next_back = back->previous;
		count++;
		//std::cout << "Freeing memory address: " << back << "\tdeletion count: " << count << std::endl;
		delete back;
		back = next_back;
		length--;
	}
	front = NULL;
	back = NULL;
}

// return an iterator that contains the pointer to the first node
// O(1)
template<typename T>
custom_container::ListIterator<T> custom_container::LinkedList<T>::begin(){
	custom_container::ListIterator<T> it(*this);
	return it;
}

// return an iterator that contains the pointer to the last node
// O(1)
template<typename T>
custom_container::ListIterator<T> custom_container::LinkedList<T>::end(){
	custom_container::ListIterator<T> it(*this);
	it--;
	return it;
	
}

// get the element at the front of the list
// O(1)
template<typename T>
T custom_container::LinkedList<T>::get_front(){
	return front->value;
}

// get the lement at the back of the list
// O(1)
template<typename T>
T custom_container::LinkedList<T>::get_back(){
	return back->value;
}

// print out the contents of the list
// O(n)
template<typename T>
void custom_container::LinkedList<T>::print_list(){
	std::cout << "LinkedList contents: " << std::endl;
	node<T> *ptr = front;
	for (int i = 0; i < length; i++){
		std::cout << ptr->value << " ";
		ptr = ptr->next;
	}
	std::cout << std::endl;
}

// get the number of bytes allocated by the list
// O(1)
template<typename T>
unsigned int custom_container::LinkedList<T>::get_bytes(){
	unsigned int bytes = length * sizeof(node<T>);
	std::cout << "Size of the list: " << bytes << " bytes" << std::endl;
	return bytes;
}

// access an element in the list
// O(n)
template<typename T>
T& custom_container::LinkedList<T>::operator[](int index){
	node<T> *ptr = front;
	for (int i = 0; i < index; i++){
		ptr = ptr->next;
	}
	return ptr->value;
}

// get the number of elements in the list
// O(1)
template<typename T>
int custom_container::LinkedList<T>::size(){
	return length;
}

// copy the contents of l into this list
// O(n)
template<typename T>
custom_container::LinkedList<T>& custom_container::LinkedList<T>::operator=(custom_container::LinkedList<T>& l){
	this->clear();
	node<T> *ptr = l.front;
	for (int i = 0; i < l.size(); i++){
		this->push_back(ptr->value);
		ptr = ptr->next;
	}
	return *this;
}

/**************************************************************************************************/

// Default constructor
// O(1)
template<typename T>
custom_container::ListIterator<T>::ListIterator(){
	my_node = NULL;
}

// Constructor to set the pointer to the argument's front pointer 
// O(1)
template<typename T>
custom_container::ListIterator<T>::ListIterator(custom_container::LinkedList<T>& l){
	my_node = l.front;
}

// Function to check if the pointer that the iterator contains is null
// O(1)
template<typename T>
bool custom_container::ListIterator<T>::is_null(){
	if (my_node == NULL)
		return true;
	else
		return false;
}

// Set the iterator's pointer to null 
// O(1)
template<typename T>
void custom_container::ListIterator<T>::set_null(){
	my_node = NULL;
}

// The pointer becomes the pointer to the next node
// O(1)
template<typename T>
void custom_container::ListIterator<T>::operator++(int){
		my_node = my_node->next;
}

// The pointer becomes the pointer to the previous node
// O(1)
template<typename T>
void custom_container::ListIterator<T>::operator--(int){
		my_node = my_node->previous;
}

// returns a reference of the value stored in node pointed to by the iterator
// O(1)
template<typename T>
T& custom_container::ListIterator<T>::operator*(){
	return my_node->value;
}


#endif

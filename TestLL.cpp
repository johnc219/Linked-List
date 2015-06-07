#include "LinkedList.h"
#include <cstdlib>
#include <ctime>
#define	TYPE int
#define UPPER 100
#define LENGTH 10

int main(){

	srand(time(NULL));
	custom_container::LinkedList<TYPE> list_0;
	for (int i = 0; i < LENGTH; i++){
		//TYPE num = static_cast<TYPE>( rand() / (RAND_MAX / static_cast<TYPE>(UPPER)) );
		list_0.push_back(static_cast<TYPE>(i));
	}
	list_0.print_list();

	custom_container::ListIterator<TYPE> it_0 = list_0.begin(); 
	for (int i = 0; i < list_0.size(); i++){
		(*it_0)++;
		it_0++;
	}
	list_0.print_list();

	for (int i = 0; i < LENGTH; i++){
		list_0.push_front(-i);
	}
	list_0.print_list();

	list_0.pop_back();
	list_0.pop_front();

	list_0.print_list();

	custom_container::LinkedList<TYPE> list_1(list_0);
	list_0.clear();
	list_0.print_list();
	list_1.print_list();

	custom_container::LinkedList<TYPE> list_2;
	list_2 = list_1;
	list_2[list_2.size()-1] = 27;
	list_2.print_list();

	custom_container::ListIterator<TYPE> it_1(list_2);
	for (int i = 0; i < list_2.size()/2; i++){
		it_1--;
		*it_1 = 0;
	}
	it_1.set_null();
	list_2.print_list();

	list_2.get_bytes();
	list_0.get_bytes();
	std::cout << list_2.get_front() << std::endl;
	std::cout << list_2.get_back() << std::endl;

	return 0;
}
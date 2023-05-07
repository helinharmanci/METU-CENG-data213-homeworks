#include <iostream>

#include "LinkedList.h"

int main() {

	// You can test your implementations here
	LinkedList<int> *mylist= new LinkedList<int>();
	//mylist->append(5);
	mylist->append(6);
	mylist->append(7);
	mylist->append(8);
	mylist->append(9);
	mylist->moveToIndex(2,0);
	std::cout<<mylist->getFirstNode()->data<<std::endl;
	std::cout<<mylist->getFirstNode()->next->data<<std::endl;
	std::cout<<mylist->getFirstNode()->next-> next->data<<std::endl;
	std::cout<<mylist->getFirstNode()->next->next->next->data<<std::endl;
	//mylist->print();
	return 0;
}

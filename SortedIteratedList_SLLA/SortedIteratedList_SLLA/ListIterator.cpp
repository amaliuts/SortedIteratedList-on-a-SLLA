#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
	this->currentElem = list.head;
}
//Theta(1)

void ListIterator::first(){
	this->currentElem = list.head;
}
//Theta(1)

void ListIterator::next(){
	if (!valid())
		throw exception();
	int prev = this->currentElem;
	this->currentElem = list.next[prev];
}
//Theta(1)

bool ListIterator::valid() const{
	return (this->currentElem != -1);
}
//Theta(1)

TComp ListIterator::getCurrent() const{
	if (!valid())
		throw exception();
	TComp e = list.elems[this->currentElem];
	return e;
}
//Theta(1)



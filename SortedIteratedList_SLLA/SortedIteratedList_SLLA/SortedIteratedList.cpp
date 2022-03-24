#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	this->capacity = 20;
	this->rel = r;
	this->elems = new TComp[this->capacity];
	this->next = new TComp[this->capacity];
	this->head = -1;		

	for (int i = 1; i < this->capacity - 1; i++)
		this->next[i] = i++;						//fixing the array of 'next positions' with default values
	this->next[this->capacity] = -1;				//the next position of the last element = -1 => end of the array
	this->firstEmpty = 1;					
}
//Theta(capacity)

int SortedIteratedList::size() const {
	int cnt = 0, currentpos = this->head;
	while (currentpos != -1) {
		cnt++;
		currentpos = this->next[currentpos];
	}
	return cnt;
}
//Best case: Theta(1), Worst case: Theta(capacity) => Total Complexity: O(capacity)

bool SortedIteratedList::isEmpty() const {
	return (this->head == -1);
}
//Theta(1)

ListIterator SortedIteratedList::first() const {
	ListIterator it(*this);
	it.first();
	return it;
}
//Theta(1)

TComp SortedIteratedList::getElement(ListIterator poz) const {
	if (!poz.valid())
		throw exception();
	TComp e = this->elems[poz.currentElem];
	return e;
}
//Theta(1)

TComp SortedIteratedList::remove(ListIterator& poz) {
	if (!poz.valid())
		throw exception();
	int deletedElem = poz.getCurrent();
	int pos, currentpos = this->head;
	while (currentpos != -1 && this->elems[currentpos] != poz.getCurrent()) {
		pos = currentpos;
		currentpos = this->next[currentpos];
	}
	if (currentpos != -1) {
		if (currentpos == this->head)		//the soon-to-be removed element is the first one
			this->head = this->next[this->head];
		else
			this->next[pos] = this->next[currentpos];
	}
	return deletedElem;
}
//Best case: Theta(1), Worst case: Theta(size()) => Total Complexity: O(size())

ListIterator SortedIteratedList::search(TComp e) const{
	int len = size();
	ListIterator it(*this);
	while (it.valid()) {
		if (it.getCurrent() == e)
			break;
	}
	return it;
}
//Best case: Theta(1), Worst Case: Theta(len) => Total Complexity: O(len)

void SortedIteratedList::add(TComp e) {
	if (this->head == -1) {						//checks if the list is empty
		this->head = this->firstEmpty;
		this->firstEmpty++;
		this->elems[this->head] = e;
		this->next[this->head] = -1;
	}
	else {
		int pos = -1, currentpos = this->head;
		while (currentpos != -1 && !rel(e, this->elems[currentpos])) {
			pos = currentpos;
			currentpos = this->next[currentpos];
		}
		int len = size();
		this->next[pos] = len + 1;
		int pos1 = this->firstEmpty;
		this->elems[pos1] = e;
		this->next[pos1] = -1;
		this->firstEmpty = this->next[this->firstEmpty];
	}
}
//Best case: Theta(1), Worst case: Theta(len) => Total Complexity: O(len)


SortedIteratedList::~SortedIteratedList() {

}
//Theta(1)

#include "List.h"
#include <utility>


template <typename Object>
List<Object>::List() { init(); }

template <typename Object>
List<Object>::List(const List<Object>& rhs) : theSize(rhs.theSize) {
	init();
	for (const_iterator itr = rhs.front(); itr != rhs.end(); ++itr)
		push_back(*itr);
}

template <typename Object>
List<Object>& List<Object>::operator=(const List<Object>& rhs) {
	List<Object> copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template <typename Object>
List<Object>::List(List<Object>&& rhs) : head{ rhs.head }, tail{ rhs.tail }, theSize{ rhs.theSize } {
	rhs.head = nullptr;
	rhs.tail = nullptr;
	theSize = 0;
	return *this;
}

template <typename Object>
List<Object>& List<Object>::operator=(List<Object>&& rhs) {
	std::swap(this->head, rhs.head);
	std::swap(this->tail, rhs.tail);
	std::swap(this->theSize, rhs.theSize);
	return *this;
}

template <typename Object>
List<Object>::~List() {
	this->clear();
	delete head;
	delete tail;
}


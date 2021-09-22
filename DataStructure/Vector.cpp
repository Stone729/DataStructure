#include "Vector.h"


template <typename Object>
Vector<Object>::Vector() : theSize{ 0 }, theCapacity{ INITIAL_CAP }, objects{ new Object[theCapacity] } {}

template <typename Object>
Vector<Object>::Vector(int capacity ) : theSize{ 0 }, theCapacity{ capacity }, objects{ new Object[theCapacity] } {}

template <typename Object>
Vector<Object>::Vector(const Vector& rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ new Object[theCapacity] } {
	for (int i = 0; i < theSize; ++i)
		objects[i] = rhs.objects[i];
}

template <typename Object>
Vector<Object>& Vector<Object>::operator=(const Vector<Object>& rhs) {
	Vector copy = rhs;
	std::swap(*this, copy);
	return *this;
}

template <typename Object>
Vector<Object>::Vector(Vector<Object>&& rhs) : theSize{ rhs.theSize }, theCapacity{ rhs.theCapcity }, objects{ rhs.objects } {
	rhs.objects = nullptr;
	rhs.theSize = 0;
	rhs.theCapacity = 0;
}

template <typename Object>
Vector<Object>& Vector<Object>::operator=(Vector<Object>&& rhs) {
	std::swap(this->theSize, rhs.theSize);
	std::swap(this->theCapacity, rhs.theCapacity);
	std::swap(this->objects, rhs.objects);
	return *this;
}

template <typename Object>
Vector<Object>::~Vector() {
	clear();
	delete[] objects;
}

//---------------------------------------------//

// template <typename Object>

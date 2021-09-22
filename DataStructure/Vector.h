#pragma once
#include <utility>

template <typename Object>
class Vector
{
public:
	static const int INITIAL_CAP = 16;
	// -----Constructors-------------------
	Vector();
	explicit Vector(int capacity);
	// -----Big 5--------------------------
	Vector(const Vector& rhs);
	Vector& operator=(const Vector& rhs);
	Vector(Vector&& rhs);
	Vector& operator=(Vector&& rhs);
	~Vector();

	// ******************************************

	// Common Operations for All Containers
	int size() const {
		return theSize;
	}

	int capacity() const {
		return theCapacity;
	}

	bool empty() const {
		return theSize == 0;
	}

	Object& operator[](int index) {
		return objects[index];
	}

	const Object& operator[] (int index) const {
		return objects[index];
	}

	void clear() {
		if (theSize != 0)
			pop_back();
	}

	Object& pop_back() {
		return objects[--theSize];
	}

	void push_back(const Object& obj) {
		if (theSize == theCapacity)
			reserve(theCapacity * 2);
		objects[theSize++] = obj;
	}

	void resize(int newSize) {
		if (theCapacity < newSize)
			reserve(newSize * 2);
		theSize = newSize;
	}

	void reserve(int newCapacity) {
		if (theCapacity >= newCapacity)
			return;
		theCapacity = newCapacity;
		Object* newobjects = new Object[newCapacity];
		for (int i = 0; i < theSize; ++i)
			newobjects[i] = std::move(objects[i]);
		std::swap(objects, newobjects);
		delete[] newobjects;
	}

	// iterator def:
	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator& begin() {
		return objects;
	}
	const_iterator& begin() const {
		return begin();
	}
	iterator& end() {
		iterator itr = &objects[size()];
		return itr;
	}
	const_iterator& end() const {
		iterator itr = &objects[size()];
		return itr;
	}


private:
	int theSize;
	int theCapacity;
	Object* objects;

};



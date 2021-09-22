template <typename Object>

class List
{
private:
	// The Node must be a struct or a class with public member!
	struct Node {
		Node* prev;
		Node* next;
		Object objects;
		Node(const Object& obj = Object{}, Node* p = nullptr, Node* n = nullptr) : prev{ p }, next{ n }, objects{ obj } {}
	};
public:
	class const_iterator {
	public:
		const_iterator() : current{ nullptr } {}

		const Object& operator*() const { return retrieve(); }

		const_iterator& operator++() { current = current->next; return *this; }
		const_iterator& operator++(int) { const_iterator temp(current); ++(*this); return temp; }

		bool operator==(const_iterator rhs) const { return current == rhs.current; }
		bool operator!=(const_iterator rhs) const { return !(*this == rhs); }
	private:
		friend class List;
		Node* current;
		Object& retrieve() const { return current->objects; }
		const_iterator(Node* p) : current{ p } {}

	};

	class iterator : public const_iterator {
	public:
		iterator() {}

		Object& operator*() { return const_iterator::retrieve(); }
		const Object& operator*() const { return const_iterator::retrieve(); }

		iterator& operator++() { const_iterator::current = const_iterator::current->next; return *this; }
		iterator& operator++(int) { iterator temp(this->const_iterator::current); ++(*this); return temp; }

	protected:
		friend class List;
		iterator(Node* p) : const_iterator{ p } {}

	};

	// Default Constructor:
	List();
	// Big 5:
	// Copy Constructor:
	List(const List& rhs);
	// Copy Assignment Operator:
	List& operator= (const List& rhs);
	// Move Constructor:
	List(List&& rhs);
	// Move Assignment Operator:
	List& operator= (List&& rhs);
	~List();

	// Some Common Accessor:
	int size() const {
		return theSize;
	}
	bool empty() const { return size() == 0; }

	void clear() {
		while (!empty())
			pop_front();
	}

	iterator begin() { return { head->next }; }
	iterator end() { return { tail }; }
	const_iterator front() const { return { head->next }; }
	const_iterator end() const { return { tail }; }

	iterator insert(iterator pos, const Object& obj) {
		Node* newnode = new Node(obj);
		Node* curr = pos.current;
		newnode->prev = curr->prev;
		newnode->next = curr->prev->next;
		curr->prev->next = newnode;
		curr->prev = newnode;
		++theSize;
		return { newnode };
	}
	//iterator& insert(iterator& pos, const_iterator& from, const_iterator& to);

	void push_back(const Object& obj) { insert(end(), obj); }
	void push_front(const Object& obj) { insert(begin(), obj); }


	iterator erase(iterator pos) {
		Node* curr = pos.current;
		Node* retptr = curr->next;
		curr->next->prev = curr->prev;
		curr->prev->next = curr->next;
		delete curr;
		theSize--;
		return { retptr };
	}

	//iterator& erase(const_iterator& pos0, const_iterator& pos1);

	void pop_back() { erase(end()); }
	void pop_front() { erase(begin()); }
private:
	// Node* current;
	Node* head;
	Node* tail;
	int theSize;
	void init() {
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
		theSize = 0;
	}
};


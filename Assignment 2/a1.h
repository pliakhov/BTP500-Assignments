#ifndef STACK_H
#define STACK_H
#include <iostream>

using namespace std;
template <typename T>
class DList{
	struct Node{
		T m_data;
		Node* m_next;
		Node* m_prev;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr):
			m_data(data),
			m_next(next),
			m_prev(prev)
		{}
	};
	Node* m_head;
	Node* m_tail;
	int m_size;
public:
	class const_iterator{
	protected:
		Node* m_curr;
		friend DList;
	public:
		const_iterator() :
			m_curr(nullptr)
		{}
		const_iterator(Node* _curr) :
			m_curr(_curr)
		{}
		bool operator==(const_iterator rhs){
			return this->m_curr == rhs.m_curr;
		}
		bool operator!=(const_iterator rhs){
			return this->m_curr != rhs.m_curr;
		}
		const_iterator operator++(){
			this->m_curr = this->m_curr->m_next;
			return *this;
		}
		const_iterator operator++(int){
			const_iterator old = *this;
			this->m_curr = this->m_curr->m_next;
			return old;
		}
		const_iterator operator--(){
			this->m_curr = this->m_curr->m_prev;
			return *this;
		}
		const_iterator operator--(int){
			const_iterator old = *this;
			this->m_curr = this->m_curr->m_prev;
			return old;
		}
		const T& operator*() const{
			return this->m_curr->m_data;
		}
	};
	class iterator :public const_iterator{
	public:
		iterator():const_iterator()
		{}
		iterator(Node* iter) : const_iterator(iter)
		{}
		
		iterator operator++(){
			this->m_curr = this->m_curr->m_next;
			return *this;
		}
		iterator operator++(int){
			iterator old = *this;
			this->m_curr = this->m_curr->m_next;
			return old;
		}
		iterator operator--(){
			this->m_curr = this->m_curr->m_prev;
			return *this;
		}
		iterator operator--(int){
			iterator old = *this;
			this->m_curr = this->m_curr->m_prev;
			return old;
		}
		std::string getKey(){
			return this->m_curr->m_data.key;
		}

		T& getValue(){
			return this->m_curr->m_data;
		}
		void setValue(T& value){
			this->m_curr->m_data.data = value.data;
		}
	};
	DList(){
		m_head = new Node();
		m_tail = new Node();
		m_head->m_next = m_tail;
		m_head->m_prev = nullptr;
		m_tail->m_prev = m_head;
		m_tail->m_next = nullptr;

		m_size = 0;
	}
	iterator begin(){
		iterator iter(m_head->m_next);
		return iter;
	}
	iterator end(){
		iterator iter(m_tail);
		return iter;
	}
	const_iterator begin() const{
		const_iterator const_iter(m_head->m_next);
		return const_iter;
	}
	const_iterator end() const{
		const_iterator const_iter(m_tail);
		return const_iter;
	}
	void push_front(const T& _data){
		Node*temp = new Node(_data, m_head->m_next, m_head);
		Node* connct = m_head->m_next;
		m_head->m_next = temp;
		connct->m_prev = temp;
		m_size++;
	}
	void push_back(const T& _data){
		Node* temp = new Node(_data, m_tail, m_tail->m_prev);
		Node* connct = m_tail->m_prev;
		m_tail->m_prev = temp;
		connct->m_next = temp;
		m_size++;
	}
	void pop_front(){
		if (m_head->m_next != m_tail){
			Node* delte = m_head->m_next;
			Node* connct = delte->m_next;
			delete delte;
			connct->m_prev = m_head;
			m_head->m_next = connct;
			m_size--;
		}
	}
	void pop_back(){
		if (m_tail->m_prev != m_head){
			Node* delte = m_tail->m_prev;
			Node* connct = delte->m_prev;
			delete delte;
			connct->m_next = m_tail;
			m_tail->m_prev = connct;
			m_size--;
		}
	}
	iterator insert(iterator loc, const T& data){
			Node* locatin = loc.m_curr;
			Node* prv = locatin;
			if (loc.m_curr){
				prv = locatin->m_prev;
			}

			if (loc != end() && loc != m_head){
				Node* temp = new Node(data, locatin, prv);
				prv->m_next = temp;
				locatin->m_prev = temp;
			}
			else if (loc == m_head){
				Node* temp = new Node(data, m_head->m_next, m_head);
				Node* nx = m_head->m_next;
				nx->m_prev = temp;
				m_head->m_next = temp;
			}
			else{
				Node* temp = new Node(data, m_tail, m_tail->m_prev);
				Node* prv = m_tail->m_prev;
				prv->m_next = temp;
				m_tail->m_prev = temp;
			}
			++m_size;
			return --loc;
	}
	//WRAPPER FUNCTION
	private:
		Node* getNode(iterator it){
			return it.m_curr;
		}
	public:
	void erase(iterator it){
		Node* delte = it.m_curr;
		Node* connctPrev = delte->m_prev;
		Node* connctNext = delte->m_next;

		connctNext->m_prev = connctPrev;
		connctPrev->m_next = connctNext;
		delete delte;
		--m_size;
	}
	void erase(iterator first, iterator last){
		Node* curr = first.m_curr;
		Node* lastCurr = last.m_curr;
		Node* next;
		Node* currPrev = curr->m_prev;
		while (curr != lastCurr){
			next = curr->m_next;
			delete curr;
			curr = next;
			--m_size;
		}
		if (currPrev){  //Check that currPrev is not nullptr 
			currPrev->m_next = lastCurr;
			lastCurr->m_prev = currPrev;
		} else{
			m_head->m_next = lastCurr;
			lastCurr->m_prev = m_head;
		}
	}
	iterator search(string key) const{
		const_iterator iter = begin();
		bool found = false;
		string tmp;
		while (!found && iter.m_curr != m_tail){
			tmp = iter.m_curr->m_data.key;
			if (tmp == key){
				found = true;
			}
			else{
				iter++;
			}
		}
		iterator it;
		it.m_curr = iter.m_curr;
		return it;
	}

	bool empty() const{
		if (!m_head && !m_tail || m_head->m_next == m_tail){
			return true;
		}
		return false;
	}
	~DList(){
		if (m_head){
			erase(begin(), end());
		}
		delete m_head;
		delete m_tail;
		m_head = m_tail = nullptr;
	}
	DList(const DList& cpyList){
		*this = cpyList;
	}
	DList& operator=(const DList& cpyList){

		if (!empty()){    //Check to see if there are Nodes in the current object to be deleted
			Node* delte = m_head->m_next;
			while (delte != m_tail){
				Node* nex = delte->m_next;
				delete delte;
				delte = nex;
			}
			m_head->m_next = m_tail;
			m_tail->m_prev = m_head;
		} else{
			m_head = new Node();
			m_tail = new Node();
			m_head->m_next = m_tail;
			m_head->m_prev = nullptr;
			m_tail->m_prev = m_head;
			m_tail->m_next = nullptr;
		}
		
		
		if (!cpyList.empty()){   
			if (this != &cpyList){	//Make sure that you are not copying the same object
				const_iterator iterBeg = cpyList.begin();
				const_iterator iterEnd = cpyList.end();
				while (iterBeg!= iterEnd){
					push_back(*iterBeg);
					iterBeg++;
				}
			}
		}
		return *this;
	}
	DList(DList&& mveList){
		*this = std::move(mveList);
	}
	DList& operator=(DList&& mveList){
		m_head = std::move(mveList.m_head);
		m_tail = std::move(mveList.m_tail);
		m_size = std::move(mveList.m_size);

		mveList.m_head = nullptr;
		mveList.m_tail = nullptr;
		mveList.m_size = 0;


		return *this;
	}
};
#endif
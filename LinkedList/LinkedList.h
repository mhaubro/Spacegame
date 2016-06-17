//Author: MG

#ifndef SRC_LINKEDLIST_LINKEDLIST_H_
#define SRC_LINKEDLIST_LINKEDLIST_H_

template<class T>
class LinkedList {
protected:

	struct Node {
		T* mData;
		Node * mNext;
		Node(T* _data, Node* _next) :
				mData(_data), mNext(_next) {
		}
		~Node() {
			delete mData;
		}
	};

	Node* mHead;
	int mSize;

	virtual bool shouldRemove(Node* node){
		return false;
	}

public:

	LinkedList();
	virtual ~LinkedList();

	void add(T* t);
	void clean();

	int size();
};

template<class T> LinkedList<T>::LinkedList() :
mHead(), mSize(0) {

}
template<class T> LinkedList<T>::~LinkedList() {
	while (mHead) {
		Node* next = mHead->mNext;
		delete mHead;
		mHead = next;
	}
}

template<class T> void LinkedList<T>::add(T* t) {
	mHead = new Node(t, mHead);
	mSize++;
}

template<class T> void LinkedList<T>::clean() {
	if (mHead) {
		Node* prev = mHead;
		Node* tmp = mHead->mNext;
		while (tmp) {
			if (shouldRemove(tmp)) {
				Node* next = tmp->mNext;
				delete tmp;
				tmp = next;
				prev->mNext = tmp;
				mSize--;
			} else {
				prev = tmp;
				tmp = tmp->mNext;
			}
		}
		if (shouldRemove(mHead)) {
			tmp = mHead->mNext;
			delete mHead;
			mHead = tmp;
			mSize--;
		}
	}
}

template<class T> int LinkedList<T>::size() {
	return mSize;
}

#endif /* SRC_LINKEDLIST_LINKEDLIST_H_ */

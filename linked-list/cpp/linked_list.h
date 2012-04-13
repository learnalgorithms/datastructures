#ifndef LINKED_LIST_H__
#define LINKED_LIST_H__

namespace LearnAlgorithms {

template<typename type>
class ListElement {
public:
	ListElement(type);
	ListElement();

	void setData(type);
	type data();
	bool hasNext();
	ListElement<type>* next();
	bool hasPrevious();
	ListElement<type>* previous();

	ListElement<type> *nextElement;
	ListElement<type> *previousElement;

private:
	type elementData;
};

template<typename type>
ListElement<type>::ListElement()
{
	nextElement = previousElement = 0;
}

template<typename type>
ListElement<type>::ListElement(type initialValue)
{
	setData(initialValue);
	nextElement = previousElement = 0;
}

template<typename type>
type ListElement<type>::data()
{
	return elementData;
}

template<typename type>
void ListElement<type>::setData(type newValue)
{
	elementData = newValue;
}

template<typename type>
bool ListElement<type>::hasNext()
{
	return nextElement != 0;
}

template<typename type>
bool ListElement<type>::hasPrevious()
{
	return previousElement != 0;
}

template<typename type>
ListElement<type>* ListElement<type>::next()
{
	return nextElement;
}

template<typename type>
ListElement<type>* ListElement<type>::previous()
{
	return previousElement;
}


template<typename type>
class LinkedList {
public:
	LinkedList();
	~LinkedList();

	ListElement<type>* addFirst(type);
	ListElement<type>* addLast(type);

	bool remove(type);
	ListElement<type>* removeFirst();
	ListElement<type>* removeLast();

	ListElement<type>* find(type);

	void clear();

	int size();
	type head();
	type tail();

private:
	ListElement<type> *listHead;
	ListElement<type> *listTail;
	int listSize;
};


template<typename type>
LinkedList<type>::LinkedList()
{
	/* set initial size */
	listSize = 0;

	/* adjusting pointers */
	listHead = listTail = 0;
}

template<typename type>
LinkedList<type>::~LinkedList()
{
	clear();
}

template<typename type>
ListElement<type>* LinkedList<type>::addFirst(type newValue)
{
	ListElement<type> *newNode = new ListElement<type>(newValue);

	if (listSize == 0) {
		listHead = newNode;
		listTail = newNode;
	} else {
		listHead->previousElement = newNode;
		newNode->nextElement = listHead;
		listHead = newNode;
	}

	listSize++;
	return newNode;
}

template<typename type>
ListElement<type>* LinkedList<type>::addLast(type newValue)
{
	ListElement<type> *newNode = new ListElement<type>(newValue);

	if (listSize == 0) {
		listHead = newNode;
		listTail = newNode;
	} else {
		newNode->previousElement = listTail;
		listTail->nextElement = newNode;
		listTail = newNode;
	}

	listSize++;
	return newNode;
}

template<typename type>
ListElement<type>* LinkedList<type>::find(type value)
{
	ListElement<type> *i = 0;

	for (i = listHead; i; i = i->next()) {
		if (i->data() == value) {
			break;
		}
	}

	return i;
}

template<typename type>
bool LinkedList<type>::remove(type value)
{
	bool ret = false;

	ListElement<type> *i = find(value);
	if (i) {
		if (listSize == 1) {
			/* head and tail at once */
			listHead = listTail = 0;
		} else if (!i->hasPrevious()) {
			/* head */
			i->nextElement->previousElement = 0;
			listHead = i->nextElement;
		} else if (!i->hasNext()) {
			/* tail */
			i->previousElement->nextElement = 0;
			listTail = i->previousElement;
		} else {
			/* middle element */
			i->previousElement->nextElement = i->nextElement;
			i->nextElement->previousElement = i->previousElement;
		}

		delete i;
		listSize--;
		ret = true;
	}

	return ret;
}

template<typename type>
ListElement<type>* LinkedList<type>::removeFirst()
{
	ListElement<type> *i = 0;

	if (listSize > 0) {
		i = listHead;

		if (listSize == 1) {
			listHead = listTail = 0;
		} else {
			listHead = listHead->nextElement;
			listHead->previousElement = 0;
		}

		listSize--;
	}

	return i;
}

template<typename type>
ListElement<type>* LinkedList<type>::removeLast()
{
	ListElement<type> *i = 0;

	if (listSize > 0) {
		i = listTail;

		if (listSize == 1) {
			listHead = listTail = 0;
		} else {
			listTail = listTail->previousElement;
			listTail->nextElement = 0;
		}

		listSize--;
	}

	return i;
}

template<typename type>
void LinkedList<type>::clear()
{
	if (listSize > 0) {
		ListElement<type> *i;

		while (listSize > 0) {
			i = removeFirst();
			delete i;
		}

		listHead = listTail = 0;
	}
}

template<typename type>
int LinkedList<type>::size()
{
	return listSize;
}

template<typename type>
type LinkedList<type>::head()
{
	return listHead->data();
}

template<typename type>
type LinkedList<type>::tail()
{
	return listTail->data();
}

}; /* namespace end */

#endif /* LINKED_LIST_H__ */

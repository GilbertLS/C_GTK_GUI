#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

template <class T> class Queue;
template <class T> Queue<T> operator+(Queue<T>&, T*);
template <class T> Queue<T> operator+(T*, Queue<T>&);
template <class T> Queue<T> operator+(Queue<T>&, Queue<T>&);
template <class T> Queue<T> operator-(Queue<T>&, T*);
template <class T> Queue<T> operator-(Queue<T>&, Queue<T>&);

template <class T>
class Queue
{
  friend Queue<T> operator+ <>(Queue<T>&, T*);
  friend Queue<T> operator+ <>(T*, Queue<T>&);
  friend Queue<T> operator+ <>(Queue<T>&, Queue<T>&);
  friend Queue<T> operator- <>(Queue<T>&, T*);
  friend Queue<T> operator- <>(Queue<T>&, Queue<T>&);
  class Node
  {
    friend class Queue;

    private:
      Node(T* item=NULL);
      T* data;
      Node* next;
  };

  public:
    Queue();
    ~Queue();

    //Dynamically allocates the copied data
    //Be sure to delete (which can be done with deleteData()
    Queue(const Queue<T>&);

    //Deletes all dynamically allocated memory including the data
    //So this deletes data + nodes, destructor only deletes nodes
    void deleteData();

    void pushBack(T*);
    T* popFront();
    T* front() const;
    bool empty() const;

    //Overloaded operators
    T* operator[](int);
    Queue<T>& operator+=(T*);
    Queue<T>& operator+=(Queue<T>&);
    Queue<T>& operator-=(T*);
    Queue<T>& operator-=(Queue<T>&);
    Queue<T>& operator!();
    Queue<T>& operator=(const Queue<T>&); //Used with + and -

    void debugPrint() const;

    int getSize();

  private:
    Node* head;
    Node* tail;
    int size;

};

template <class T>
int Queue<T>::getSize()
{
  return size;
}

//Template class must have implementation in header file

template <class T>
Queue<T>::Node::Node(T* item) : data(item), next(0)
{ }

template <class T>
Queue<T>::Queue() : size(0), head(0), tail(0)
{ }

template <class T>
Queue<T>::~Queue() 
{
  !(*this);
}

template <class T>
Queue<T>::Queue(const Queue<T>& q) : size(0), head(0), tail(0)
{
  Node* curNode = q.head;
  while(curNode != NULL){
    T* newData = new T(*(curNode->data));
    pushBack(newData);
    curNode = curNode->next;
  }
}

template <class T>
void Queue<T>::deleteData()
{
  Node* curNode = head;
  while(curNode != NULL){
    Node* delNode = curNode;
    curNode = curNode->next;
    delete delNode->data;
    delete delNode;
  }
  head = tail = 0;
  size = 0;
}

//Adds an item to the back of the list
template <class T>
void Queue<T>::pushBack(T* item)
{
  Node* n = new Node(item);
  if(size++ == 0){
    head = n;
  }else{
    tail->next = n;
  }
  tail = n;

}


//Removes and returns the item at the front of the list
template <class T>
T* Queue<T>::popFront()
{
  if(size > 0){
    Node* n = head;
    head = n->next;
    T* item = n->data;
    delete n;
    size--;
    return item;
  }else{
    return NULL;
  }
}

//Returns the first item (next to be popped)
template <class T>
T* Queue<T>::front() const
{
  if(head != NULL)
    return head->data;
  else
    return NULL;
}

//Returns true if the list is empty
template <class T>
bool Queue<T>::empty() const
{
  return size == 0;
}

//Prints out the elements in the list
//NOTE: Only works on types that support the stream insertion operator 
template <class T>
void Queue<T>::debugPrint() const
{
  Node* curNode = head;
  while(curNode != NULL){
    cout << *(curNode->data) << ", ";
    curNode = curNode->next;
  }
  cout << endl;
}

//Overloaded operators
template <class T>
T* Queue<T>::operator[](int index)
{
  if(index < 0 || index >= size)
    return NULL;

  int i = 0;
  Node* curNode = head;
  while(i < index){ //No need to check curNode != NULL because index < size
    curNode = curNode->next;
    i++;
  }
  return curNode->data;
}
template <class T>
Queue<T>& Queue<T>::operator+=(T* e)
{
  pushBack(e);
  return *this;
}
template <class T>
Queue<T>& Queue<T>::operator+=(Queue<T>& q)
{
  
  Node* curNode = q.head;
  while(curNode != NULL){
    *this += curNode->data;
    curNode = curNode->next;
  }
  return *this;
}
template <class T>
Queue<T>& Queue<T>::operator-=(T* e)
{
  Node* curNode = head;
  Node* prevNode = NULL;
  while(curNode != NULL){
    if(curNode->data == e){
      if(prevNode != NULL)
        prevNode->next = curNode->next;
      if(tail == curNode)
        tail = prevNode;
      if(head == curNode)
        head = curNode->next;
      delete curNode;
    }
    prevNode = curNode;
    curNode = curNode->next;
  }
  return *this;
}
template <class T>
Queue<T>& Queue<T>::operator-=(Queue<T>& q)
{
  Node* curNode = q.head;
  while(curNode != NULL){
    *this -= curNode->data;
    curNode = curNode->next;
  }
  return *this;
}
template <class T>
Queue<T>& Queue<T>::operator!()
{
  Node* curNode = head;
  while(curNode != NULL){
    Node* delNode = curNode;
    curNode = curNode->next;
    delete delNode;
  }
  size = 0;
  tail = head = 0;
  return *this;
}
template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& q)
{
  !(*this);
  Node* curNode = q.head;
  while(curNode != NULL){
    T* newData = new T(*(curNode->data));
    *this += newData;
    curNode = curNode->next;
  }
  return *this;
}

//Returning by value because this lets the user of this class not have to
// worry about it's memory (unless they want to)
template <class T>
Queue<T> operator+(Queue<T>& q, T* e)
{
  Queue<T> newQ;
  newQ += q;
  newQ += e;
  return newQ;
}
template <class T>
Queue<T> operator+(T* e, Queue<T>& q)
{
  Queue<T> newQ;
  newQ += e;
  newQ += q;
  return newQ;
}
template <class T>
Queue<T> operator+(Queue<T>& ql, Queue<T>& qr)
{
  Queue<T> newQ;
  newQ += ql;
  newQ += qr;
  return newQ;
}
template <class T>
Queue<T> operator-(Queue<T>& q, T* e)
{
  Queue<T> newQ;
  newQ += q;
  newQ -= e;
  return newQ;
}
template <class T>
Queue<T> operator-(Queue<T>& ql, Queue<T>& qr)
{
  Queue<T> newQ;
  newQ += ql;
  newQ -= qr;
  return newQ;
}

#endif

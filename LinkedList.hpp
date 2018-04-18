#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include "Node.hpp"

using namespace std;


template <class T> 
class LinkedList {
    private:
        Node<T>* head;
		Node<T>* tail;
		size_t  size; 
    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();


        Node<T>* getHead() const;
        void setHead(Node<T>* n);
        Node<T>* getTail() const;
        void setTail(Node<T>* n);
        Node<T>* findPrev(const T& data) const;
        Node<T>* findNode(const T& data) const;
        void insertNode(Node<T>* prev, const T& data); 
        void deleteNode(Node<T>* prevNode);  
        void clear();
        bool isEmpty() const;
        size_t getSize() const;
        void print() const;
};

template <class T>
void LinkedList<T>::print() const{
    const Node<T>* node = head;
    while (node != NULL) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

template <class T>
LinkedList<T>::LinkedList(){
    head = tail = NULL;
    size = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll){

    *this = ll;

}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll){

    Node<T>* r = ll.head;
    Node<T>* p;

    if (&ll != this){
        head = NULL;

        if(&ll){
        head = new Node<T>(r->getData());
        p = head;
        r = r->getNext();

        while(r!= NULL){
            insertNode(p, r->getData());
            r = r->getNext();
            p = p->getNext();
        }
    tail = p;
    size = ll.getSize(); 
    }}
    
    return *this;
}

template <class T>
LinkedList<T>::~LinkedList(){
    Node<T>* discard;
    while (head != NULL){
        discard = head;
        head = head->getNext();
        delete discard;
    }
    head = NULL;
    tail = NULL;
}


template <class T>
Node<T>* LinkedList<T>::getHead() const{
    return head;
}


template <class T>
void LinkedList<T>::setHead(Node<T>* n){
    head = n;
}


template <class T>
Node<T>* LinkedList<T>::getTail() const{
    return tail;
}

template <class T>
void LinkedList<T>::setTail(Node<T>* n){
    tail = n;
}



template <class T>
Node<T>* LinkedList<T>::findPrev(const T& data) const{
    Node<T>* p = head;
    Node<T>* r = head->getNext();

    if(p->getData()==data)
        return NULL;
    else {

        while(p->getNext()){
            if(p->getNext()->getData() == data)
                return p;
            else
                p = p->getNext();
        }
    }
    return NULL;
}


template <class T>
Node<T>* LinkedList<T>::findNode(const T& data) const{
    Node<T>* curr = head;
    while(curr != NULL){
        if(curr->getData() == data)
            return curr;
        else
            curr = curr->getNext();
    }

    return NULL;
}


template <class T>
void LinkedList<T>::insertNode(Node<T>* prev, const T& data){

    Node<T>* newNode = new Node<T>(data);

    if(prev){
    
        newNode->setNext(prev->getNext());
        prev->setNext(newNode);
    }
    else{
        head = newNode;

    }
    
    if(newNode->getNext() == NULL){
        tail = newNode;
    }

    size++;
}



template <class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode){
    
    if(prevNode != NULL){
        Node<T>* tmp = prevNode->getNext();
        prevNode->setNext(tmp->getNext());
        if(tmp->getNext()== NULL){
            tail = prevNode;
        }
        delete tmp;
    }

    else{
        Node<T>* tmp2 = head;
        head = head->getNext();
        delete tmp2;
    }
    size--;

}



template <class T>
void LinkedList<T>::clear(){

    Node<T>* discard;
    while (head != NULL) {
        discard = head;
        head = head->getNext();
        delete discard;
    }
    head = NULL;
    tail = NULL;
}




template <class T>
bool LinkedList<T>::isEmpty() const{
    return head == NULL;
}


template <class T>
size_t LinkedList<T>::getSize() const{
    return size;
}



#endif

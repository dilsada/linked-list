#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "Node.hpp"

template <class T>
class MyStack{
    private:
    Node<T> *top;                
    public:

    MyStack();                     					

    MyStack(const MyStack<T>& rhs);  				

    ~MyStack(); 

    MyStack<T>& operator=(const MyStack<T>& rhs);  	

    bool isEmpty() const;

    void push(const T& newItem);

    void pop();

    Node<T>* Top() const;

    void print() const;
};

template <class T>
void MyStack<T>::print() const{
    const Node<T>* node = top;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}


template <class T>
MyStack<T>::MyStack(){
    top = NULL;
}                                     


template <class T>
MyStack<T>::MyStack(const MyStack<T>& rhs){
    *this = rhs;
}               


template <class T>
MyStack<T>::~MyStack(){
    while(!isEmpty()){
        pop();
    }
}

template <class T>
MyStack<T>& MyStack<T>::operator=(const MyStack<T>& rhs){
    Node<T>* r = rhs.top;
    Node<T>* l;

    if(this != &rhs){
        while(!isEmpty())
            pop();
        if(rhs.top == NULL){
            top = NULL;
        }
        else{
            top = new Node<T>(r->getData());
            l = top;
            r = r->getNext();
            while(r != NULL){
                l->setNext(new Node<T>(r->getData()));
                l = l->getNext();
                r = r->getNext();
            } 
        }
    }
    return *this;

}


template <class T>
bool MyStack<T>::isEmpty() const{
    return top == NULL;
}


template <class T>
void MyStack<T>::push(const T& newItem){

    Node<T>* newptr = new Node<T>(newItem);

    newptr->setNext(top);
    top = newptr;
}


template <class T>
void MyStack<T>::pop(){

    if(!isEmpty()){
        Node<T>* tmp = top;
        top = top->getNext();
        delete tmp;
    }
}


template <class T>
Node<T>* MyStack<T>::Top() const{
    return top;
}


#endif /* MYSTACK_HPP */


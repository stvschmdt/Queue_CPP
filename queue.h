#ifndef QUEUE_H_
#define QUEUE_H_
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>


class Customer{
    private:
	long arrive;
	int processtime;
    public:
	Customer() {arrive = processtime = 0;}
	void set(long when);
	long when() const { return arrive;}
	int ptime() const { return processtime;}
};

typedef Customer Item;


class Queue{
    private:
	Queue(const Queue & q) : qsize(0){}
	Queue & operator=(const Queue & q){return *this;}
	struct Node{Item item; struct Node *next;};
	enum{Q_SIZE = 10};
	Node * front;
	Node * rear;
	int items;
	const int qsize;
    public:
	Queue(int qs = Q_SIZE);
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item &item);
	bool dequeue(Item &item);

};

struct Node{
    Item item;
    struct Node * next;
};

Queue::Queue(int qs) :qsize(qs){
    front = rear = NULL;
    items = 0;
}

bool Queue::enqueue(const Item & item){
    if(isfull())
	return false;
    Node * add = new Node;
    if (add == NULL)
	return false;
    add->item = item;
    add->next = NULL;
    items++;
    if(front ==NULL)
	front =add;
    else
	rear->next = add;
    rear = add;
    return true;

}

bool Queue::dequeue(Item & item){
    if (front==NULL)
	return false;
    item = front->item;
    items--;
    Node * temp = front;
    front = front->next;
    delete temp;
    if(items==0)
	rear = NULL;
    return true;
}


Queue::~Queue(){
    Node * temp;
    while(front!=NULL){
	temp =front;
	front = front->next;
	delete temp;
    }
}


void Customer::set(long when){
    processtime = std::rand() %3 + 1;
    arrive = when;
}

bool Queue::isempty() const{
    return items ==0;
}

bool Queue::isfull() const{
    return items == qsize;
}

int Queue::queuecount() const{
    return items;
}

#endif

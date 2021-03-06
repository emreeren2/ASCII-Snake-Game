/*Author: Zeynep Dogmus
 *Date: March 2013
 *Operator Overloading with Queue
*/
#include <iostream>
#include "DynamicIntQueue.h"
using namespace std;

//********************************************
// Constructor. Generates an empty queue     *
//********************************************
DynamicIntQueue::DynamicIntQueue()
{
	front = NULL;
	rear = NULL;
}

QueueNode* DynamicIntQueue::GetFront()
{
	return front;
}

QueueNode* DynamicIntQueue::GetRear()
{
	return rear;
}

//********************************************
// Deep Copy Constructor                     *
//********************************************
DynamicIntQueue::DynamicIntQueue(const DynamicIntQueue & copy)
{
	createClone(copy);
	//#ifdef _DEBUG
	//	cout << "Copy constructor is invoked\n";
	//	cout << endl;
	//#endif
}


//******************************************************************
// Shallow Copy Constructor:									   *
// Queue that is copied with a shallow copy will be problematic.   *
// Since it only copies the front and rear of the original queue.  *
// Copied queue will be modified as the original queue is modified.*
//******************************************************************
/*
DynamicStringQueue::DynamicStringQueue(const DynamicStringQueue & q)
{
	front = q.front;	//front copy
	rear = q.rear;		//rear copy
}
*/

void DynamicIntQueue::createClone(const DynamicIntQueue & copy)
{
	if (copy.front == NULL) 
	{
		front = NULL;
		rear = NULL;
	}
	else
	{
		QueueNode * temp = copy.front;
		front = new QueueNode(temp->row, temp->col, NULL);
		rear = front;

		while(temp->next != NULL) 
		{
			temp = temp->next;
			rear->next = new QueueNode(temp->row, temp->col, NULL);
			rear = rear->next;
		}
	}
}

//****************************************************
// Assignment operator                               *                                    
//****************************************************
const DynamicIntQueue & DynamicIntQueue::operator=(const DynamicIntQueue & rhs) // !!!!!!!!!!!!!!!!!! BUNU DUZENLEMEDIM
{
	//Check whether the rhs object is different than our queue
	if (this != &rhs)
	{
		clear(); 
		createClone(rhs);
	}
	return *this;
}

//********************************************************************
// Compares the number of elements inside the queue with the integer *
// parameter "value", returns true if it is smaller than the value   *
//********************************************************************
bool DynamicIntQueue::operator<(int value) // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! BUNU DUZENLEMEDIM
{
	QueueNode *tempNode;
	int counter=0;

	tempNode = front;
	while(tempNode != NULL)
	{
		counter++;
		tempNode = tempNode->next;
	}

	if(counter<value)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void DynamicIntQueue::enqueue(int row, int col)
{
	if (isEmpty())   //if the queue is empty
	{	//make it the first element
		front = new QueueNode(row, col);
		rear = front;
	}
	else  //if the queue is not empty
	{	//add it after rear
		rear->next = new QueueNode(row, col);
		rear = rear->next;
	}
	//#ifdef _DEBUG
	//	cout << elmt << " enqueued\n";
	//#endif
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void DynamicIntQueue::dequeue(int & R, int & C)
{
	QueueNode *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's value, advance front and delete old front
		R = front->row;
		C = front->col;
		temp = front;
		front = front->next;
		delete temp;      
	}
	//#ifdef _DEBUG
	//	cout << elmt << " dequeued\n";
	//#endif
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool DynamicIntQueue::isEmpty() const
{
	if (front == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//********************************************
// Function clear dequeues all the elements  *
// in the queue.                             *
//********************************************
void DynamicIntQueue::clear(void)
{
	int row, col;   // Dummy variable for dequeue

	while(!isEmpty())
	{
		dequeue(row, col); //delete all elements
	}
}

DynamicIntQueue::~DynamicIntQueue()
{
	clear();
	//#ifdef _DEBUG
	//	cout << "Destructor is invoked\n";
	//	cout << endl;
	//#endif
}
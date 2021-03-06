#ifndef DYNAMICINTQUEUE_H
#define DYNAMICINTQUEUE_H

#include <string>
using namespace std;

struct QueueNode
{
	int row, col;
	QueueNode *next;
	QueueNode(int R, int C, QueueNode *ptr = NULL)
	{
		row = R;
		col = C;
		next = ptr;
	}
};

class DynamicIntQueue
{
	private:
		QueueNode *front;
		QueueNode *rear;

	public:
		DynamicIntQueue();
		~DynamicIntQueue();
		//Deep Copy or Shallow Copy Constructor (by commenting out necessary parts)
		DynamicIntQueue(const DynamicIntQueue &);

		void enqueue(int, int);
		void dequeue(int &, int &);
		bool isEmpty() const; 
		void clear(void);

		QueueNode* GetFront();
		QueueNode* GetRear();
		void createClone(const DynamicIntQueue &);
		const DynamicIntQueue & DynamicIntQueue::operator = (const DynamicIntQueue & rhs);
		bool DynamicIntQueue::operator<(int);

};


#endif
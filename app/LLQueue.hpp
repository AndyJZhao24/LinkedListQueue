#ifndef __PROJ2_QUEUE_HPP
#define __PROJ2_QUEUE_HPP

#include "runtimeexcept.hpp"

class QueueEmptyException : public RuntimeException 
{
public:
	QueueEmptyException(const std::string & err) : RuntimeException(err) {}
};


template<typename Object>
class LLQueue
{
private:
	// fill in private member data here

	//Nodes of our Linked list
	struct QNode{
		Object window_num; //Holds data for this node.
		QNode* next; //Keeps track of next node in queue.
		QNode(Object init_val, QNode* next_node = nullptr) : window_num(init_val), next(next_node) {} //Node constructor.
	};

	QNode *frontN, *rearN; //Pointers to first and last node, Will initially be nullptr when LLQueue object is instantiated.
	
	int count; //Tracks the size of the LinkedList 

public:
	LLQueue();

//	In principle, you should have copy constructors and 
// assignment operators implemented.
// I am not going to require it for this assignment.
//	LLQueue(const LLQueue & st);
//	LLQueue & operator=(const LLQueue & st);
	~LLQueue()
	{
		while (not isEmpty()) //Wile the LLQueue is not empty.
		{
			dequeue(); //Dequeue a node.
		}
	}

	int size() const noexcept;
	bool isEmpty() const noexcept;

	Object & front();
	const Object & front() const;

	void enqueue(const Object & elem);

// does not return anything.  Just removes. 
	void dequeue();
};


// TODO:  Fill in the functions here. 
template<typename Object>
LLQueue<Object>::LLQueue() : frontN(nullptr), rearN(nullptr), count(0) {} //Initializaiton list for constructor.


template<typename Object>
int LLQueue<Object>::size() const noexcept
{
	return count; //Return count, which represents the number of nodes in the linkedlist.
}

template<typename Object>
bool LLQueue<Object>::isEmpty() const noexcept
{
	return (count == 0); //Check whether there are 0 nodes.
}

template<typename Object>
Object & LLQueue<Object>::front()
{
	if (isEmpty()) //If count == 0
	{
		throw QueueEmptyException("Tried to access an empty queue."); 
	}
	return frontN -> window_num; //Return the data that frontN holds.
}

template<typename Object>
const Object & LLQueue<Object>::front() const
{
	if (isEmpty()) //If count == 0
	{
		throw QueueEmptyException("Tried to access an empty queue.");
	}
	return frontN -> window_num; //Return the data the frontN holds

}

template<typename Object>
void LLQueue<Object>::enqueue(const Object & elem)
{

	if (isEmpty()) //If count == 0
	{
		frontN = new QNode(elem); //frontN now points to a new node initialized with value elem.
		rearN = frontN; //Since there is only one node. That node is both the front and rear node.
	}
	else //If there is more than 1 node in the LL.
	{
		rearN->next = new QNode(elem); //Assign rearN's next to be the new node. 
		rearN = rearN->next; //Have rear point to that node.
	}
	count++; //Increment count(which represents the number of nodes in the LL)
}

template<typename Object>
void LLQueue<Object>::dequeue()
{
	if(isEmpty()) //If count == 0.
	{
		throw QueueEmptyException("Tried to dequeue an empty queue.");
	}
	QNode* tmp = frontN; //Keep track of the first node in the LL.
	if (frontN == rearN) //If the first node is the only node in the LL.
	{
		rearN = nullptr; //Set rearN to nullptr.
	}
	frontN = frontN->next; // Have frontN point to its next node.
	delete tmp; //Delete the original frontN.
	count--; //Decrement count.
}
#endif 

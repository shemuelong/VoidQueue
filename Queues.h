#ifndef INC_110C_MIDTERM_QUEUES_H
#define INC_110C_MIDTERM_QUEUES_H

//Code taken from Clifford A Shaffer's Data Structure and Algorithm Analysis

#include <iostream>
#include <cstdlib>

using namespace std;


// Assert: If "val" is false, print a message and terminate
// the program
void Assert(bool val, string s) {
	if (!val) { // Assertion failed -- close the program
		cout << "Assertion Failed: " << s << endl;
		exit(-1);
	}
}

// Abstract queue class

class Queue {       //Queue ADT is no longer a template, as it now holds an array of void*
private:
	void operator =(const Queue&) {} // Protect assignment
	Queue(const Queue&) {} // Protect copy constructor
public:
	Queue() {} // Default
	virtual ~Queue() {} // Base destructor
// Reinitialize the queue. The user is responsible for
// reclaiming the storage used by the queue elements.
	virtual void clear() = 0;
// Place an element at the rear of the queue.
// it: The element being enqueued.
	virtual void enqueue(void*, string) = 0;
// Remove and output the element at the front of the queue.
	virtual void dequeue() = 0;         //dequeue previously had the return type of E
                                        //However, since the queue now consists of void* it cannot have a return type of E because the datatype of each element is different
                                        //To satisfy the prompt, the values are printed out instead of returned.
// Return: The number of elements in the queue.
	virtual int length() const = 0;
//Outputs the front Value to the screen
    virtual void frontValue() const = 0;//frontValue() has been changed to a void like dequeue for the same reason above
};

// Array-based queue implementation
class AQueue: public Queue{
private:
	int maxSize; // Maximum size of queue
	int front; // Index of front element
	int rear; // Index of rear element
	void** listArray; // Array is declared as a void**, meaning it points to an array of void*
	string* stringArray; //To store the datatype of each element, a secondary array of strings is initialized
public:
	AQueue(int size = 6) { // Constructor
// Make list array one position larger for empty slot
		maxSize = size+1;
		rear = 0; front = 1;
		listArray = new void*[maxSize];     //an array of void* is dynamically allocated with a given size of 6
		stringArray = new string[maxSize];  //an array of strings is allocated to store the datatypes of the corresponding elements
	}
	~AQueue() { delete [] listArray; delete [] stringArray;} // Destructor deletes both arrays
	void clear() { rear = 0; front = 1; } // Reinitialize
	void enqueue(void* ptr, string s) override { // Put "it" in queue
		Assert(((rear+2) % maxSize) != front, "Queue is full");
		rear = (rear+1) % maxSize; // Circular increment
        listArray[rear] = ptr;      //When a new element is queued, its value is stored in the void* array
		stringArray[rear] = s;      //Its datatype name is stored in the string array
	}

  void dequeue() override { // Take element out
      Assert(length() != 0, "Queue is empty");
      void *it = listArray[front];            //In order to dequeue, two temporary variables are declared with the same element value and datatype name
      string its = stringArray[front];
      front = (front+1) % maxSize; // Circular increment
      if (its == "string") {           //If the element is a string, its void* data is casted as such and outputted to the screen
          string *temp = static_cast<string*>(it);
          std::cout << *temp << std::endl;
      } else if (its == "int") {       //If the element is an int, its void* data is casted as such and outputted to the screen
          int* temp = static_cast<int*>(it);
          std::cout << *temp << std::endl;
      } else if (its == "double") {    //If the element is a double, its void* data is casted as such and outputted to the screen
          double* temp = static_cast<double*>(it);
          std::cout << *temp << std::endl;
      }
  }

  void frontValue() const { // Get front value
      Assert(length() != 0, "Queue is empty");    //frontValue() function has been rewritten with the same code as dequeue to output the first element in the Queue
      void *it = listArray[front];                //However, frontValue() does not dequeue the front element, it simply prints it.
      string its = stringArray[front];
      if (its == "string") {
          string *temp = static_cast<string*>(it);
          std::cout << *temp << std::endl;
      } else if (its == "int") {
          int* temp = static_cast<int*>(it);
          std::cout << *temp << std::endl;
      } else if (its == "double") {
          double* temp = static_cast<double*>(it);
          std::cout << *temp << std::endl;
      }
  }

    virtual int length() const // Return length
    { return ((rear+maxSize) - front + 1) % maxSize; }
};

#endif //INC_110C_MIDTERM_QUEUES_H

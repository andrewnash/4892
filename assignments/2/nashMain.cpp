//
// Created by adn11 on 2018-06-02.
//

#include <iostream>
#include "CircularQueue.h"

using namespace std;

int main()
{
    //general methods test 1
    int size = 4;
    CircularQueue<int> intQueue(size);
    cout << "CircularQueue intQueue created" << endl << endl;

    cout << "Test 1 Begin:" << endl;
    //basic empty queue
    if (!intQueue.empty())
    {
        cout << "empty() failed!" << endl;
    }
    if(intQueue.full())
    {
        cout << "full() failed!" << endl;
    }

    for(int i = 0; i != size; i++)
    {
        if(intQueue.depth() != i)
        {
            cout << "depth() failed!" << endl;
        }
        intQueue.enqueue(i*2);
        if(intQueue.depth() != i+1)
        {
            cout << "depth() failed!" << endl;
        }
    }

    if(intQueue.peek())
    {
        cout << "peek() failed!" << endl;
    }
    if(intQueue.enqueue(69))
    {
        cout << "enqueue failed! I added a value while the queue was full!" << endl;
    }
    if(intQueue.empty())
    {
        cout << "empty() failed! - the queue is full but returned true" << endl;
    }
    if(!intQueue.full())
    {
        cout << "full() failed! - the queue is full but returned false" << endl;
    }
    intQueue.dequeue();
    if(intQueue.depth() != 3)
    {
        cout << "depth() failed! - returned wrong depth";
    }
    if(intQueue.empty())
    {
        cout << "empty() failed! - the queue is full but returned true" << endl;
    }
    if(intQueue.full())
    {
        cout << "full() failed! - the queue not full but returned true" << endl;
    }
    intQueue.dequeue();
    intQueue.dequeue();
    intQueue.enqueue(69);
    intQueue.enqueue(420);
    intQueue.enqueue(1337);
    if(!intQueue.full())
    {
        cout << "full() failed! - the queue is full but returned false" << endl;
    }
    if(intQueue.empty())
    {
        cout << "empty() failed! - the queue is full but returned true" << endl;
    }
    if(intQueue.depth() != 4)
    {
        cout << "depth() failed!" << endl;
    }
    for(int i = 4; i != 0; i--)
    {
        intQueue.dequeue();
    }
    cout << "Test 1 complete!" << endl << endl;

    //test 2 - adding and then removing values right after
    cout << "Test 2 Begin:" << endl;
    for(int i = 0; i < size*6; i++)
    {
        int a = i * 69;
        intQueue.enqueue(i * 69);
        int b = intQueue.dequeue();
        if (a != b) {
            cout << "FAIL - could not preform test 2" << endl;
        }
    }
    cout << "Test 2 complete!" << endl << endl;

    //test 3 - adding and then removing values right after:
    //this will add 3 values then remove them a bunch of times
    //so your front and back are forced to rotate around the entire list
    cout << "Test 3 Begin:" << endl;
    for(int i = 0; i < size*6; i++)
    {
        int a1 = i * 1;
        int b1 = i * 2;
        int c1 = i * 3;
        intQueue.enqueue(i * 1);
        if(intQueue.peek() != i*1)
        {
            cout << "peek() failed on test 2!" << endl;
        }
        if(intQueue.depth() != 1)
        {
            cout << "depth() failed on test 2! on a depth of 1" << endl;
        }
        intQueue.enqueue(i * 2);
        if(intQueue.depth() != 2)
        {
            cout << "depth() failed on test 2! on a depth of 2" << endl;
        }
        intQueue.enqueue(i * 3);
        if(intQueue.depth() != 3)
        {
            cout << "depth() failed on test 2! on a depth of 3" << endl;
        }
        int a2 = intQueue.dequeue();
        int b2 = intQueue.dequeue();
        int c2 = intQueue.dequeue();
        if(a2 != a1 or b2 != b1 or c2 != c1 or !intQueue.empty() or intQueue.full() or intQueue.depth())
        {
            cout << "FAIL - could not preform test 3" << endl;
        }
    }
    cout << "Test 3 complete!" << endl << endl;


    //test 4 - copy
    cout << "Test 4 (copy) Begin:" << endl;
    for(int i = 0; i < size; i++)
    {
        intQueue.enqueue(i);
    }
    CircularQueue<int> intQueue2(intQueue);
    for(int i = 0; i < size; i++)
    {
        if(intQueue.peek() != intQueue2.peek())
        {
            cout << "peek() failed!" << endl;
        }
        if(intQueue.peek() != intQueue2.peek())
        {
            cout << "full() failed!" << endl;
        }
        if(intQueue.empty() != intQueue2.empty())
        {
            cout << "empty() failed!" << endl;
        }
        if(intQueue.depth() != intQueue2.depth())
        {
            cout << "depth() failed!" << endl;
        }
        if(intQueue.dequeue() != intQueue2.dequeue())
        {
            cout << "dequeue() failed!" << endl;
        }
    }
    cout << "Test 4 complete!" << endl << endl;

    //test 5 - move
    cout << "Test 5 (move) Begin:" << endl;
    for(int i = 0; i < size; i++)
    {
        intQueue.enqueue(i);
        intQueue2.enqueue(i);
    }
    CircularQueue<int> intQueue3(move(intQueue));
    for(int i = 0; i < size; i++)
    {
        if(intQueue3.peek() != intQueue2.peek())
        {
            cout << "peek() failed!" << endl;
        }
        if(intQueue3.peek() != intQueue2.peek())
        {
            cout << "full() failed!" << endl;
        }
        if(intQueue3.empty() != intQueue2.empty())
        {
            cout << "empty() failed!" << endl;
        }
        if(intQueue3.depth() != intQueue2.depth())
        {
            cout << "depth() failed!" << endl;
        }
        if(intQueue3.dequeue() != intQueue2.dequeue())
        {
            cout << "dequeue() failed!" << endl;
        }
    }
    cout << "Test 5 complete!" << endl << endl;

    cout << "Test 6 (copy =) Begin:" << endl;
    CircularQueue<int> intQueue4(size);
    for(int i = 0; i < size; i++)
    {
        intQueue3.enqueue(i);
    }
    intQueue4 = intQueue3;
    for(int i = 0; i != 3; i++)
    {
        if(intQueue3.peek() != intQueue4.peek())
        {
            cout << "peek() failed!" << endl;
        }
        if(intQueue3.peek() != intQueue4.peek())
        {
            cout << "full() failed!" << endl;
        }
        if(intQueue3.empty() != intQueue4.empty())
        {
            cout << "empty() failed!" << endl;
        }
        if(intQueue3.depth() != intQueue4.depth())
        {
            cout << "depth() failed!" << endl;
        }
        if(intQueue3.dequeue() != intQueue4.dequeue())
        {
            cout << "dequeue() failed!" << endl;
        }
    }
    cout << "Test 6 complete!" << endl << endl;

    cout << "Test 7 (move =) Begin:" << endl;
    CircularQueue<int> intQueue5(size);
    for(int i = 0; i < size; i++)
    {
        intQueue2.enqueue(i);
    }
    intQueue3 = intQueue2;
    intQueue5.enqueue(69);
    intQueue5.enqueue(420);
    intQueue5 = move(intQueue3);
    for(int i = 0; i < size; i++)
    {
        if(intQueue2.peek() != intQueue5.peek())
        {
            cout << "peek() failed!" << endl;
        }
        if(intQueue2.full() != intQueue5.full())
        {
            cout << "full() failed!" << endl;
        }
        if(intQueue2.empty() != intQueue5.empty())
        {
            cout << "empty() failed!" << endl;
        }
        if(intQueue2.depth() != intQueue5.depth())
        {
            cout << "depth() failed!" << endl;
        }
        if(intQueue2.dequeue() != intQueue5.dequeue())
        {
            cout << "dequeue() failed!" << endl;
        }
    }
    cout << "Test 7 complete!" << endl << endl;

    cout << "Test 8 (delete) Begin: " << endl;
    CircularQueue<int> *heapQ = new CircularQueue<int>(size);
    for(int i = 0; i < size; i++)
    {
        heapQ->enqueue(i);
    }
    delete heapQ;
    cout << "Test 8 complete!" << endl;

    cout << "testing done!" << endl;

    return 0;
}

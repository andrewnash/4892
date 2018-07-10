/*
 * Copyright 2018 Jonathan Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdint>   // for size_t
#include <memory>
#include <cstring>


/**
 * A circular queue is a bounded queue that provides enqueue/dequeue operations,
 * can report the current depth of the queue, the number of spaces left in it
 * and whether or not it's empty.
 */
template<typename T>
class CircularQueue
{
public:
    /**
     * Construct a bounded circular queue of maximum length length.
     */
    CircularQueue(size_t length)
    {
        Q = new T[length];

        len = length;

        front = &Q[len -1]; //len - 1 = back bound of array
        back = &Q[len -1];
        arrayBack = &Q[len -1];
    }

    //! Copy constructor
    CircularQueue(const CircularQueue &orig)
    {
        *this = orig;
    }

    //! Move constructor
    CircularQueue(CircularQueue &&orig)
    {
        *this = std::move(orig);
    }

    //! Destructor
    ~CircularQueue()
    {
        front, back, arrayBack = nullptr; //prevent hanging pointer
        delete[] Q;
    }


    //! Copy assignment operator
    CircularQueue& operator= (const CircularQueue &orig)
    {
        if(Q != nullptr)
        {
            front, back, arrayBack = nullptr;
            delete[] Q;
        }
        count = orig.count;
        len = orig.len;
        Q = new T[len];
        std:memcpy(Q, orig.Q, len*(sizeof(T))); //copy elements
        arrayBack = &Q[len - 1];
        back = &Q[orig.back - orig.Q]; //ptr math to get positions of front/ back
        front = &Q[orig.front - orig.Q];
    }

    //! Move assignment operator
    CircularQueue& operator= (CircularQueue &&orig)
    {
        if(Q != nullptr) //delete our current queue
        {
            front, back, arrayBack = nullptr;
            delete[] Q;
        }
        count = 0;
        len = orig.len;
        Q = new T[len]; //create queue with new len from orig
        front = &Q[len - 1];
        back = &Q[len - 1];
        arrayBack = &Q[len - 1];
        while(!orig.empty()) //empty orig and fill out q
        {
            enqueue(orig.dequeue());
        }
    }



    //
    // Accessors:
    //
    //! How many elements are currently stored in the queue?
    
    size_t depth() const
    {
        return count;
    }

    //! Is the queue empty?
    bool empty() const
    {
        if(count == 0)
            return true;
        else
            return false;
    }
    //! Is the queue full?
    bool full() const
    {
        if(count == len)
        {
            return true;
        }
        return false;
    }

    /**
     * Get a reference to the next-to-be-dequeued element (i.e., the
     * least-recently-enqueued element) in the queue.
     *
     * @pre        assumes that the queue is not empty
     */
    const T& peek() const
    {
        return *front;
    }

    //
    // Mutators:
    //

    /**
     * Add an element to the queue, if there's space.
     *
     * If there isn't any more space in the queue, this method should simply
     * return false and not change the state of the queue.
     *
     * @returns    whether or not the item was successfully enqueued
     */
    bool enqueue(T value)
    {
        if(depth() == len) //check if full
        {
            return false;
        }
        *back = value;
        count ++;
        if(back == Q) //special case where we are at the end of the array and must circle to front
            back = arrayBack;
        else
            back--;
        return true;
    }

    /**
     * Remove the least-recently-enqueued element from the queue.
     *
     * @returns    the newly-dequeued element
     * @pre        assumes that the queue is not empty
     */
    T dequeue()
    {
        T temp = *front;
        if(front == Q)
            front = arrayBack;
        else
            front--;
        count --;
        return temp;
    }

private:
    T* Q = nullptr;
    size_t len = 0;
    T* front = nullptr;
    T* back = nullptr ;
    T* arrayBack = nullptr;
    int count = 0; //keep track how many array elements
};
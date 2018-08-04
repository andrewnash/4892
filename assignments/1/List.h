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

#include <iostream>
#include <cstdint>
#include <memory>

using namespace std;


template<typename T>
class List
{
public:

    class Node
    {
    public:
        Node( std::shared_ptr<Node> prev_,
              std::shared_ptr<Node> next_,
              T key_)
        {
            next = std::move(next_);
            prev = std::move(prev_);
            key = std::move(key_);
        }

        std::shared_ptr<Node> next;
        std::shared_ptr<Node> prev;
        T key;
    };


    //! A constant iterator over elements of the List.
    class const_iterator
    {
    public:
        const_iterator(std::shared_ptr<Node> node) //itr of node
        {
            current = node;
        }

        /**
         * The dereference operator.
         *
         * @returns   a reference to the "current" element
         */
        const T& operator*()
        {
            return current->key;
        }

        /**
         * Pre-increment operator (i.e., `++i`).
         *
         * This method increments the iterator and then returns a
         * reference to the newly-incremented iterator.
         *
         * @returns   a reference to this iterator, after incrementing
         */
        const_iterator& operator++()
        {
            current = current->next;
            return *this;
        }

        /**
         * Post-increment operator (i.e., `i++`).
         *
         * This method returns a copy of this iterator as it currently
         * is (i.e., pointing where it currently points) and _then_
         * increments itself.
         *
         * @param     ignored   this is only used to distinguish the two
         *                      increment operators (pre- and post-)
         *                      from each other: its value should be
         *                      ignored
         *
         * @returns   an iterator to the previously-current element
         */
        const_iterator operator++(int ignored)
        {
            auto prevNode = *this;
            current = current->next;
            return prevNode;
        }

        //! Is this iterator pointing at the same place as another one?
        bool operator== (const const_iterator& other) const
        {
            return current == other.current;
        }

        //! Is this iterator pointing at a different place from another?
        bool operator!= (const const_iterator& other) const
        {
            return current != other.current;
        }

        T get_node()
        {
            return current->key;
        }

        std::shared_ptr<Node> current = nullptr;

    };

    //! A mutable version of const_iterator (can modify list values)
    class iterator : public const_iterator
    {
    public:
        iterator(std::shared_ptr<Node> node):const_iterator(node)
        {
            current = node;
        }

        // Non-const overloads of const_iterator methods:
        T& operator*()
        {
            return current->key;
        }
        iterator& operator++()
        {
            current = current->next;
            return *this;
        }
        iterator operator++(int ignored)
        {
            auto prevNode = *this;
            current = current->next;
            return prevNode;
        }

        //! Is this iterator pointing at the same place as another one?
        bool operator== (const const_iterator& other) const
        {
            return current == other.current;
        }

        //! Is this iterator pointing at a different place from another?
        bool operator!= (const const_iterator& other) const
        {
            return current != other.current;
        }

        std::shared_ptr<Node> current;
    };


    //! Default constructor
    List()
    {
    }


    //! Copy constructor
    List(const List& other)
    {
        *this = other;
    }

    //! Move constructor
    List(List&& other)
    {
        head = std::move(other.head);
        tail = std::move(other.tail);
        size_ = other.size_;
    }

    //! Destructor
    ~List()
    {
//        auto i = head;
//        while(i->next)
//        {
//            i->prev = nullptr;
//        }
//        head, tail = nullptr;
    }

    //! Copy assignment operator
    List& operator= (const List& other)
    {
        //empty this list
       auto thisList = head;
       if(thisList)
       {
           while(thisList->next)
           {
               thisList->prev = nullptr;
           }
           head, tail = nullptr;
       }

       //fill this list with other list
        std::shared_ptr<Node> i = other.head;
        for(auto j = other.begin(); j != other.end(); j++)
        {
            T temp = i->key;
            push_back(temp);
            i = i->next;
        }
        return *this;
    }

    //! Move assignment operator
    List& operator= (List&& other)
    {
        head = std::move(other.head);
        tail = std::move(other.tail);
        size_ = other.size_;

        return *this;
    }


    //.;
    // Accessors:
    //
    //! How many elements are in this list?
    size_t size() const
    {
        return size_;
    }

    //! Is this list empty?
    bool empty() const
    {
        return size_ == 0;
    }

    //! Get an iterator to the beginning of the list
    iterator begin()
    {
        return iterator(head);
    }
    const_iterator begin() const
    {
        return const_iterator(head);
    }

    //! Get an iterator just past the end of the list
    iterator end()
    {
        return iterator(nullptr);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }


    //
    // Mutators:
    //
    //! Copy an element to the front of the list
    void push_front(const T& data)
    {
        insert(begin(), data);
    }

    //! Move an element to the front of the list
    void push_front(T&& data)
    {
        insert(begin(), std::move(data));
    }

    //! Copy an element to the back of the list
    void push_back(const T& data)
    {
        insert(iterator(tail), data);
    }

    //! Move an element to the back of the list
    void push_back(T&& data)
    {
        insert(iterator(tail), std::move(data));
    }

    /**
     * Copy an element into an arbitrary location.
     *
     * This method makes a copy of an element and inserts that copy into a
     * location pointed at by the given iterator. After insertion into a
     * list of n elements, the list should contain n+1 elements (i.e., no
     * existing element should be replaced).
     *
     * @returns   an iterator pointing at the newly-inserted element
     */
    iterator insert(iterator currentItr, const T& data)
    {
        auto temp = data;
        return insert(currentItr, std::move(temp));
    }

    /**
     * Move an element into an arbitrary location.
     *
     * This method inserts an element into a location pointed at by the
     * given iterator, using move semantics to avoid copies. After insertion
     * into a list of n elements, the list should contain n+1 elements
     * (i.e., no existing element should be replaced).
     *
     * @returns   an iterator pointing at the newly-inserted element
     */
    iterator insert(iterator itr, const T&& data)
    {
        size_++;

        //Create Head
        if(!head)
        {
            head = std::make_shared<Node>(nullptr, tail, std::move(data));
            return iterator(head);
        }
        //Create Tail
        else if(!tail)
        {
            tail = std::make_shared<Node>(head, nullptr, std::move(data));
            head->next = tail;
            return iterator(tail);
        }
        //Push Back
        else if(itr.current == tail)
        {
            auto newNode = tail;
            tail.reset(new Node(newNode, nullptr, std::move(data)));
            newNode->next = tail;
        }
        //Push Front
        else if(itr.current == head)
        {
            auto newNode = head;
            head.reset(new Node(nullptr, newNode, std::move(data)));
            newNode->prev = head;
        }
        //Normal Insert
        else
        {
            auto prev = itr.current->prev;
            auto next = itr.current;

            auto newNode = std::make_shared<Node>(std::move(prev), 
                                                std::move(next), 
                                                std::move(data));

            prev->next = std::move(newNode);
            next->prev = newNode;

            return iterator(newNode);
        }
    }

    //! Remove an element from an arbitrary location
    void erase(iterator itr)
    {
        auto prev = itr.current->prev;
        auto next = itr.current->next;

        next->prev = prev;
        prev->next = next;

        size_--;
    }

protected:
    // Add whatever you need to add here
    std::shared_ptr<Node> head = nullptr;
    std::shared_ptr<Node> tail = nullptr;
    size_t size_ = 0;
};
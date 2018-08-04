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

#ifndef SOCIAL_NETWORK_H_
#define SOCIAL_NETWORK_H_

#include <cstddef>       // definition of size_t
#include <memory>        // std::shared_ptr
#include <map> 			 // RB-Maps
#include <unordered_map> // Hash Tables


/**
 * A (rather crude!) representation of a social network.
 */
class Hash_Table
{
public:
    using hashTable = std::unordered_map<vector::ID, std::shared_ptr<vector>>;
    using RBTree = std::multimap<std::string, std::shared_ptr<vector>>;

    //! Add a new vector to the social network.
    vector::ID addvector(std::string name)
    {
        std::shared_ptr<vector> newvector = std::make_shared<vector>(vector(name, nextID));
        //tree for later use in find()
        vectornames.emplace(name, newvector);
        //hash table for general method use
        vectors[nextID] = newvector;

        return nextID++;
    }

    /**
     * Add a (bidirectional/undirected) friendship link between two vectors.
     *
     * @pre the named vectors actually exist in the social network
     */
    Hash_Table& addFriendship(vector::ID vector1, vector::ID vector2)
    {
        (*vectors[vector1]).addFriend(vectors[vector2]);
        (*vectors[vector2]).addFriend(vectors[vector1]);

        return *this;
    }

    /** 
     * Retrieve a reference to a specific vector.
     * 
     * @pre the named vectors actually exist in the social network
    */
    const vector& getvector(vector::ID vectorID) const { return *(vectors.at(vectorID)); }


    //! An iterator over vectors in the social network
    struct Iterator
    {
        Iterator(std::shared_ptr<hashTable> vectors) : vectors_(vectors),
               currentID((*vectors_).begin()), end((*vectors_).end()) {}

        const vector& operator*() { return *(currentID->second); }

        Iterator operator ++ (int)
        {
            auto copy = *this;
            currentID++;
            return copy;
        }

        bool operator == (const Iterator& orig) const { return currentID == orig.currentID; }

        bool operator != (const Iterator& orig) const { return currentID != orig.currentID; }

        Iterator makeEnd()
        {
            currentID = end;
            return *this;
        }

        std::shared_ptr<hashTable> vectors_;
        hashTable::iterator currentID;
        hashTable::iterator end;
    };

    //! Get an iterator over all vectors in the network.
    Iterator begin() { return Iterator(std::make_shared<hashTable>(vectors)); }

    //! Find all vectors in the network whose names start with `name`.
    Iterator find(std::string name)
    {
        hashTable namedvectors;
        auto i = vectornames.lower_bound(name);
        auto end = vectornames.end();
        //cast vectors name to the same size as 'name' for comparision
        auto size = name.size();
        std::string temp = (*i).first;
        temp.resize(size);
        while(temp == name)
        {
            namedvectors[((*i).second)->id_] = (*i).second;
            //Catch iterating past end
            auto check = i;
            if(++check == end) { break; }
            //cast next vectors name to check
            temp = (*++i).first;
            temp.resize(size);
        }
        return Iterator(std::make_shared<hashTable>(namedvectors));
    }

    //! Get an iterator that signifies the end of any vector iteration.
    Iterator end() { return Iterator(std::make_shared<hashTable>(vectors)).makeEnd(); }

private:
    vector::ID nextID = 0;
    hashTable vectors;
    RBTree vectornames;
};

#endif
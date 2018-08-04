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

#ifndef USER_H_
#define USER_H_

#include <cstddef>          // for definition of size_t
#include <memory>           // std::shared_ptr
#include <queue>            // Queues
#include <unordered_map>    // Hash Tables


/**
 * Representation of a social network user.
 */
class User
{
public:
    using ID = size_t;
    using hashTable = std::unordered_map<User::ID, std::shared_ptr<const User>>;

    
    User(std::string name, ID id) : name_(name), id_(id) {}

    //! What is this user's ID?
    ID id() const { return id_; }

    //! How many friends does this user have?
    size_t degree() const { return friends.size(); }

    bool operator == (const User& orig) const { return id_ == orig.id_; }

    bool operator != (const User& orig) const { return id_ != orig.id_; }

    //!Bi-Directional Breath First Search
    size_t BI_BFS(std::queue<User> Qvisited1, 
                std::queue<User> Qvisited2, 
                std::unordered_map<User::ID, bool> visited1,
                std::unordered_map<User::ID, bool> visited2, 
                size_t length) const
    {
        size_t result  = 0;
        int flag = 1;
        while(!Qvisited1.empty() and !Qvisited2.empty())
        {
            //flag accounts for first case of length 1
            result = BFS(Qvisited1, visited1, visited2, length, flag);
            if(result) { return result; }

            result = BFS(Qvisited2, visited2, visited1, length, 0);
            if(result) { return result; }
            flag = 0;
        }
        //there is no connection between friends
        return SIZE_MAX;
    }


    //!Preform one Iteration of a Breath First Search
    size_t BFS(std::queue<User> &Qvisited, 
            std::unordered_map<User::ID, bool> &map1,
            std::unordered_map<User::ID, bool> &map2, 
            size_t &length, 
            int flag) const
    {
        length++;
        auto Qsize = Qvisited.size();
        size_t result = 0;
        if(Qsize > 0)
        {
            result = BFS_Friends(Qvisited, map1, map2, length, flag);
            if(result) { return result; }

            result = BFS_Friends_Friends(Qvisited, map1, map2, length, flag);
            if(result) { return result; }
        }
        return 0;
    }

    //!Search friends for path
    size_t BFS_Friends(std::queue<User> &Qvisited,  
                    std::unordered_map<User::ID, bool> &map1,
                    std::unordered_map<User::ID, bool> &map2, 
                    size_t &length, 
                    int flag) const
    {
        auto Qsize = Qvisited.size();
        User currentUser = Qvisited.front();
        
        //iterate through queue and check if any imitate friends are goal friend
        for(auto i = 0; i < Qsize; i++)
        {
            currentUser = Qvisited.front();
            Qvisited.pop();
            map1[currentUser.id_] = 1;
            //check if visited yet (path found)
            if(map2[currentUser.id_] == 1)
            {
                return length - flag;
            }
            Qvisited.push(currentUser);
        }
        return 0;
    }

    //!Search friends of friends for path
    size_t BFS_Friends_Friends(std::queue<User> &Qvisited,  
                            std::unordered_map<User::ID, bool> &map1,
                            std::unordered_map<User::ID, bool> &map2, 
                            size_t &length, 
                            int flag) const
    {
        auto Qsize = Qvisited.size();
        User currentUser = Qvisited.front();
        //iterate through friends friends and check if any are goal friend
        for(auto i = 0; i < Qsize; i++)
        {
            currentUser = Qvisited.front();
            Qvisited.pop();
            for(auto j: currentUser.friends)
            {
                //Check if visited yet (path found)
                if(map2[j.first] == 1)
                {
                    return length + 1 - flag;
                }
                //if we haven't visited this friend yet, add them to queue to be visited
                if(map1[j.first] == 0)
                {
                    map1[j.first] = 1;
                    Qvisited.push(*(j.second));
                }
            }
        }
        return 0;
    }

    /**
     * What is the shortest path to the given User from this one?
     *
     * @returns   the number of friend links between this User and that
     *            one, or SIZE_MAX if there is no connection between them
     */
    size_t distance(const User& goalFriend) const
    {
        //we are the goal friends so 0
        if(*this == goalFriend) { return 0; }

        size_t length = 1;
        std::queue<User> Qvisited1;
        std::queue<User> Qvisited2;

        //keep track of visited users by our user and goal user
        std::unordered_map<User::ID, bool> visited1;
        std::unordered_map<User::ID, bool> visited2;

        //Users have obviously already visited themselves
        visited1[id_] = 1;
        visited2[goalFriend.id_] = 1;

        //fill Queue with initial friends
        for(auto i: friends)
        {
            Qvisited1.push(*i.second);
        }
        for(auto i: goalFriend.friends)
        {
            Qvisited2.push(*i.second);
        }

        return BI_BFS(Qvisited1, Qvisited2, visited1, visited2, length);
    }

    //! Make this User friends with another User
    void addFriend(const User& newfriend)
    {
        //catch user adding itself as a friends
        if(id_ != (newfriend).id_)
        {
            friends[(newfriend).id_] = std::make_shared<const User>(newfriend);
        }
    }
    void addFriend(const std::shared_ptr<User> newfriend)
    {
        //catch user adding itself as a friends
        if(id_ != (*newfriend).id_)
        {
            friends[(*newfriend).id_] = newfriend;
        }
    }


    //! An iterator that can iterate over all of a User's friends
    struct FriendIterator
    {
        FriendIterator(std::shared_ptr<hashTable> friends) : 
                    friends_(friends), currentID((*friends_).begin()),
                    end((*friends_).end()) {}

        const User& operator*() { return *(currentID->second); }

        FriendIterator operator ++ (int)
        {
            auto copy = *this;
            currentID++;
            return copy;
        }

        bool operator == (const FriendIterator& orig) const { return currentID == orig.currentID; }

        bool operator != (const FriendIterator& orig) const { return currentID != orig.currentID; }

        FriendIterator makeEnd()
        {
            currentID = end;
            return *this;
        }

        std::shared_ptr<hashTable> friends_;
        hashTable::iterator currentID;
        hashTable::iterator end;
    };

    //! Get an iterator that will iterate over this User's friends
    FriendIterator begin() const { return FriendIterator(std::make_shared<hashTable>(friends)); }

    /**
     * Get an iterator that will iterate over this User's friends
     * as well as **their** friends.
     */
    FriendIterator friendsOfFriends() const
    {
        hashTable friendsFriends;
        //iterate through all friends and append to hash table
        for(auto i: friends)
        {
            friendsFriends[i.first] = i.second;
            //iterate through all friends friends and append to hash table
            for(auto j: (*(i.second)).friends)
            {
                friendsFriends[j.first] = j.second;
            }
        }
        //remove this user from list
        friendsFriends.erase(id_);
        return FriendIterator(std::make_shared<hashTable>(friendsFriends));
    }

    //! Get an iterator that signifies the end of any friend iteration.
    FriendIterator end() const { return FriendIterator(std::make_shared<hashTable>(friends)).makeEnd(); }

private:
    friend class SocialNetwork;
    ID id_;
    std::string name_;
    hashTable friends;
};

#endif

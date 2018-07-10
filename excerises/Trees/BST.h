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

#include <cassert>      // tbh idk what this does
#include <cstddef>      // for definition of size_t
#include <functional>   // std::function
#include <memory>       // std::unique_ptr
#include <iostream>     // gotta print somehow
#include <vector>       // vectors



template<typename T, typename Comparator = std::less<T>>
class BinarySearchTree
{
private:

    struct Node
    {
        // Did you know that structs can have methods too? Yes I did.
        Node(T &&value)
            : element_(std::move(value)), count_(1)
        {}

        void printDot(int space)
        {
            //root case
            if(!this)
                return;

            //increase distance between levels
            space += 2;

            //process right children first
            right_->print(space);

            //print current node after space
            printf("\n");
            for(int i = 0; i < space; i++)
                printf(" ");
            std::cout << element_ << "\n";

            //process left children
            left_->print(space);
        }

        bool contains(const T& n) const
        {
            bool L = false;
            bool R = false;
            //recursion through entire tree incase comparator breaks
            if(right_)
            {
                R = right_->contains(n);
            }
            if(left_)
            {
                L = left_->contains(n);
            }
            //found element
            if(element_ == n || L || R)
            {
                return true;
            }
            return false;
        }

        //leaf nodes have no children
        bool leaf()
        {
            return !right_ && !left_;
        }

        Node& min()
        {
            if(!left_)
            {
                return *this;
            }
            return left_->min();
        }

        Node& max()
        {
            if(!right_)
            {
                return *this;
            }
            return right_->max();
        }

        //This function is stupid and needless
        T takeMin();

        size_t maxDepth() const
        {
            if(!this || (!left_ && !right_))
            {
                return 0;
            }

            //compute the depth of each subtree
            auto lDepth = left_->maxDepth();
            auto rDepth = right_->maxDepth();

            //pick larger subtree
            if(lDepth > rDepth)
            {
                return(lDepth + 1);
            }
            return(rDepth + 1);
        }

        void print(std::ostream &cAnderson, int space)
        {
            //root case
            if(!this)
                return;

            //increase distance between levels
            space += 2;

            //process right children first
            right_->print(cAnderson, space);

            //print current node after space
            printf("\n");
            for(int i = 0; i < space; i++)
                printf(" ");
            cAnderson << element_ << "\n";

            //process left children
            left_->print(cAnderson, space);
        }

        T element_;
        size_t count_ = 0;
        std::shared_ptr<Node> left_ = nullptr;
        std::shared_ptr<Node> right_ = nullptr;
    };

    /**
    * Internal implementation of recursive insert.
    *
    * @param   value      the value to insert
    * @param   node       the root of the (sub-)tree being inserted into;
    *                     may be null if the (sub-)tree is empty
    */
    void insert(T &&value, std::shared_ptr<Node> &node)
    {
        //no root
        if(!node)
        {
            node.reset(new Node(std::move(value)));
        }
        //found element already existing
        else if(node->element_ == value)
        {
            node->count_++;
            return;
        }
        //traverse less
        else if(compare_(value, node->element_))
        {
            if(node->left_ != nullptr)
            {
                insert(std::move(value), node->left_);
            }
            else
            {
                node->left_.reset(new Node(std::move(value)));
            }
        }
        //traverse greater
        else
        {
            if(node->right_ != nullptr)
            {
                insert(std::move(value), node->right_);
            }
            else
            {
                node->right_.reset(new Node(std::move(value)));
            }
        }
    }

    /**
    * Internal implementation of recursive removal.
    *
    * @param   value      the value to remove
    * @param   node       the root of the (sub-)tree being inserted into;
    *                     may be null if the (sub-)tree is empty
    */
    bool remove(const T &value, std::shared_ptr<Node> &node)
    {
        bool L = false;
        bool R = false;
        bool Me = false;

        //verify we can traverse
        if(!node || !contains(value))
        {
            return false;
        }
        //traverse entire tree incase comparitor breaks
        if(node->left_)
        {
            L = remove(value, node->left_);
        }
        if(node->right_)
        {
            R = remove(value, node->right_);
        }
        //node removal
        if(value == node->element_)
        {
            if(node->count_ > 1)
            {
                node->count_--;
            }

            //no children
            else if(node->leaf())
            {
                node = nullptr;
            }
            //two children
            else if(node->left_ && node->right_)
            {
                node->element_ = node->right_->min().element_;
                remove(node->element_, node->right_);
            }
            //one child
            else
            {
                node.swap(node->left_ ? node->left_ : node->right_);
            }
            Me = true;
        }
        if(Me || L || R)
        {
            return true;
        }
        return false;
    }

    Comparator compare_;


public:

    BinarySearchTree()
    {}

    enum class Traversal
    {
        PreOrder,
        InOrder,
        PostOrder,
    };


    //! Does this tree contain the given value?
    bool contains(const T &value)
    {
        return(!empty() && root_->contains(value));
    }

    size_t maxDepth() const
    {
        if(empty())
        {
            return 0;
        }

        return root_->maxDepth();
    }

    //! Is this tree empty?
    bool empty() const
    {
        return(!root_);
    }

    //! Insert a new value into the appropriate place in the tree.
    void insert(T value)
    {
        insert(std::move(value), root_);
    }

    /**
    * Find the minimum value in the tree.
    *
    * @pre   tree is not empty
    */
    const T& min() const
    {
        assert(root_);
        return root_->min().element_;
    }

    /**
    * Find the minimum value in the tree.
    *
    * @pre   tree is not empty
    */
    const T& max() const
    {
        assert(root_);
        return root_->max().element_;
    }

    /**
    * Remove a value (if it exists) from the tree.
    *
    * @returns   whether or not anything was found to remove
    */
    bool remove(const T &&value)
    {
        return remove(value, root_);
    }


    void print(std::ostream &cAnderson)
    {
        root_->print(cAnderson, 0);
    }


    class Iterator
    {
    public:
        Iterator(Traversal travelType, 
                 std::shared_ptr<Node> treeRoot, 
                 std::shared_ptr<Node> sentinelNode, 
                 Comparator comparee)
        {
            root = treeRoot;
            type = travelType;
            end = sentinelNode;
            compare = comparee;
            
            //set itr starting positions
            position = root;
            switch(type)
            {
            case Traversal::InOrder:
                //find min
                while(position->left_)
                {
                    if(!position->leaf())
                    {
                        visited.push_back(position);
                    }
                    position = position->left_;
                }
                break;
            case Traversal::PostOrder:
                //traverse left over right 
                while(!position->leaf())
                {
                    while(position->left_)
                    {
                        if(!position->leaf())
                        {
                            visited.push_back(position);
                        }
                        position = position->left_;
                    }
                    if(position->right_)
                    {
                        visited.push_back(position);
                        position = position->right_;
                    }
                }
                break;
            }
        }

        T& operator*()
        {
            //incase we accidently try and print the end
            if(position == end)
            {
                return root->element_;
            }
            return position->element_;
        }

        // Is this iterator pointing at the same place as another one?
        bool operator== (Iterator& otherItr)
        {
            return position == otherItr.position;
        }

        // Is this iterator pointing at a different place from another?
        bool operator!= (const Iterator& otherItr) const
        {
            return position != otherItr.position;
        }

        //Pre-increment operator (i.e., `++i`)
        Iterator& operator++()
        {
            //overide so we dont iterate past end
            if(position == end)
            {
                return *this;
            }
            switch(type)
            {
            case Traversal::PreOrder:
                preorder();
                break;
            case Traversal::InOrder:
                inorder();
                break;
            case Traversal::PostOrder:
                postorder();
                break;
            }
            return *this;
        }

        //Post-increment operator (i.e., `i++`)
        Iterator& operator++(int ignored)
        {
            //overide so we dont iterate past end
            if(position == end)
            {
                return *this;
            }
            //return what itr previously was, hence post-increment
            Iterator previous = *this;
            switch(type)
            {
            case Traversal::PreOrder:
                preorder();
                break;
            case Traversal::InOrder:
                inorder();
                break;
            case Traversal::PostOrder:
                postorder();
                break;
            }
            return previous;
        }

        void preorder()
        {
            if(!position->leaf())
            {
                visited.push_back(position);
            }
            //Traverse left over right
            if(position->left_)
            {
                position = position->left_;
            }
            else if(position->right_)
            {
                position = position->right_;
            }
            //we are at a leaf node
            else
            {
                //traverse up, note this loop will always exit as visited will eventually become empty
                while(1)
                {
                    //case for last node
                    if(visited.empty())
                    {
                        position = end;
                        break;
                    }
                    //traverse back up tree
                    else if(!compare(position->element_, visited.back()->element_))
                        visited.pop_back();
                    //visit next leaf node to right
                    else if(visited.back()->right_)
                    {
                        position = visited.back()->right_;
                        break;
                    }
                    else
                    {
                        visited.pop_back();
                    }
                }
            }
        }

        void inorder()
        {
            //check for right child
            if(position->right_)
            {
                visited.push_back(position);
                position = position->right_;
                //get min of right child
                while(position->left_)
                {
                    visited.push_back(position);
                    position = position->left_;
                }
            }
            else
            {
                //traverse up, note this loop will always exit as visited will eventually become empty
                while(1)
                {
                    //case for last node
                    if(visited.empty())
                    {
                        position = end;
                        break;
                    }
                    //if we are <= our parent, traverse up
                    else if(!compare(position->element_, visited.back()->element_))
                    {
                        visited.pop_back();
                    }
                    else
                    {
                        position = visited.back();
                        break;
                    }
                }
            }
        }

        void postorder()
        {
            //case for last node
            if(visited.empty())
            {
                position = end;
            }
            //check if we are left node
            else if(visited.back()->left_ == position)
            {
                //if so traverse down right of our parent
                if(visited.back()->right_)
                {
                    position = visited.back()->right_;
                    while(!position->leaf())
                    {
                        while(position->left_)
                        {
                            visited.push_back(position);
                            position = position->left_;
                        }
                        if(position->right_)
                        {
                            visited.push_back(position);
                            position = position->right_;
                        }
                    }
                }
                //case for no children
                else
                {
                    position = visited.back();
                    visited.pop_back();
                }
            }
            //case if we are right node
            else
            {
                position = visited.back();
                visited.pop_back();
            }
        }

        //used to make end
        Iterator makeEnd()
        {
            position = end;
            return *this;
        }

        std::shared_ptr<Node> end = nullptr; //end sentinel
        std::shared_ptr<Node> root = nullptr; //root for future reference
        std::vector<std::shared_ptr<Node>> visited; //visited nodes for easier traversal (that arn't leafs)
        std::shared_ptr<Node> position = nullptr;  //the iterators current position
        Traversal type;
        Comparator compare;
    };

    /**
    * Returns an iterator that can be used to traverse the tree in the given order.
    *
    * This iterator should visit every node in the tree exactly once, after which
    * it should test equal to the iterator returned from `end()`.
    */
    Iterator begin(Traversal type) 
    {
        Iterator iter(type, root_, sentinel, compare_);
        return iter;
    }
    /**
    * The end of a tree traversal.
    *
    * The iterator returned by this method should be usable as the end-of-iteration
    * marker for any iterator on this tree, whether it was traversing the tree in
    * pre-, in- or post-order.
    */
    Iterator end()
    {
        //inputs dont matter because we set this itr to end
        Iterator endItr(Traversal::PreOrder, root_, sentinel, compare_);
        endItr.makeEnd();
        return endItr;
    }

    std::shared_ptr<Node> sentinel; //sentinel for end node
    std::shared_ptr<Node> root_ = nullptr;
};


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

#include "BST.h"

#include <iostream>

int main()
{
    BinarySearchTree<int> bst;

    bst.insert(25);
    bst.insert(15);
    bst.insert(10);
    bst.insert(22);
    bst.insert(12);
    bst.insert(4);
    bst.insert(18);
    bst.insert(24);
    bst.insert(50);
    bst.insert(35);
    bst.insert(31);
    bst.insert(44);
    bst.insert(70);
    bst.insert(66);
    bst.insert(90);



    std::cout << "min value: " << bst.min() << "\n";
    std::cout << "max value: " << bst.max() << "\n";



    auto a = bst.begin(Traversal::PreOrder);
    auto b = bst.end();

    std::cout << "total nodes is: " << b - a << std::endl;


    std::cout << "PreOrder: ";
    for(auto i =  bst.begin(Traversal::PreOrder); i !=  bst.end(); i++)
    {
        std::cout << *i << ", ";
    }

    std::cout << std::endl << "InOrder: ";
    for(auto i =  bst.begin(Traversal::InOrder); i !=  bst.end(); i++)
    {
        std::cout << *i << ", ";
    }

    std::cout << std::endl << "PostOrder: ";
    for(auto i =  bst.begin(Traversal::PostOrder); i !=  bst.end(); i++)
    {
        std::cout << *i << ", ";
    }

    std::cout << std::endl << std::endl << std::endl;
    bst.print(std::cout);
//    std::cout << std::endl << std::endl << "attempting to remove 10 : " << bst.remove(10) << std::endl << std::endl;
//    bst.print(std::cout);
//
//    std::cout << std::endl << std::endl << "attempting to remove 14 : " << bst.remove(14) << std::endl << std::endl;
//    bst.print(std::cout);
//
//    std::cout << std::endl << std::endl << "attempting to remove 7 : " << bst.remove(7) << std::endl << std::endl;
//    bst.print(std::cout);

    return 0;
}

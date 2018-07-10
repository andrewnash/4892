#include <iostream>
#include <vector>
#include <memory>

/* Q1: Unique pointers only allow one pointer to point to the object (or tree node in this case)
 * this works well becuase each child node should only have one pointer and no more. This would
 * be counter intutative with a shared pointer as this allowed multipe pointers to point to the
 * same tree node, which is exactly what we don't want
 */


template<typename T>
class Tree
{
public:
	Tree()
	{
		std::shared_ptr<Node> root(new Node()); //create tree
	}

	/**
	 * Set the value of the tree's root node.
	 */
	Tree& setRoot(T value)
	{
		*root = value;
	}

	/**
	 * Add a leaf node to the top level of this tree.
	 */
	Tree& addChild(T value)
	{
		root->child = new Node();
		root->child->value = value;
	}

	/**
	 * Add a subtree to the top level of this tree, using move
	 * semantics to "steal" the subtree's nodes.
	 */
	Tree& addSubtree(Tree<T>&& node)
	{
		setRoot(std::move(node));
	}


	void visit(const T &value)

	{
		static size_t i = 0;
		std::cout << "Node " << i++ << ": " << value << "\n";
	}

private: 
	struct Node
	{
		Node()
		{
			parent = nullptr;
			child = nullptr; //Link to child node for future inseration
		}

		T value;
		std::shared_ptr<Node> parent;
		std::shared_ptr<Node> child;
	};

	std::shared_ptr<Node> root;
};

int main()
{
	Tree<int> tree;
	tree.addChild(5);
	return 0;
}
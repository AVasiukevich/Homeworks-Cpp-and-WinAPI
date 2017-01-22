#include <iostream>

enum color { BLACK, RED };

template <class T>
class RedBlackTree
{
	class Node
	{
	public:
		color col;
		Node* leftPtr;
		Node* rightPtr;
		Node* parent;
		T data;
		Node(const T& data_, Node* par = nullptr, color col_ = BLACK, Node* left = nullptr, Node* right = nullptr)
			:data{ data_ }, col{ col_ }, leftPtr{ left }, rightPtr{ right }, parent{ par }
		{}
	};
	Node* root = nullptr;
	/*Standard methods Tree*/
	void add(const T& data_, Node*& ptr, Node* par = nullptr)
	{
		if (ptr)
		{
			if (data_ < ptr->data) {
				add(data_, ptr->leftPtr, ptr);
			}
			else
				add(data_, ptr->rightPtr, ptr);
		}
		else {
			ptr = new Node(data_, par, RED);
			balancing(ptr);
		}
	}
	void show(const Node* node, std::ostream& os) const
	{
		if (node)
		{
			show(node->leftPtr, os);
			if (node->col == RED)
				os << node->data << " - " << "RED" << std::endl;
			else
				os << node->data << " - " << "BLACK" << std::endl;
			show(node->rightPtr, os);
		}
	}
	void copyAll(Node* ptr, Node*& ptr_new)
	{
		add(ptr->data, ptr_new);

		if (ptr->leftPtr)
			copyAll(ptr->leftPtr, ptr_new->leftPtr);
		if (ptr->rightPtr)
			copyAll(ptr->rightPtr, ptr_new->rightPtr);
	}
	void deleteAll(Node* ptr)
	{
		if (root)
		{
			if (ptr->leftPtr)
				deleteAll(ptr->leftPtr);
			if (ptr->rightPtr)
				deleteAll(ptr->rightPtr);
			delete ptr;
		}
	}
	Node* search(const T& data_, Node*& ptr) const
	{
		if (ptr) {
			if (data_ == ptr->data)
				return ptr;
			else if (data_ < ptr->data && ptr->leftPtr)
				return search(data_, ptr->leftPtr);
			else if (data_ > ptr->data && ptr->rightPtr)
				return search(data_, ptr->rightPtr);
		}
		return nullptr;
	}
	/*methods for RedBlackTree*/
	void balancing(Node* ptr) // for add and union
	{
		Node* father = ptr->parent;
		Node* grandf = nullptr;
		Node* uncle = nullptr;
		color uncle_color = BLACK;

		if (father)
			grandf = father->parent;
		if (grandf)
		{
			if (grandf->leftPtr == father)
				uncle = grandf->rightPtr;
			else
				uncle = grandf->leftPtr;
		}
		if (uncle)
			uncle_color = uncle->col;

		if (father == nullptr) // start balancing
		{
			std::cout << "tut 1" << std::endl;
			ptr->col = BLACK;
		}
		else if (father->col == BLACK) {
			std::cout << "tut 2" << std::endl;
			return;
		}
		else if (uncle_color == RED && father->col == RED)
		{
			std::cout << "tut 3" << std::endl;
			father->col = BLACK;
			if (uncle)
				uncle->col = BLACK;
			grandf->col = RED;
			balancing(grandf);
		}
		else if (father->col == RED && uncle_color == BLACK)
		{
			std::cout << "tut 4" << std::endl;
			if (grandf->leftPtr == father)
			{
				if (father->rightPtr == ptr)
				{
					turnLeft(father);
					father = ptr;
				}
				turnRight(grandf);
			}
			else
			{
				if (father->leftPtr == ptr)
				{
					turnRight(father);
					father = ptr;
				}
				turnLeft(grandf);
			}
			father->col = BLACK;
			grandf->col = RED;
		}
	}
	void turnRight(Node* ptr)
	{
		Node* father = ptr->parent;
		Node* child = ptr->leftPtr;

		if (father == nullptr)
			root = child;

		child->parent = father;
		if (father)
		{
			if (father->leftPtr == ptr)
				father->leftPtr = child;
			else
				father->rightPtr = child;
		}

		ptr->leftPtr = child->rightPtr;
		if (child->rightPtr)
			child->rightPtr->parent = ptr;

		child->rightPtr = ptr;
		ptr->parent = child;
	}
	void turnLeft(Node* ptr)
	{
		Node* father = ptr->parent;
		Node* child = ptr->rightPtr;

		if (father == nullptr)
			root = child;

		child->parent = father;
		if (father)
		{
			if (father->leftPtr == ptr)
				father->leftPtr = child;
			else
				father->rightPtr = child;
		}

		ptr->rightPtr = child->leftPtr;
		if (child->leftPtr)
			child->leftPtr->parent = ptr;

		child->leftPtr = ptr;
		ptr->parent = child;
	}
	void delete_check(Node* del)
	{
		Node* father = del->parent;
		Node* child = del->leftPtr ? del->leftPtr : del->rightPtr;
		color col_child = BLACK;
		if (child)
		{
			child->parent = father;
			col_child = child->col;
		}
		if (father)
		{
			if (father->leftPtr == del)
				father->leftPtr = child;
			else
				father->rightPtr = child;
		}
		else {
			root = child;
			if (child)
				child->col = BLACK;
			return;
		}
		if (del->col == BLACK && col_child == RED)
			child->col = BLACK;
		else if (del->col == BLACK)
			del_balancing(father, del);
	}
	void del_balancing(Node* f_del, Node* del) // for delete
	{
		Node* bro = f_del->leftPtr == del ? f_del->rightPtr : f_del->leftPtr;
		Node* bro_child_1 = bro->leftPtr;
		Node* bro_child_2 = bro->rightPtr;
		color col_bro_child_1 = BLACK;
		color col_bro_child_2 = BLACK;

		if (bro_child_1)
			col_bro_child_1 = bro_child_1->col;
		if (bro_child_2)
			col_bro_child_2 = bro_child_2->col;

		if (f_del == nullptr) // start balancing
			return;
		else if (bro->col == RED)
		{
			f_del->col = RED;
			bro->col = BLACK;
			if (f_del->leftPtr == del)
				turnLeft(f_del);
			else
				turnRight(f_del);

			del_balancing(f_del, del);
			return;
		}
		else if (col_bro_child_1 == BLACK && col_bro_child_2 == BLACK)
		{
			bro->col = RED;
			if (f_del->col == BLACK)
				del_balancing(f_del->parent, f_del);
			else
				f_del->col = BLACK;
		}
		else if (col_bro_child_1 == RED && col_bro_child_2 == BLACK && f_del->leftPtr == del)
		{
			bro->col = RED;
			if (bro_child_1)
				bro_child_1->col = BLACK;
			turnRight(bro);
			bro = bro_child_1;
			bro_child_2 = bro->rightPtr;
		}
		else if (col_bro_child_2 == RED && col_bro_child_1 == BLACK && f_del->rightPtr == del)
		{
			bro->col = RED;
			if (bro_child_2)
				bro_child_2->col = BLACK;
			turnLeft(bro);
			bro = bro_child_2;
			bro_child_1 = bro->leftPtr;
		}

		if (f_del->leftPtr == del)
		{
			turnLeft(f_del);
			if (bro_child_2)
				bro_child_2->col = BLACK;
		}
		else
		{
			turnRight(f_del);
			if (bro_child_1)
				bro_child_1->col = BLACK;
		}
		bro->col = f_del->col;
		f_del->col = BLACK;
	}
	int max_top() const
	{
		if (root)
		{
			Node* curr_Max = root;
			while (curr_Max->rightPtr)
				curr_Max = curr_Max->rightPtr;
			return curr_Max->data;
		}
		return 0;
	}
	void plus_tree(Node*& obj_add, Node*& p, int hei)
	{
		Node* curr = root;
		Node* needed = nullptr;
		while (curr)
		{
			if (curr->col == BLACK && height(curr) == hei)
				needed = curr;
			curr = curr->rightPtr;
		}
		p->parent = needed->parent;
		needed->parent->rightPtr = p;
		p->leftPtr = needed;
		needed->parent = p;
		p->rightPtr = obj_add;
		obj_add->parent = p;
		balancing(p);
		obj_add = nullptr;
		p = nullptr;
	}

public:
	template <class T>
	friend std::ostream& operator<<(std::ostream&, const RedBlackTree<T>& obj);
	RedBlackTree() = default;
	RedBlackTree(const T& data_)
		:root{ new Node(data_) }
	{}
	RedBlackTree(const T& data_, color col)
		:root{ new Node(data_, nullptr, col) }
	{}
	RedBlackTree(const RedBlackTree& obj)
	{
		if (obj.root)
			copyAll(obj.root, root);
	}
	RedBlackTree& operator=(const RedBlackTree& obj)
	{
		if (&obj != this)
		{
			if (root)
				deleteAll(root);
			root = nullptr;
			copyAll(obj.root, root);
		}
		return *this;
	}
	void add(const T& data_)
	{
		if (!root)
			root = new Node(data_);
		else
			add(data_, root);
	}
	bool search(const T& data_) const
	{
		if (search(data_, root))
			return true;

		return false;
	}
	bool new_delete(const T& data_)
	{
		Node* del = search(data_, root);
		if (del)
		{
			if (del->leftPtr && del->rightPtr)
			{
				Node* curr = del->leftPtr;
				if (curr->rightPtr)
					while (curr->rightPtr)
						curr = curr->rightPtr;

				del->data = curr->data;
				delete_check(curr);
				del = curr;
			}
			else
				delete_check(del);

			delete del;
			return true;
		}
		return false;
	}
	int height(Node* r = nullptr) const
	{
		Node* top = r ? r : root;
		int count = 0;
		while (top->rightPtr)
		{
			if (top->rightPtr->col == BLACK)
				++count;
			top = top->rightPtr;
		}
		return count;
	}
	void unionTree(RedBlackTree& obj, RedBlackTree& peak)
	{
		Node*& p = peak.root;
		Node*& obj_add = obj.root;
		int max_this = max_top();
		int max_add = obj.max_top();
		if ((max_this <= p->data && p->data <= max_add) || (max_add <= p->data && p->data <= max_this))
		{
			int top = height();
			int top_2 = obj.height();
			if (top > top_2)
				plus_tree(obj_add, p, top_2);
			else
				obj.plus_tree(root, p, top);
		}
		else
			std::cout << "The join condition is not fulfilled" << std::endl;
	}
	~RedBlackTree()
	{
		deleteAll(root);
		root = nullptr;
	}
};
template <class T>
std::ostream& operator<<(std::ostream& os, const RedBlackTree<T>& obj)
{
	if (obj.root)
		obj.show(obj.root, os);
	else
		os << "Tree null!" << std::endl;

	return os;
}

int main()
{
	RedBlackTree<int> tr;
	tr.add(-7);
	std::cout << tr << std::endl;
	tr.add(-16);
	std::cout << tr << std::endl;
	tr.add(0);
	std::cout << tr << std::endl;
	tr.add(-88);
	std::cout << tr << std::endl;
	tr.add(-5);
	std::cout << tr << std::endl;
	tr.add(8);
	std::cout << tr << std::endl;
	tr.add(-2);
	std::cout << tr << std::endl;
	std::cout << tr.new_delete(-7) << std::endl;
	std::cout << tr << std::endl;
	std::cout << tr.new_delete(0) << std::endl;
	std::cout << tr << std::endl;
	return 0;
}
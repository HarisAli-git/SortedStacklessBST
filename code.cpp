#include <iostream>
using namespace std;
template<class T>
class Bnode;
template <class T>
class SortedStacklessBST
{
	Bnode<T>* root;
	bool IsSuccessor;
public:
	bool IsLeafBalance() // returns true if all the leaves of the tree are on the same level
	{
		int lvl = 0, leaflvl = 0;
		return IsLeafBalance(root, lvl, leaflvl); // call the wrapper function
	}
	bool IsLeafBalance(Bnode<T>* r, int lvl, int &leaflvl) // recursive wrapper function
	{
		if (r == NULL) // base case
			return true;
		if (r->right == NULL && r->left == NULL) // if it is leaf node
		{
			if (leaflvl == 0) // if this is first leaf occurrences
			{
				leaflvl = lvl; // then assign the level to the leaflvl
				return true;
			}
			return (lvl == leaflvl); // else, compare with previous leaf level and return true/false
		}
		// check both left & right sub-tree recursively
		return IsLeafBalance(r->left, lvl + 1, leaflvl) && IsLeafBalance(r->right, lvl + 1, leaflvl); // call the recursive function first of left and then right sub-tree, and then return their AND
	}
	void ReverseOder() // reverses the nextInOrder depending on value of IsSucessor
	{
		if (root)
		{
			if (IsSuccessor)
			{
				Bnode<T>* temp = get_min_successor(root);
				temp = ReverseOder(temp);
				IsSuccessor = false;
			}
			else
			{
				Bnode<T>* temp = get_max_predecessor(root);
				temp = ReverseOder(temp);
				IsSuccessor = true;
			}
		}
		else
			cout << "\nTree is Empty!";
	}
	Bnode<T>* ReverseOder(Bnode<T>* r) //  ReverseOder wrapper function
	{
		if (r == NULL)
			return NULL;
		if (r->nextInOrder == NULL)
			return r;
		Bnode<T>* r1 = ReverseOder(r->nextInOrder); // nextInOrder pointers reversed recusively
		r1->nextInOrder = r;
		r->nextInOrder = NULL;
		return r;
	}
	void print() // prints the data depending on IsSuccessor value
	{
		if (root)
		{
			if (IsSuccessor)
			{
				Bnode<T>* temp = get_min_successor(root);
				print(temp);
			}
			else
			{
				Bnode<T>* temp = get_max_predecessor(root);
				print(temp);
			}
		}
		else
			cout << "\nTree is Empty!";
	}
	void print(Bnode<T> const* r) // print wrapper function
	{
		while (r)
		{
			cout << r->data << ' ';
			r = r->nextInOrder;
		}
		cout << endl;
	}
	void print(T Low, T High)
	{
		if (root)
		{
			if (IsSuccessor)
			{
				Bnode<T>* temp = get_min_successor(root);
				if (print(temp, High, Low))
					cout << "Are all the numbers b/w the given range!";
				else
					cout << "\nNumber does not exist"; // else, print an error message
			}
			else
			{
				Bnode<T>* temp = get_max_predecessor(root);
				if (print(temp, High, Low))
					cout << "Are all the numbers b/w the given range!";
				else
					cout << "\nNumber does not exist"; // else, print an error message
			}
		}
		else
			cout << "\nTree is Empty!";
	}
	bool print(Bnode<T>* n, T High, T Low) // print all data items that fall b/w Low and High range
	{
		bool flag = false;
		while (n)
		{
			if (n->data > Low && n->data < High)
			{
				cout << n->data << ' ';
				flag = true;
			}
			n = n->nextInOrder;
		}
		return flag;
	}
	SortedStacklessBST() // default constructor
	{
		root = NULL;
		IsSuccessor = true; // initially it is true
	}
	SortedStacklessBST(SortedStacklessBST<T> const& obj) // copy constructor
	{
		root = NULL;
		IsSuccessor = obj.IsSuccessor;
		if (obj.root) // if obj.root is not NULL
			copy(obj.root); // performs deep copy recusively
	}
	SortedStacklessBST<T> operator=(SortedStacklessBST<T> const& obj) // overloaded assingment operator
	{
		root = NULL;
		IsSuccessor = obj.IsSuccessor;
		if (obj.root) // if obj.root is not NULL
			copy(obj.root); // performs deep copy recusively
		return *this;
	}
	bool search(T d) // search a data in the tree without recursion
	{
		Bnode<T>* n = root;
		while (n != NULL)
		{
			if (d == n->data)
				return true;
			else
			{
				if (d > n->data)
					n = n->right;
				else
					n = n->left;
			}
		}
		return false;
	}
	bool insert(T d)
	{
		return insert(d, root);
	}
	bool insert(T d, Bnode<T>*&r)
	{
		if (r == NULL) // if root is NULL then 
		{
			Bnode<T>* n = new Bnode<T>(d); // form a new node with data d
			r = n; // assign the new node to root
			return true;
		}
		else if (r->data == d) // else if data already exits 
		{
			cout << "\nData Already exists!"; // then print an error message
			return false; // return false
		}
		Bnode<T>* n = new Bnode<T>(d), *parent = NULL, *child = r; // iteratively insert the data 
		while (child != NULL) // two pointers parent and child are mentained for the traversal of the tree
		{
			parent = child;
			if (child->data == d)
			{
				cout << "\nData Already exists!";
				return false;
			}
			else if (d > child->data) // if d is larger than its parent 
			{
				child = child->right;
				if (IsSuccessor) // successor case 
				{
					if (parent->nextInOrder == NULL)
						parent->nextInOrder = n;
					else if (parent->nextInOrder->data > d)
						parent->nextInOrder = n;
				}
				else // predeccessor case 
				{
					if (n->nextInOrder == NULL)
						n->nextInOrder = parent;
					else if (n->nextInOrder->data < parent->data)
						n->nextInOrder = parent;
				}
			}
			else // if d is small than its parent
			{
				child = child->left;
				if (IsSuccessor) // successor case 
				{
					if (n->nextInOrder == NULL)
						n->nextInOrder = parent;
					else if (n->nextInOrder->data < parent->data)
						n->nextInOrder = parent;
				}
				else // predeccessor case
				{
					if (parent->nextInOrder == NULL)
						parent->nextInOrder = n;
					else if (parent->nextInOrder->data < d)
						parent->nextInOrder = n;
				}
			}
		}
		if (parent->data < d) // then insert at right side of parent
		{
			parent->right = n;
			if (IsSuccessor)
				parent->nextInOrder = n;
			else
				n->nextInOrder = parent;
			return true;
		}
		else // else insert at left side of parent
		{
			parent->left = n;
			if (!IsSuccessor)
				parent->nextInOrder = n;
			else
				n->nextInOrder = parent;
			return true;
		}
	}
	Bnode<T>* get_max_predecessor(Bnode<T>* n)
	{
		while (n->right != NULL) // maximum value - right child NULL
			n = n->right;
		return n;
	}
	Bnode<T>* get_min_successor(Bnode<T>* n)
	{
		while (n->left != NULL) // minimum value - left child NULL
			n = n->left;
		return n;
	}
	bool remove(T d)
	{
		Bnode<T>* sp = NULL;
		return remove(d, root, root, sp, false);
	}
	bool remove(T d, Bnode<T>* &parent, Bnode<T>* &r, Bnode<T>*& sp, bool flag)
	{
		if (r == NULL)
			return false;
		if (d < r->data)
		{
			if (!IsSuccessor) // then point sp to its successor
				sp = r;
			return remove(d, r, r->left, sp, flag);
		}
		else if (d > r->data)
		{
			if (IsSuccessor) // then point sp to its predecessor
				sp = r;
			return remove(d, r, r->right, sp, flag);
		}
		else if (r->data == d)
		{
			if (r->left == NULL && r->right == NULL)
			{
				if (parent->left != NULL)
				{
					if (parent->left->data == d)
					{
						if (!flag && sp) // then update its nextinorder
						{
							sp->nextInOrder = r->nextInOrder;
						}
						delete r;
						r = NULL;
						parent->left = NULL;
					}
				}
				else if (parent->right != NULL)
				{
					if (parent->right->data == d)
					{
						if (!flag && sp) // then update its nextinorder
						{
							sp->nextInOrder = r->nextInOrder;
						}
						delete r;
						r = NULL;
						parent->right = NULL;
					}
				}
				else
				{
					delete r;
					r = NULL;
				}
				return true;
			}
			if (r->left != NULL && r->right != NULL) // if the node to be deleted has both childs
			{
				r->data = r->nextInOrder->data; // then replace its data with its nextInOrder (predecessor or successor)
				r->nextInOrder = r->nextInOrder->nextInOrder; // set its nextInOrder
				if (IsSuccessor)
					return remove(r->data, r, r->right, sp, true); // remove the node whoes data was copied 
				else
					return remove(r->data, r, r->left, sp, true); // remove the node whoes data was copied
				return true;
			}
			else
			{
				if (sp == NULL)
				{
					if (IsSuccessor) // then return predecessor
					{
						if (r->left != NULL) // check if current node is smallest or not
						{
							sp = get_max_predecessor(r->left);
							sp->nextInOrder = r->nextInOrder;
						}
					}
					else // else return sucessor
					{
						if (r->right != NULL) // check if current node is largest or not
						{
							sp = get_min_successor(r->right);
							sp->nextInOrder = r->nextInOrder;
						}
					}
				}
				else
					sp->nextInOrder = r->nextInOrder;
				Bnode<T>* temp;
				if (r->left != NULL)
					temp = r->left;
				else
					temp = r->right;
				delete r;
				r = temp;
				return true;
			}
		}
	}
	void copy(Bnode<T>* n) // recursive wrapper copy function 
	{
		if (n)
		{
			insert(n->data, this->root);
			copy(n->left);
			copy(n->right);
		}
	}
	void Destroy(Bnode<T>*& n) // destructor wrapper function
	{
		Bnode<T> *temp;
		while (n != NULL) // it destroys the tree by using linkedlist approach
		{
			temp = n->nextInOrder;
			delete n; // all the nodes are linked together, so we would just traverse like linkedlist and delete accordingly
			n = temp;
		}
	}
	~SortedStacklessBST() // destructor
	{
		if (root)
		{
			if (IsSuccessor)
			{
				Bnode<T>* temp = get_min_successor(root);
				Destroy(temp);
			}
			else
			{
				Bnode<T>* temp = get_max_predecessor(root);
				Destroy(temp);
			}
		}
	}
};
template <class T>
class Bnode {
	T data;
	Bnode<T>* left;
	Bnode<T>* right;
	Bnode<T>* nextInOrder;
public:
	Bnode() // default constructor
	{
		left = right = nextInOrder = NULL;
	}
	Bnode(T d) // paramterized constructor
	{
		data = d;
		left = NULL;
		right = NULL;
		nextInOrder = NULL;
	}
	Bnode(T d, Bnode<T>* l, Bnode<T>* r) // paramterized constructor
	{
		data = d;
		left = l;
		right = r;
	}
	Bnode(T d, Bnode<T>* l, Bnode<T>* r, Bnode<T>* n) // paramterized constructor
	{
		data = d;
		left = l;
		right = r;
		nextInOrder = n;
	}
	~Bnode()
	{

	}
	friend class SortedStacklessBST<T>; // make SortedStacklessBST class friend, so that private data members can be accessed 
};
void menu()
{
	cout << "\n\tPress Buttons to perform actions:-";
	cout << "\n0 to exit";
	cout << "\n1 to insert";
	cout << "\n2 to remove";
	cout << "\n3 to copy constructor";
	cout << "\n4 to overloaded assignment operator";
	cout << "\n5 to reverse order";
	cout << "\n6 to check if all the leaves are on same level";
	cout << "\n7 to print";
	cout << "\n8 to print(T Low, T High)\n\n";
}
template <typename T>
void input()
{
	char i = ' ';
	T d;
	SortedStacklessBST<T> tree;
	while (i != '0')
	{
		menu();
		cin >> i;
		if (i == '0')
			cout << "\nProgram exited!";
		else if (i == '1')
		{
			cout << "\nEnter data to insert: ";
			cin >> d;
			tree.insert(d);
		}		
		else if (i == '2')
		{
			cout << "\nEnter data to remove: ";
			cin >> d;
			if (tree.remove(d))
				cout << d << " removed";
			else
				cout << d << " not removed";
		}
		else if (i == '3')
		{
			SortedStacklessBST<T> tree1(tree);
			cout << "\nCopied tree is:- ";
			tree1.print();
		}
		else if (i == '4')
		{
			SortedStacklessBST<T> tree1;
			tree1 = tree;
			cout << "\nCopied tree is:- ";
			tree1.print();
		}
		else if (i == '5')
		{
			tree.ReverseOder();
		}
		else if (i == '6')
		{
			if (tree.IsLeafBalance())
				cout << "\nLeafs are balanced!";
			else
				cout << "\nLeafs are not balanced!";
		}
		else if (i == '7')
		{
			cout << endl;
			tree.print();
		}
		else if (i == '8')
		{
			T Low , High;
			cout << "\nInput Low parameter: ";
			cin >> Low;
			cout << "\nInput High parameter: ";
			cin >> High;
			cout << endl;
			tree.print(Low, High); // prints all data between Low/High Range
		}
		else
			cout << "\nPlease input correct no.";
	}
}
void main()
{
	input<char>();
	system("pause");
}

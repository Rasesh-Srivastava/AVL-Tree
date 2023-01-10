#include <iostream>
#include <cmath>
using namespace std;
class Node
{
public:
	int data;
	Node *left;
	Node *right;
	Node *parent;
	int h;
};
class AVL_Tree
{
public:
	void PreOrder(Node *root)
	{
		cout << "Node: " << root->data
			 << ", Parent Node: ";

		if (root->parent != NULL)
			cout << root->parent->data << endl;
		else
			cout << "NULL" << endl;
		if (root->left != NULL)
		{
			PreOrder(root->left);
		}
		if (root->right != NULL)
		{
			PreOrder(root->right);
		}
	}
	void inorder(Node *n)
	{
		if (n == NULL)
		{
			return;
		}
		inorder(n->left);
		cout << n->data << " ";
		inorder(n->right);
	}
	void preorder(Node *n)
	{
		if (n == NULL)
		{
			return;
		}
		cout << n->data << " ";
		preorder(n->left);
		preorder(n->right);
	}
	void postorder(Node *n)
	{
		if (n == NULL)
		{
			return;
		}
		postorder(n->left);
		postorder(n->right);
		cout << n->data << " ";
	}
	void update_h(Node *root)
	{
		if (root != NULL)
		{
			int val = 1;
			if (root->left != NULL)
			{
				val = root->left->h + 1;
			}
			if (root->right != NULL)
			{
				val = max(val, root->right->h + 1);
			}
			root->h = val;
		}
	}
	Node *LL(Node *root)
	{
		Node *temp = root->left;
		root->left = temp->right;
		if (temp->right != NULL)
		{
			temp->right->parent = root;
		}
		temp->right = root;
		temp->parent = root->parent;
		root->parent = temp;
		if (temp->parent != NULL && root->data < temp->parent->data)
		{
			temp->parent->left = temp;
		}
		else
		{
			if (temp->parent != NULL)
			{
				temp->parent->right = temp;
			}
		}
		root = temp;
		update_h(root->left);
		update_h(root->right);
		update_h(root);
		update_h(root->parent);
		return root;
	}
	Node *RR(Node *root)
	{
		Node *temp = root->right;
		root->right = temp->left;
		if (temp->left != NULL)
		{
			temp->left->parent = root;
		}
		temp->left = root;
		temp->parent = root->parent;
		root->parent = temp;
		if (temp->parent != NULL && root->data < temp->parent->data)
		{
			temp->parent->left = temp;
		}
		else
		{
			if (temp->parent != NULL)
			{
				temp->parent->right = temp;
			}
		}
		root = temp;
		update_h(root->left);
		update_h(root->right);
		update_h(root);
		update_h(root->parent);
		return root;
	}
	Node *LR(Node *root)
	{
		root->left = RR(root->left);
		return LL(root);
	}
	Node *RL(Node *root)
	{
		root->right = LL(root->right);
		return RR(root);
	}
	Node *BalanceTree(Node *root)
	{
		int left_h = 0;
		int right_h = 0;
		if (root->left != NULL)
		{
			left_h = root->left->h;
		}
		if (root->right != NULL)
		{
			right_h = root->right->h;
		}
		if (abs(left_h - right_h) == 2)
		{
			if (left_h < right_h)
			{
				int right_h1 = 0;
				int right_h2 = 0;
				if (root->right->right != NULL)
				{
					right_h2 = root->right->right->h;
				}
				if (root->right->left != NULL)
				{
					right_h1 = root->right->left->h;
				}
				if (right_h1 > right_h2)
				{
					root = RL(root);
				}
				else
				{
					root = RR(root);
				}
			}
			else
			{
				int left_h1 = 0;
				int left_h2 = 0;
				if (root->left->right != NULL)
				{
					left_h2 = root->left->right->h;
				}
				if (root->left->left != NULL)
				{
					left_h1 = root->left->left->h;
				}
				if (left_h1 > left_h2)
				{
					root = LL(root);
				}
				else
				{
					root = LR(root);
				}
			}
		}
		return root;
	}
	Node *InsertNode(Node *root, Node *parent, int data)
	{
		if (root == NULL)
		{
			root = new Node();
			root->h = 1;
			root->left = NULL;
			root->right = NULL;
			root->parent = parent;
			root->data = data;
		}
		else if (root->data > data)
		{
			root->left = InsertNode(root->left, root, data);
			int left_h = 0;
			int right_h = 0;
			if (root->left != NULL)
			{
				left_h = root->left->h;
			}
			if (root->right != NULL)
			{
				right_h = root->right->h;
			}
			if (abs(left_h - right_h) == 2)
			{

				if (root->left != NULL && data < root->left->data)
				{
					root = LL(root);
				}
				else
				{
					root = LR(root);
				}
			}
		}
		else if (root->data < data)
		{
			root->right = InsertNode(root->right, root, data);
			int left_h = 0;
			int right_h = 0;
			if (root->left != NULL)
			{
				left_h = root->left->h;
			}
			if (root->right != NULL)
			{
				right_h = root->right->h;
			}
			if (abs(left_h - right_h) == 2)
			{
				if (root->right != NULL && data < root->right->data)
				{
					root = RL(root);
				}
				else
				{
					root = RR(root);
				}
			}
		}
		update_h(root);
		return root;
	}
	Node *DeleteNode(Node *root, int data)
	{
		if (root != NULL)
		{
			if (root->data == data)
			{
				if (root->right == NULL && root->left != NULL)
				{
					if (root->parent != NULL)
					{
						if (root->parent->data < root->data)
						{
							root->parent->right = root->left;
						}
						else
						{
							root->parent->left = root->left;
						}
						update_h(root->parent);
					}
					root->left->parent = root->parent;
					root->left = BalanceTree(root->left);
					return root->left;
				}
				else if (root->left == NULL && root->right != NULL)
				{
					if (root->parent != NULL)
					{
						if (root->parent->data < root->data)
						{
							root->parent->right = root->right;
						}
						else
						{
							root->parent->left = root->right;
						}
						update_h(root->parent);
					}
					root->right->parent = root->parent;
					root->right = BalanceTree(root->right);
					return root->right;
				}
				else if (root->left == NULL && root->right == NULL)
				{
					if (root->parent->data < root->data)
					{
						root->parent->right = NULL;
					}
					else
					{
						root->parent->left = NULL;
					}
					if (root->parent != NULL)
					{
						update_h(root->parent);
					}
					root = NULL;
					return NULL;
				}
				else
				{
					Node *temp = root;
					temp = temp->right;
					while (temp->left != NULL)
					{
						temp = temp->left;
					}
					int val = temp->data;
					root->right = DeleteNode(root->right, temp->data);
					root->data = val;
					root = BalanceTree(root);
				}
			}
			else if (root->data < data)
			{
				root->right = DeleteNode(root->right, data);
				root = BalanceTree(root);
			}
			else if (root->data > data)
			{
				root->left = DeleteNode(root->left, data);
				root = BalanceTree(root);
			}
			if (root != NULL)
			{
				update_h(root);
			}
		}
		root = BalanceTree(root);
		return root;
	}
	Node *search(Node *node, int data)
	{
		Node *current = node;
		while (current->data != data)
		{
			if (current->data > data)
			{
				current = current->left;
			}
			else
			{
				current = current->right;
			}
			if (current == NULL)
			{
				return NULL;
			}
		}
		return current;
	}
};
int main()
{
	AVL_Tree Rasesh;
	Node *root = NULL;
	while (true)
	{
		cout << "1. Insert an element" << endl;
		cout << "2. Delete an element" << endl;
		cout << "3. Search an element" << endl;
		cout << "4. InOrder Traversal" << endl;
		cout << "5. PreOrder Traversal" << endl;
		cout << "6. PostOrder Traversal" << endl;
		cout << "7. Exit" << endl;
		cout << "Enter your choice" << endl;
		int n;
		cin >> n;
		switch (n)
		{
		default:
			cout << "Enter a valid choice" << endl;
			break;
		case 7:
			exit(0);
			break;
		case 6:
			Rasesh.postorder(root);
			cout << endl;
			break;
		case 5:
			Rasesh.preorder(root);
			cout << endl;
			break;
		case 4:
			Rasesh.inorder(root);
			cout << endl;
			break;
		case 1:
			cout << "Enter the element to be inserted" << endl;
			int a;
			cin >> a;
			root = Rasesh.InsertNode(root, NULL, a);
			break;
		case 2:
			cout << "Enter the element to be deleted" << endl;
			int b;
			cin >> b;
			root = Rasesh.DeleteNode(root, b);
			break;
		case 3:
			cout << "Enter the element to be searched" << endl;
			int c;
			cin >> c;
			Node *temp = Rasesh.search(root, c);
			if (temp == NULL)
			{
				cout << "Element Not Found" << endl;
			}
			else
			{
				cout << "Element Found" << endl;
				if (temp->parent != NULL)
				{
					cout << "Parent of " << temp->data << " is: ";
					cout << temp->parent->data << endl;
				}
			}
			break;
		}
	}
	return 0;
}

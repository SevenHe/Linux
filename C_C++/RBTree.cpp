#include<iostream>
using namespace std;

#define RED 0
#define BLACK 1

// NIL is a sentry node.
struct RBNode {
	int key;
	RBNode* left;
	RBNode* right;
	RBNode* parent;
	int color;
};

// The most difficult in RBTree is that every node has three Node* 
// so that every change needs to influence them!
class RBTree {

	public:
		void left_rotate(RBNode*);
		void right_rotate(RBNode*);
	protected:
		RBNode* root;
		RBNode* nil;
};

void RBTree::left_rotate(RBNode* x)
{
	RBNode* y = x->right;
	x->right = y->left;
	y->parent = x->parent;
	y->left = x;
	if(x->parent == this->nil)
	{
		// so x is equal to root.
		// need to change root for iteration!
		this->root = y;
	}
	else if(x == x->parent->left)
	{
		// change the parent, also for iteration!!
		x->parent->left = y;
	}
	else
		x->parent->right = y;
	// Then, change the parent of x
	x->parent = y;
	// seting the child's parent is a very different thing that you needs to take care if it is a nil!
	if(x->right != this->nil)
		x->right->parent = x;
}

// just like the left_rotate
void RBTree::right_rotate(RBNode* y)
{
	RBNode* x = y->left;
	y->left = x->right;
	x->parent = y->parent;
	x->right = y;
	if(y->parent == this->nil)
	{
		this->root = x;
	}
	else if(y == y->parent->left)
	{
		y->parent->left = x;
	}
	else
		y->parent->right = x;
	y->parent = x;
	if(y->left != this->nil)
		y->left->parent = y;
}


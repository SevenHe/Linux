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
// and the node itself is invariable!
class RBTree {

	public:
		RBTree();
		void left_rotate(RBNode*);
		void right_rotate(RBNode*);
		void rb_insert(RBNode*);
		void rb_left_insert_fixup(RBNode*);
		void rb_insert_fixup(RBNode*);
		void rb_delete(RBNode*);
		void display(RBNode*);
	protected:
		RBNode* root;
		RBNode* nil;
};

// x is the parent of y!
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

// just like the left_rotate, but y is the parent of x, from the same level!
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

void RBTree::rb_insert(RBNode* z)
{
	RBNode* y = this->nil;
	RBNode* x = this->root;
	while(x != this->nil)
	{
		// at last, y is the parent node.
		y = x;
		if(z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	// This is the situation that there is no root, so we need not create a tree manually!
	if(y == this->nil)
		this->root = z;
	else if(z->key < y->key)
		y->left = z;
	else
		y->right = z;
	z->left = this->nil;
	z->right = this->nil;
	z->color = RED;
	// next, we need to fix the tree up to meet the RBTree property!
	rb_insert_fixup(z);
}

// rotate is not a recursion operation!
// z->parent just have two directions, left and right, so just two situations!
// pay attention to understanding!
void RBTree::rb_insert_fixup(RBNode* z)
{
	while(z->parent->color == RED)
	{
		RBNode* y = NULL;
		int direction = -1;		// 0 for y right, 1 for y left!
		if(z->parent ==  z->parent->parent->left)
		{
			y = z->parent->parent->right;
			direction = 0;
		}
		else if(z->parent == z->parent->parent->right)
		{
			y = z->parent->parent->left;
			direction = 1;
		}
		// right!
		if(direction == 0)
		{
			if(y->color == RED)
			{
				y->parent->color = RED;
				y->color = BLACK;
				z->parent->color = BLACK;
				// for recursion, do the whole tree!
				z = z->parent->parent;
			}
			else if(y->color == BLACK && z == z->parent->right)
			{
				z = z->parent;
				// iteration 
				left_rotate(z);
				// get into next situation!
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				// iteration
				right_rotate(z->parent->parent);
			}
			else if(y->color == BLACK && z == z->parent->left)
			{
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				// iteration
				right_rotate(z->parent->parent);
			}
		}
		// left
		else if(direction == 1)
		{
			if(y->color == RED)
			{
				y->parent->color = RED;
				y->color = BLACK;
				z->parent->color = BLACK;
				z = z->parent->parent;
			}
			// simple situation!
			else if(y->color == BLACK && z == z->parent->right)
			{
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
			// take into previous situation!
			else if(y->color == BLACK && z == z->parent->left)
			{
				z = z->parent;
				right_rotate(z);
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
		}
	}
	// fix the seconde property, that is the root color is always BLACK!
	this->root->color = BLACK;
}

void RBTree::display(RBNode* z)
{
	static int level = 0;
	if(z != this->nil)
	{
		cout << "level: " << level << " key: " << z->key << " color: " << z->color << endl;
		level ++;
		if(z->left != nil)
			display(z->left);
		if(z->right != nil)
			display(z->right);
	}
}

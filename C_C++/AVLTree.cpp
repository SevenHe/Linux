#include<iostream>
using namespace std;

/************************----Definition----*****************************/
struct AVLNode {
	int data;
	AVLNode* left;
	AVLNode* right;
	int level;
};

class AVLTree
{
	public:
		static int max_left_level;
		static int max_right_level;
		AVLTree(int);
		~AVLTree();
		AVLNode* nfv(int);
		void insert(AVLNode*);
		AVLNode* find_parent(int, AVLNode*, AVLNode*);
		void display();
		int destruct(AVLNode*);
	protected:
		AVLNode* root;
		void display(AVLNode*);
};

/************************----Accomplishment----*************************/
int AVLTree::max_left_level = 0;
int AVLTree::max_right_level = 0;
AVLTree::AVLTree(int initValue)
{
	this->root = new AVLNode;
	this->root->data = initValue;
	this->root->level = 0;
}

AVLTree::~AVLTree()
{
	if(destruct(this->root) == 0)
		cout << "Have cleaned the rubbish!!" << endl;
}

// return a new node from a int value, n f v
AVLNode* AVLTree::nfv(int value)
{
	AVLNode* incoming = new AVLNode;
	incoming->data = value;
	incoming->left = NULL;
	incoming->right = NULL;
	return incoming;
}

void AVLTree::insert(AVLNode* newcome)
{
	AVLNode* parent = NULL;
	if(newcome->data > this->root->data) 
	{
		parent = find_parent(newcome->data, this->root->right, this->root);
		if(parent->level == max_left_level)
		{
			newcome->level = parent->level + 1;
			max_left_level = newcome->level;
		}	
		else
			newcome->level = parent->level + 1;
	}
	else if(newcome->data < this->root->data)
	{
		parent = find_parent(newcome->data, this->root->left, this->root);
		if(parent->level == max_right_level)
		{
			newcome->level = parent->level + 1;
			max_right_level = newcome->level;
		}
		else
			newcome->level = parent->level + 1;
	}
	if(parent == NULL)
		cout << "AVLTree has had the same value!" << endl;
	else if(parent->data > newcome->data)
		parent->left = newcome;
	else
		parent->right = newcome;

	// for future, prompt the level and the direction.
	if(parent != NULL)
		cout << "Complete the insert operation!" << endl;
}

AVLNode* AVLTree::find_parent(int rookie, AVLNode* child, AVLNode* parent)
{
	if(child == NULL)
		return parent;
	else if(child->data > rookie)
		return find_parent(rookie, child->left, child);
	else if(child->data < rookie)
		return find_parent(rookie, child->right, child);
	else
		return NULL;		// This means child->data == rookie!
}

void AVLTree::display()
{
	this->display(this->root);
	cout << "Display operation completed!" << endl;
}

void AVLTree::display(AVLNode* root)
{
	cout << "Level " << root->level << ": " << root->data << endl;
	if(root->left != NULL)
		display(root->left);
	if(root->right != NULL)
		display(root->right);
}

int AVLTree::destruct(AVLNode* root)
{
	if(root->left == NULL && root->right == NULL)
	{
		delete root;
		return 1;
	}
	else
	{
		if(root->left != NULL)
			destruct(root->left);
		if(root->right != NULL)
			destruct(root->right);
	}
	return 0;
}

/*********************************----MAIN----********************************/
int main()
{
	AVLTree* test = new AVLTree(25);
	AVLNode* a = test->nfv(13);
	AVLNode* b = test->nfv(34);
	AVLNode* c = test->nfv(11);
	AVLNode* d = test->nfv(28);
	AVLNode* e = test->nfv(17);
	test->insert(a);
	test->insert(b);
	test->insert(c);
	test->insert(d);
	test->insert(e);
	test->display();
	delete test;
}


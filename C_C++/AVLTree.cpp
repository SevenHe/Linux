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
		void left_balance(AVLNode*, AVLNode*);
		void right_balance(AVLNode*, AVLNode*);
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
	if(newcome->data < this->root->data) 
	{
		parent = find_parent(newcome->data, this->root->left, this->root);
		if(parent != NULL)
		{	
			if(parent->level == max_left_level)
			{
				newcome->level = parent->level + 1;
				max_left_level = newcome->level;
			}	
			else
				newcome->level = parent->level + 1;
			parent->left = newcome;
		}
	}
	else if(newcome->data > this->root->data)
	{
		parent = find_parent(newcome->data, this->root->right, this->root);
		if(parent != NULL)
		{
			if(parent->level == max_right_level)
			{
				newcome->level = parent->level + 1;
				max_right_level = newcome->level;
			}
			else
				newcome->level = parent->level + 1;
			parent->right = newcome;
		}
	}

	if(parent == NULL)
		cout << "AVLTree has had the same value!" << endl;
	else
	{
		// for future, prompt the level and the direction.
		cout << "Complete the insert operation!" << max_left_level << max_right_level << endl;
		if(max_left_level - max_right_level > 1)
			left_balance(newcome, parent);
		else if(max_right_level - max_left_level > 1)
			right_balance(newcome, parent);
	}
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

// left and right, both have 4 situations!
void AVLTree::left_balance(AVLNode* child, AVLNode* parent)
{
	//AVLNode* p_parent = NULL;
	if(this->root->right == NULL && parent->right == NULL)
	{
		// must handle the left and right!
		AVLNode* temp = this->root;
		this->root->left = NULL;
		this->root = parent;
		parent->right = temp;
		this->root->level = 0;
		child->level = 1;		//(++this->root->level);
	    temp->level = 1;		//(++this->root->level);	
		max_left_level --;
		cout << "Have balanced the left side!" << endl;
	}

}

void AVLTree::right_balance(AVLNode* child, AVLNode* parent)
{
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
	//AVLNode* b = test->nfv(34);
	AVLNode* c = test->nfv(11);
	//AVLNode* d = test->nfv(28);
	//AVLNode* e = test->nfv(17);
	test->insert(a);
	//test->insert(b);
	test->insert(c);
	//test->insert(d);
	//test->insert(e);
	test->display();
	delete test;
}


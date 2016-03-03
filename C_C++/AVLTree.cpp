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
		AVLNode* find_existed_parent(int, AVLNode*, AVLNode*);
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
	this->root->left = NULL;
	this->root->right = NULL;
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
			if(newcome->data < parent->data)
				parent->left = newcome;	
			else if(newcome->data > parent->data)
				parent->right = newcome;
			if(parent->level == max_left_level)
			{
				newcome->level = parent->level + 1;
				max_left_level = newcome->level;
			}	
			else
				newcome->level = parent->level + 1;
			
		}
	}
	else if(newcome->data > this->root->data)
	{
		parent = find_parent(newcome->data, this->root->right, this->root);
		if(parent != NULL)
		{
			if(newcome->data < parent->data)
				parent->left = newcome;	
			else if(newcome->data > parent->data)
				parent->right = newcome;

			if(parent->level == max_right_level)
			{
				newcome->level = parent->level + 1;
				max_right_level = newcome->level;
			}
			else
				newcome->level = parent->level + 1;
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

AVLNode* AVLTree::find_existed_parent(int rookie, AVLNode* child, AVLNode* parent)
{
	if(child->data == rookie)
		return parent;
	else if(child->data > rookie)
		return find_existed_parent(rookie, child->left, child);
	else if(child->data < rookie)
		return find_existed_parent(rookie, child->right, child);
	else
		return NULL;		// do not find it!
}

// left and right, both have 4 situations!
// the node memory is all the same whenever!
void AVLTree::left_balance(AVLNode* child, AVLNode* parent)
{
	AVLNode* p_parent = find_existed_parent(parent->data, this->root->left, this->root);
	AVLNode* pp_parent = NULL;
	if(p_parent->data == this->root->data)
		pp_parent = this->root;
	else
		pp_parent = find_existed_parent(p_parent->data, this->root->left, this->root);
	if(p_parent != NULL && pp_parent != NULL)
	{
		if(p_parent->right == NULL && parent->right == NULL)
		{
			// must handle the left and right!
			if(pp_parent != p_parent)
			{
				pp_parent->left = parent;
				p_parent->left = NULL;
			}
			else
			{
				// This situation, root has changed!
				p_parent->left = NULL;
				this->root = parent;
			}
			parent->right = p_parent;
			parent->level = p_parent->level;
			child->level --;		//(++this->root->level);
			p_parent->level = child->level;
			max_left_level --;
			cout << "Have balanced the left side!" << endl;
		}
		else if(parent->right == NULL && p_parent->right != NULL)
		{
			// likewise!
			pp_parent->left = p_parent->right;
			p_parent->right = pp_parent;
			if(pp_parent == this->root)
				this->root = p_parent;
			pp_parent->level ++;
			pp_parent->right->level ++;
			p_parent->level --;
			parent->level --;
			child->level --;
		}

	}
	else
		cout << "Unkown error, please debug it!" << endl;
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
	AVLTree* test = new AVLTree(50);
	AVLNode* a = test->nfv(40);
	AVLNode* b = test->nfv(60);
	AVLNode* c = test->nfv(30);
	AVLNode* d = test->nfv(45);
	AVLNode* e = test->nfv(20);
	test->insert(a);
	test->insert(b);
	test->insert(c);
	test->insert(d);
	test->display();
	test->insert(e);
	test->display();
	delete test;
}


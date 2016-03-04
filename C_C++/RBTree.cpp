#include<iostream>
using namespace std;

#define RED 0
#define BLACK 1

struct RBNode {
	int key;
	RBNode* left;
	RBNode* right;
	RBNode* parent;
	int color;
};

class RBTree {

	public:
		void left_rotate();
	protected:
		RBNode* root;
};

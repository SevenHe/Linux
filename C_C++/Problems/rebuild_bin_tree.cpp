/*
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Definition for binary tree
 */
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Solution {
	public:
		struct TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> in) 
		{
			if(pre.size() == 1 || in.size() == 1)
				return new TreeNode(pre[0]);
			int root = pre[0];
			vector<int>::iterator pos = find(in.begin(), in.end(), root);
			vector<int> leftp;
			vector<int> rightp;
			vector<int> lefti;
			vector<int> righti;
			TreeNode* left = NULL;
			TreeNode* right = NULL;
			int div = pos - in.begin();
			leftp.assign(pre.begin()+1, pre.begin()+div+1);
			rightp.assign(pre.begin()+div+1, pre.end());
			lefti.assign(in.begin(), in.begin()+div);
			righti.assign(in.begin()+div+1, in.end());
			if(leftp.size() != 0 && lefti.size() != 0)
				left = reConstructBinaryTree(leftp, lefti);
			if(rightp.size() != 0 && righti.size() != 0)
				right = reConstructBinaryTree(rightp, righti);
			TreeNode* cur = new TreeNode(root);
			cur->left = left;
			cur->right = right;
			return cur;
		}
};

void print_tree(struct TreeNode* cur)
{
	if(cur == NULL)
		return;
	else
	{
		cout << cur->val << " ";
		print_tree(cur->left);
		print_tree(cur->right);
	}
}

int main()
{
	Solution S;
	int a[] = {1, 2, 4, 7, 3, 5, 6, 8};
	int b[] = {4, 7, 2, 1, 5, 3, 6, 8};
	vector<int> va(a, a+8);
	vector<int> vb(b, b+8);
	TreeNode* root = S.reConstructBinaryTree(va, vb);
	print_tree(root);
	cout << endl;
	return 0;
}

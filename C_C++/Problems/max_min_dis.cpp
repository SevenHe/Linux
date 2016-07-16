/*
   有一棵二叉树，树上每个点标有权值，权值各不相同，请设计一个算法算出权值最大的叶节点到权值最小的叶节点的距离。二叉树每条边的距离为1，一个节点经过多少条边到达另一个节点为这两个节点之间的距离。
   给定二叉树的根节点root，请返回所求距离。
 */
/*
 * 一棵树上两个叶节点或者说两个节点之间的权值，关系等，都可以通过传递一个数组，然后通过递归判断值是否存在于数组中来进行返回
 * 最后得到的路径中，有重复的，则-2，最后为两边路径之和-两倍的重复路径条数即可！
 * 认真读好题，想好每一个问题！
 */
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

#include <limits.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
		}
};

class Tree {
public:
    int maxV;
    int minV;
    Tree()
    {
        maxV = 0;
        minV = INT_MAX;
    }
    void findV(TreeNode* node)
    {
        if(node == NULL)
            return;
        if(node->left == NULL && node->right == NULL)
        {
            if(node->val > maxV)
                maxV = node->val;
            if(node->val < minV)
                minV = node->val;
        }
        findV(node->left);
        findV(node->right);
    }
    vector<int> findPath(TreeNode* node, int value, vector<int> ret)
    {
        if(node == NULL)
            return ret;
        if(node->left == NULL && node->right == NULL)
        {
            if(node->val == value)
            {
                ret.push_back(value);
                return ret;
            }
        }
        ret.push_back(node->val);
        vector<int> left = findPath(node->left, value, ret);
        vector<int> right = findPath(node->right, value, ret);
        if(find(left.begin(), left.end(), value) != left.end())
            return left;
        else if(find(right.begin(), right.end(), value) != right.end())
            return right;
        return ret;
    }
    
    int getDis(TreeNode* root) {
        findV(root);
        vector<int> maxP;
        maxP = findPath(root, maxV, maxP);
        vector<int> minP;
        minP = findPath(root, minV, minP);
        int repeat = 0;
        int len = maxP.size() > minP.size() ? minP.size(): maxP.size();
        for(int i=1; i<len; i++)
        {
            if(minP[i-1] == maxP[i-1] && minP[i] == maxP[i])
                repeat ++;
        }
        return minP.size()+maxP.size()-2-2*repeat;
    }
};

int main()
{
	struct TreeNode* root = new TreeNode(13);
	root->left = new TreeNode(8);
	root->right = new TreeNode(12);
	root->left->left = new TreeNode(9);
	root->left->left->left = new TreeNode(7);
	root->left->left->right = new TreeNode(11);
	root->left->right = new TreeNode(6);
	root->left->right->right = new TreeNode(14);
	root->right->left = new TreeNode(4);
	root->right->left->left = new TreeNode(2);
	root->right->left->right = new TreeNode(5);
	root->right->right = new TreeNode(3);
	root->right->right->right = new TreeNode(1);

	Tree tree;
	cout << tree.getDis(root) << endl;
	return 0;
}

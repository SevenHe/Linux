/*
   输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
 */
/*
   后序遍历一个二叉查找树，每次都与最后一个元素判断即可，看看能否到达这个位置，
   因为即使是分左右子树，后面的元素都属于父亲节点的右子节点，因此值是大于左子树的节点和父亲节点的左子节点，
   因此正常的查找树，同样能到该位置，因此不断遍历树的节点即可。
 */
class Solution {
	public:
		bool VerifySquenceOfBST(vector<int> sequence) {
			int size = sequence.size();
			if(0==size)return false;

			int i = 0;
			while(--size)
			{
				while(sequence[i++]<sequence[size]);
				while(sequence[i++]>sequence[size]);

				if(i<size)return false;
				i=0;
			}
			return true;
		}
};

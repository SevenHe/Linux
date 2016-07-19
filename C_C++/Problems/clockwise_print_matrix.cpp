/*
   输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
 */
/*
   循环打印，可以判断圈数即可，不过利用四个角上的变量便于理解
 */
class Solution {
	public:
		vector<int> printMatrix(vector<vector<int> > matrix) {
			int n = 0;
			int len = 0;
			for(int i=0; i<matrix.size(); i++)
				len += matrix[i].size();
			vector<int> ret;
			if(matrix.size() == 1)
			{
				ret.assign(matrix[0].begin(), matrix[0].end());
				return ret;
			}
			else if(matrix[0].size() == 1)
			{
				for(int i=0; i<matrix.size(); i++)
					ret.push_back(matrix[i][0]);
				return ret;
			}
			int lx = 0, ly = matrix[0].size() - 1, vy = 0, vx = matrix[0].size()-1;
			int l = 0, v = matrix.size() - 1;
			while(n < len && l <= v)
			{
				for(int i=lx; i<=ly; i++)
					ret.push_back(matrix[l][i]);
				n += (ly-lx+1);
				if(n == len)
					break;
				for(int i=l+1; i<=v; i++)
					ret.push_back(matrix[i][ly]);
				n += (v-l);
				if(n == len)
					break;
				for(int i=vx-1; i>=vy; i--)
					ret.push_back(matrix[v][i]);
				n += (vx-vy);
				if(n == len)
					break;
				for(int i=v-1; i>l; i--)
					ret.push_back(matrix[i][vy]);
				n += (v-l-1);
				lx ++;
				ly --;
				vx --;
				vy ++;
				l ++;
				v --;
			}
			return ret;
		}
};

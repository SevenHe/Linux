#include <iostream>
#include <cstring>
using namespace std;

class Solution {
	public:
        bool move(int row, int col, int threshold)
        {
            int sum = 0;
			int tr = row;
			int tc = col;
			row = row - 1;
			col = col - 1;
            while(row != 0)
            {
                int x = row % 10;
                sum += x;
                row /= 10;
            }
            while(col != 0)
            {
                int x = col % 10;
                sum += x;
                col /= 10;
            }
			cout << tr << "," << tc << ",sum:" << sum << endl;
            if(sum > threshold)
                return false;
            return true;
        }
        
		int movingCount(int threshold, int rows, int cols)
		{
			int nr = 1;

			int state[rows+2][cols+2];
			memset(state, 0, sizeof(state));
			
			state[1][1] = 1;
			for(int x=1; x<=rows; x++)
				for(int y=1; y<=cols; y++)
				{
					if(move(x, y, threshold))
					{
						if(state[x-1][y] || state[x][y-1] ||
							state[x+1][y] || state[x][y+1])
						{
							nr++;
							state[x][y] = 1;
							cout << x << "," << y << endl;
							cout << state[x-1][y] << "," << state[x][y-1] << ","
								<< state[x+1][y] << "," << state[x][y+1] << endl;
						}
					}
					else
						state[x][y] = 0;
				}
			
			return nr;
		}
};

int main()
{
	Solution s;
	int ret = 0;
	int a,b;
	cin >> a >> b;
	ret = s.movingCount(10, a, b);
	cout << "(0, 0):" << ret << endl;
	return 0;
}

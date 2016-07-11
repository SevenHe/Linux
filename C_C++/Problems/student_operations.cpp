/*
 * 输入包括多组测试数据。
 每 组输入第一行是两个正整数N和M（0 < N <= 30000,0 < M <* 5000）,分别代表学生的数目和操作的数目。
 学生ID编号从1编到N。
 第二行包含N个整数，代表这N个学生的初始成绩，其中第i个数代表ID为i的学生的成绩
 接下来又M行，每一行有一个字符C（只取‘Q’或‘U’），和两个正整数A,B,当C为'Q'的时候, 表示这是一条询问操作，他询问ID从A到B（包括A,B）的学生当中，成绩最高的是多少
 当C为‘U’的时候，表示这是一条更新操作，要求把ID为A的学生的成绩更改为B。
 */

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int N;
	int M;
	while(cin >> N >> M)
	{
		int grade[30000];
		int index = 1;
		while(N--)
		{
			int tmp;
			cin >> tmp;
			grade[index] = tmp;
			index ++;
		}
		while(M--)
		{
			char op;
			int A;
			int B;
			cin >> op >> A >> B;
			if(op == 'U')
				grade[A] = B;
			else if(op == 'Q')
			{
				if(A > B)
					A = A + B - (B = A);
				cout << A << "," << B<<endl;
				int max = 0;
				for(int i=A; i<=B; i++)
					if(grade[i] > max)
						max = grade[i];
				cout << max << endl;
			}
		}
	}
	return 0;
}



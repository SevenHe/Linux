/*
   小明陪小红去看钻石，他们从一堆钻石中随机抽取两颗并比较她们的重量。这些钻石的重量各不相同。在他们们比较了一段时间后，它们看中了两颗钻石g1和g2。现在请你根据之前比较的信息判断这两颗钻石的哪颗更重。
   给定两颗钻石的编号g1,g2，编号从1开始，同时给定关系数组vector,其中元素为一些二元组，第一个元素为一次比较中较重的钻石的编号，第二个元素为较轻的钻石的编号。最后给定之前的比较次数n。请返回这两颗钻石的关系，若g1更重返回1，g2更重返回-1，无法判断返回0。输入数据保证合法，不会有矛盾情况出现。
 */
/*
 * 当有固定个数的元素，但是可以进行多次甚至重复比较而得出结果时，要了解到每个元素比较一次就可以得出结论，
 * 因此一个Queue就可以迭代的进行判断，当有新元素加入时，判断该元素是否已经迭代过了，若不进行状态的保存，则情况很多时，无限迭代了。
 * 而数据用map嵌套vector来保存，一个下标的多组数据。
 */
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Cmp {
public:
    map<int, vector<int> > reback;
    int less_than(int a, int b)
    {
		if(reback.find(b) == reback.end())
			return 0;
		vector<int> arr = reback[b];
        for(int i=0; i<arr.size(); i++)
        {
            if(arr[i] == a)
                return 1;
			else
                return less_than(a, arr[i]);
        }
        return 0;
    }
    int cmp(int g1, int g2, vector<vector<int> > records, int n) 
    {
        for(int i=0; i<n; i++)
            reback[records[i][0]].push_back(records[i][1]);  
        if(less_than(g2, g1) == 1)
            return 1;
        if(less_than(g1, g2) == 1)
            return -1;
        return 0;
    }
};

int main()
{
	int tt[4][2] = {{1, 2}, {2, 4}, {1, 3}, {4, 3}};
	vector<vector<int> > r;
	vector<int> t(tt[0], tt[0]+2);
	r.push_back(t);
	vector<int> t1(tt[1], tt[1]+2);
	r.push_back(t1);
	vector<int> t2(tt[2], tt[2]+2);
	r.push_back(t2);
	vector<int> t3(tt[3], tt[3]+2);
	r.push_back(t3);

	Cmp c;
	cout << c.cmp(3, 4, r, 4);
	return 0;
}

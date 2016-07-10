#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
using namespace std;

/* Divide the area, so cut down the cost. */
/* 另一个方法，可以将所有的等价元素排序，然后根据一个保存的下标数组，输出
 * 重点是1->3, 2->4, 3->4时，4被3的标签所改变，但是2也同样等价与4，则等价与3和1，这个代换要做好，即可完成所有的工作
 * 而通常的方法，则是在数组中，用值来链接，l[4] = 2. l[3] = 1, l[2] = 1, <<l[1] = 1>>!
 */
/*
 * 得到各部分等价的元素集合后，通过数组链接，然后通过一个类似选择排序，但是通过交换方式，即将字符串内所有已知的等价集合排列完毕。
 * 而且要注意，一个元素可以跟多个元素交换即等价，2->3, 2->5, 则3与5通过2等价.
 * The Worst: O(n^2)
 * 冒泡排序，每一趟，将一个最大的元素下沉，小元素上浮，最坏情况O(n^2).
 */
/*string find1(string s, int (&id)[10000])
{
	bool has_changed = true;
	for(int i=0; i<s.size()-1; i++)
		for(int j=i+1; j<s.size(); j++)
		{
			if(id[i] == id[j] && s[i] > s[j])
				swap(s[i], s[j]);
		}

	return s;
}

string find2(string s, map<int, vector<int> >& ops)
{
	int id[10000];
	for(int i=0; i<s.size(); i++)
		id[i] = i;
	map<int, vector<int> > cls;
	for(map<int, vector<int> >::iterator it = ops.begin(); it != ops.end(); it++)
	{
		int n1 = it->first;
		vector<int> tmp = it->second;
		for(vector<int>::iterator tip = tmp.begin(); tip != tmp.end(); tip++)
		{
			int n2 = *tip;
			if(id[n1] != id[n2])
			{
				id[n1] = id[n1] < id[n2] ? id[n1] : id[n2];
				id[n2] = id[n1];
#ifdef DEBUG
			cout << "n2 = " << n2 << ", n1 = " << n1 << endl;
#endif		
				if(find(cls[id[n1]].begin(), cls[id[n1]].end(), n1) == cls[id[n1]].end())
				{
#ifdef DEBUG
				cout << "Add " << n1 << " to " << id[n1] << endl;
#endif
					cls[id[n1]].push_back(n1);
				}
				if(find(cls[id[n1]].begin(), cls[id[n1]].end(), n2) == cls[id[n1]].end())
				{
#ifdef DEBUG
				cout << "Add " << n2 << " to " << id[n1] << endl;
#endif
					cls[id[n1]].push_back(n2);
				}	
			}
		}
	}
	*/
	/*
	for(map<int, vector<int> >::iterator it = cls.begin(); it != cls.end(); it++)
	{
		vector<int> ch;
		for(vector<int>::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
		{
#ifdef DEBUG
			cout << s[*vit] << ":" << (int)s[*vit] << endl;
#endif
			ch.push_back(s[*vit]);
		}
		sort(ch.begin(), ch.end());	
		sort(it->second.begin(), it->second.end());
		vector<int>::iterator cit = ch.begin();
		for(vector<int>::iterator vit = it->second.begin(); vit != it->second.end(); vit++)
		{
#ifdef DEBUG
			cout << (char)*cit<< ":" << *vit << endl;
#endif
			s[*vit] = (char)(*cit);
			cit ++;
		}
	}*/
//		
//	return find1(s, id);
//}

/*===================================*/
/* 只在一个array中partition不好，because a element can be in two groups or more, but when one group 
 * changes its value, other groups will not get the notification.
 * so connect the parents, and do links with an array.
 */
int id[10001] = {0};

int find(int n)
{
	int tmp = n;
	while(id[tmp] != tmp)
		tmp = id[tmp];
	id[n] = tmp;
	return tmp;
}

void join(int n1, int n2)
{
	int f1 = find(n1);
	int f2 = find(n2);
	/* find the parent and connect with each other! */
	if(f1 > f2)
		id[f1] = f2;
	else
		id[f2] = f1;
}
		

string find3(string s)
{
	int len = s.size();
	for(int i=0; i<len-1; i++)
		for(int j=i+1; j<len; j++)
		{
			if(find(i) == find(j) && s[i] > s[j])
				swap(s[i], s[j]);
		}

	return s;
}

int main()
{
	string s;
	while(cin >> s)
	{
		int n;
		cin >> n;
		for(int i=0; i<s.size(); i++)
			id[i] = i;
		map<int, vector<int> > ops;
		for(int i=0; i<n; i++)
		{
			int n1, n2;
			cin >> n1 >> n2;
			ops[n1].push_back(n2);
			join(n1, n2);
#ifdef DEBUG
		cout << "Input" << endl;
#endif
		}
		
		s = find3(s);

		cout << s << endl;
	}

	return 0;
}

/*
 * #include <iostream>
 * #include <cstdio>
 * #include <string>
 * #include <algorithm>
 * 
 * using namespace std;
 * 
 * int dsu[10001]={0};
 * 
 * int find(int x)
 * {
 *    int r=x;
 *    while(dsu[r]!=r)
 *        r=dsu[r];
 *    dsu[x]=r;
 *    return r;
 * }
 * 
 * void join(int x, int y)
 * {
 *    int fx=find(x);
 *    int fy=find(y);
 *    if(fx<fy)
 *        dsu[fy]=fx;
 *    else
 *        dsu[fx]=fy;
 * }
 * 
 * int main()
 * {
 *    string s;
 *    while(cin>>s)
 *    {
 *        int n;
 *        cin>>n;
 *        int len = s.size();
 *        for( int i=0; i<len; ++i)
 *            dsu[i]=i;
 *        while(n--)
 *        {
 *            int a,b;
 *            cin>>a>>b;
 *            join(a,b);
 *        }
 *        for(int i=0; i<len-1; ++i)
 *            for(int j=i+1; j<len; ++j)
 *            {
 *                int fj=find(i);
 *                int fj1=find(j);
 *                if(fj==fj1 && s[i] > s[j])
 *                    swap(s[i],s[j]);
 *            }
 *        cout<<s<<endl;
 *    }
 *    return 0;
 * }
 */

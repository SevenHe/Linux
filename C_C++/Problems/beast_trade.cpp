/*
 * 在最近几场魔兽争霸赛中，赫柏对自己的表现都不满意。
 * 为了尽快提升战力，赫柏来到了雷鸣交易行并找到了幻兽师格丽，打算让格丽为自己的七阶幻兽升星。
 * 经过漫长的等待以后，幻兽顺利升到了满星，赫柏很满意，打算给格丽一些小费。
 * 赫柏给小费是有原则的：
 * 1.最终给格丽的钱必须是5的倍数；
 * 2.小费必须占最终支付费用的5%~10%之间（包含边界）。
 * 升星总共耗费A魔卡，赫柏身上带了B魔卡，赫柏想知道他有多少种支付方案可供选择。
 * 注：魔卡是一种货币单位，最终支付费用=本该支付的+小费
 */
/* when you can not judge the bits, just use long and double! */
/* 多个数值比较的过程中，一定要考虑各种不同的情况，即使时很简单的情况，在数字很大的时候，也会造成很复杂的后果！！ */

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double A;
    double B;
    while(cin >> A >> B)
    {
        // (x+A)/20 <= x <= (x+A)/10
        long min = A/19;
        double rMin = A/19;
        long max = A/9;
        double rMax = A/9;
        long ret = 0;
        /*
         *		cout << "Min: " << min << endl;
         *		cout << setprecision(3) << "rMin: " << rMin << endl;
         *		cout << "Max: " << max << endl;
         *		cout << setprecision(3) << "rMax: " << rMax << endl;
         */
        long tA = A;
        long tB = B;
		bool has_found = false;
        for(long i=min; i<=max; i++)
        {
            if(i+tA > tB)
                break;
            //cout << "i: " << i << endl;
            if(i+tA <= tB && i+tA >= rMin+tA && (i+tA) % 5 == 0)
			{
				has_found = true;
                ret ++;
			}
			if(has_found)
				i+=4;
        }
        cout << ret << endl;
        
    }
    return 0;
}

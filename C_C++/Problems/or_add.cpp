/*
   给定 x, k ，求满足 x + y = x | y 的第 k 小的正整数 y 。 | 是二进制的或(or)运算，例如 3 | 5 = 7。
   比如当 x=5，k=1时返回 2，因为5+1=6 不等于 5|1=5，而 5+2=7 等于 5 | 2 = 7。
 */
/*
 * C++中 int的1<<31是最大值，但是不能等于，等于由于最高为1，变成了一个负数，溢出，不同与其他语言。
 * 因此遇到2，,000，,000，,000这样的大数，用unsigned int 或者 unsigned long。
 * 最好是long， 因为处理后不知道会多大。
 * 位运算用bitset！！！
 */
#include <iostream>
#include <bitset>
using namespace std;

int main() {
    unsigned long long x, y = 0, k;
    cin >> x >> k;
    
    bitset<64> xbs(x), kbs(k);
    
    for (size_t i = 0, kpos = 0; i < xbs.size(); ++i) {
        if (! xbs.test(i)) { // xbs[i] == 0
            xbs.set(i, kbs[kpos++]);
        }
    }
    
    y = xbs.to_ullong();
    y ^= x;
    
    cout << y << endl;   
    
    return 0;
}

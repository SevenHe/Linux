#include <iostream>
#include <string>
using namespace std;

/* very excellent solution ! */
class Solution {
	public:
		/* this can be expanded into any big numbers' adding with any bases
		 * just use an integer to store the cur bit, and use the cur bit as the result's current bit
		 * and if there was a carry, the rest of integer would be used in the next loop, so it is always right!
		 * remember, a good solution, O(max(m,n)), very quick!
		 */
		string addBinary(string a, string b) {
			int la = a.size() - 1;
			int lb = b.size() - 1;
			string ret = "";

			int c = 0;
			while (la >= 0 || lb >= 0 || c == 1) {
				c += la >= 0 ? a[la--]-'0' : 0;
				c += lb >= 0 ? b[lb--]-'0' : 0;

				// c just store two bits, the cur bit, and the higher bit
				// if there is not a carry, just >> 1 == 0
				// else the rest part would be the value in the higher bit!
				ret.insert(0, 1, (c&1)+'0');
				c >>= 1;
			}
			return ret;
		}
};

int main()
{
	return 0;
}

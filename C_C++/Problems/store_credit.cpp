#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define IN_PATH "/home/seven/Downloads/Google_Code_Jam/alp.in"
#define OUT_PATH "/home/seven/Downloads/Google_Code_Jam/alp.out"

int cmp(const pair<int, int>& x, const pair<int, int>& y)
{
	if (x.first != y.first)
		return x.first < y.first;
	return x.second < y.second;	
}

int main() 
{
	int N;
	ifstream ifs;
	ofstream ofs;
	ifs.open(IN_PATH);
	ofs.open(OUT_PATH);
	ifs >> N;
	for (int n=0; n<N; n++) {
		int C, L;
		ifs >> C >> L;
		vector<pair<int, int> > P(L);
		for (int i=0; i<L; i++) {
			int nr;
			ifs >> nr;
			P[i] = make_pair(nr, i+1);
		}
		sort(P.begin(), P.end(), cmp);
		vector<int> result(2);
		if (P.size() == 2) {
			result[0] = P[0].second;
			result[1] = P[1].second;
		}
		else {
			bool end = false;
			for (int i=0; i<L && !end; i++) {
				int rest = C - P[i].first;
				int left = 0;
				int right = L-1;
				// speed up!
				if (rest < P[i].first)
					right = i-1;
				else if (rest > P[i].first)
					left = i+1;
				else if (rest == P[i].first) {
					result[0] = P[i].second;
					result[1] = P[i+1].second;
					break;
				}
				while (left<=right) {
					int mid = (left+right)>>1;
					if (P[mid].first == rest) {
						result[0] = P[i].second;
						result[1] = P[mid].second;
						end = true;
						break;
					}
					else if (P[mid].first > rest) {
						right = mid-1;
					}
					else if (P[mid].first < rest) {
						left = mid + 1;
					}
				}
			}
		}
		sort(result.begin(), result.end());
		cout << "Case #" << n+1 << ": " <<  result[0] << " " << result[1] << endl;
		ofs << "Case #" << n+1 << ": " <<  result[0] << " " << result[1] << endl;
	}

	ifs.close();
	ofs.close();
	return 0;
}

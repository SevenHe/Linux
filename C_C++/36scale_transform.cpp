#include<iostream>
#include<string>
using namespace std;

string transform(int);
int main()
{
	cout << "Please input a decimal number:";
	int input;
	cin >> input;

	cout << "The result is " << transform(input) << endl;
	return 0;
}

string transform(int input)
{
	char transform_list[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	if(input < 36)
	{
		int unit = input % 36;
		char t_unit = transform_list[unit];
		string temp = "000";
		return temp+t_unit; 
	}
	else if(input < 36 * 36)
	{
		int decade = input / 36;
		char t_decade= transform_list[decade];
		int unit = (input - decade * 36) % 36;
		char t_unit = transform_list[unit];
		string temp = "00";
		return temp+t_decade+t_unit;
	}
	
	return "Input Error!!";
}

#include<iostream>
using namespace std;

int main()
{
	char input[1024];
	char output[1024];
	int count[1024];
	cin.getline(input, sizeof(char)*1024);
	int i = 0;
	char C = 'A';
	char c = 'a';
	int temp = -1;
	bool have_find = false;
	for( ; input[i]!='\0'; i++)
	{
		if(int(c) <= int(input[i]) && int(input[i]) <= int(c+25))
			input[i] = int(C)-int(c) + input[i];
		if(int(C) <= int(input[i]) && int(input[i]) <= int(C+25))
		{
			have_find = true;
			if(temp == -1) 
			{
				temp = int(input[i]);
				output[temp] = input[i];
				count[temp] = 1;
				continue;
			}
			else if(temp != 0)
			{
				if(temp == int(input[i]))
				{
					count[temp] ++;
				}
				else
				{
					cout << output[temp] << count[temp];
					output[temp] = 0;
					count[temp] = 0;
					temp = int(input[i]);
					output[temp] = input[i];
					count[temp] = 1;
					continue;
				}
			}
		}
	}
	if(have_find && output[temp] != -1)
		cout << output[temp] << count[temp];
}



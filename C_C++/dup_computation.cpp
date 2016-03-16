#include<iostream>
using namespace std;

int main()
{
	char input[1024];
	char output[1024];
	int count[1024];
	cin >> input;
	int i = 0;
	int index = 0;
	char C = 'A';
	for( ; input[i]!='\0'; i++)
	{
		if(int(C) <= int(input[i]) && int(input[i]) <= int(C+25))
		{
			int j = i - 1;
			bool duplicate = false;
			while(j>=0)
			{
				if(input[j] == input[i])
				{
					duplicate = true;
					break;
				}
				j --;
			}
			if(!duplicate)
			{
				output[index] = input[i];
				count[index] = 1;
				index ++;
			}
			else
			{
				int temp = index;
				while(temp>=0)
				{
					if(output[temp] == input[i])
					{
						count[temp] ++;
						break;
					}
					temp --;
				}
			}
		}
	}
	for(i=0; i<index; i++)
	{
		cout << output[i] << count[i];
	}
}



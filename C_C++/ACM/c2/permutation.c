#include<stdio.h>

int main()
{
	// so just 1 2 3 can multiply 3 in the range of 1 to 9
	// so permutation 123 to make 3-bit number
	for(int i=1; i<4; i++)
	{
		for(int j=1; j<10; j++)
		{
			if(i == j) continue;
			for(int k=1; k<10; k++)
			{
				if(k == i || k == j) continue;
				else
				{
					int unit = 100 * i + 10 * j + k;
					int unit_2 = 2 * unit;
					int unit_3 = 3 * unit;
					if(unit_3 >= 1000) continue;
					int k2 = unit_2 % 10;
					int j2 = (unit_2 / 10) % 10;
					int i2 = unit_2 / 100;
					int k3 = unit_3 % 10;
					int j3 = (unit_3 / 10) % 10;
					int i3 = unit_3 / 100;
					if(k2 == 0 || j2 == 0 || j3 == 0) continue;
					if(i == j2 || i == k2 || i == k3 || i == j3) continue;
					else if(j == i2 || j == k2 || j == j2 || j == k3 || j == j3 || j == i3) continue;
					else if(k == i2 || k == j2 || k == j3 || k == i3) continue;
					else if(i2 == k2 || i2 == j2 || i2 == k3 || i2 == j3) continue;
					else if(i3 == k3 || i3 == j3) continue;
					else if(k2 == j2 || k3 == j3) continue;
					else if(k2 == j3 || k3 == j2) continue;
					printf("%d %d %d\n", unit, unit_2, unit_3);
				}
			}
		}
	}
	return 0;
}

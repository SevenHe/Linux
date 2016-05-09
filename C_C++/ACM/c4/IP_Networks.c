#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<inttypes.h>	/* FOR PRINT STDINT */
#include<math.h>

/*
 * 解决思路是找到一个最短前缀，即所有IP地址共同的1；
 * 然后一个最长前缀，相较于最短，从第一块开始判断从哪一块分地址即可，掩码改变处前面为1，后面为0.
 * The way of thinking is to find a shortest prefix, to get the subnet.
 * This is because the ip in the same subnet has the same network address, so that is the prefix.
 * And find a longest prefix to subtract the shortest one from left to right,
 * Then the difference is the min length. Shift with the binary knowledge, and finally get the answer.
 */

uint8_t shift(uint8_t max, uint8_t sn)
{
	uint8_t pos = log2(max-sn);
	//printf("max = %" PRIu8 ", subnet = %" PRIu8 "\n", max, sn);
	uint8_t mask = 255;
	pos = (max-sn) == 0 ? pos : (pos+1);
	while(pos != 0)
	{
		mask <<= 1;
		//printf("pos = %" PRIu8 ", mask = %" PRIu8 "\n", pos, mask);
		pos --;
	}

	return mask;
}


int main()
{
	/*
	uint8_t A[1024],B[1024],C[1024],D[1024];
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));
	memset(C, 0, sizeof(C));
	memset(D, 0, sizeof(D));
	//printf("get: %"PRIu16"\n", ..);
	*/
	unsigned short n;
	while(scanf("%hu", &n) != EOF)
	{
		uint8_t snA = 255, maxA = 0;
		uint8_t snB = 255, maxB = 0;
		uint8_t snC = 255, maxC = 0;
		uint8_t snD = 255, maxD = 0;
		for(int i=0; i<n; i++)
		{
			char ip[15];
			uint8_t tempA,tempB,tempC,tempD;
			memset(ip, 0, sizeof(ip));
			scanf("%s", ip);
			char* temp = ip;
			tempA = atoi(temp);
			while(*temp != '.' && *temp != '\0') temp++;
			tempB = atoi(++temp);
			while(*temp != '.' && *temp != '\0') temp++;
			tempC = atoi(++temp);
			while(*temp != '.' && *temp != '\0') temp++;
			tempD = atoi(++temp); 
			//printf("get an ip: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ".%" PRIu8 "\n", tempA, tempB, tempC, tempD);
			snA &= tempA;
			snB &= tempB;
			snC &= tempC;
			snD &= tempD;
			if(tempA > maxA)
			{
				maxA = tempA;
				maxB = tempB;
				maxC = tempC;
				maxD = tempD;
			}
			else if(tempA == maxA)
			{
				if(tempB > maxB)
				{
					maxB = tempB;
					maxC = tempC;
					maxD = tempD;
				}
				else if(tempB == maxB)
				{
					if(tempC > maxC)
					{
						maxC = tempC;
						maxD = tempD;
					}
					else if(tempC == maxC)
					{
						if(tempD > maxD)
							maxD = tempD;
					}
				}
			}
		}
		uint8_t maskD,maskC,maskB,maskA;
		maskA = maskB = maskC = maskD = 255;
		if((maskA = shift(maxA, snA)) != 255)
		{
			maskB = maskC = maskD = 0;
			snB &= maskB;
			snC &= maskC;
			snD &= maskD;
		}
		else
		{
			if((maskB = shift(maxB, snB)) != 255)
			{
				maskC = maskD = 0;
				snC &= maskC;
				snD &= maskD;
			}
			else
			{
				if((maskC = shift(maxC, snC)) != 255)
				{
					maskD = 0;
					snD &= maskD;
				}
				else
				{
					maskD = shift(maxD, snD);
					snD &= maskD;
				}
			}
		}
		printf("%" PRIu8 ".%" PRIu8 ".%" PRIu8 ".%" PRIu8 "\n", snA, snB, snC, snD);
		printf("%" PRIu8 ".%" PRIu8 ".%" PRIu8 ".%" PRIu8 "\n", maskA, maskB, maskC, maskD);
	}

	return 0;
}

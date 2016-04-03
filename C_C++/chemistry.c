#include <stdio.h>
#include <stdlib.h>

int main() 
{
	float *x, *y0, *y1, *y2, *yy;
	float *a0, *a1, *a2;
	float h,h2;
	int i,n;
	printf("N = ");
	scanf("%d", &n);
	x = (float*)malloc((n+1)*sizeof(float));
	for(i=0; i<n; i++)
	{
		x[i] = 0;
		printf("index%d=%1.4f \n", i, x[i]);
	}
	free(x);
	return 0;
}
		

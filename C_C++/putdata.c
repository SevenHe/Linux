#include <stdio.h>
#include "putdata.h"

void putdata(int n, int k, double data)
{
	char prompt[100];
	sprintf(prompt, "The kind of the used samples %d in the whole %d is %.0lf\n", n, k, data);
	puts(prompt);
}	

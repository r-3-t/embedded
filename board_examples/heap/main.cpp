
#include <stdlib.h>


int main(void)
{
	unsigned char* heap_size = 0;
	int ctr = 0;

	while (malloc(1024) != 0)
	{
		ctr++;
		heap_size += 1024;
	}


	while (1);

	return 1;
}

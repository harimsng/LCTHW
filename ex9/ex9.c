#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 25;
	while (i > 0) {
		if (i > 9)
			printf("'%d", i);
		else
			printf("%d", i);
		i--;
	}

	return 0;
}

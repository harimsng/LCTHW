#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("ERROR: You need more than one argument.\n");
		return 1;
	}
	for (int i = 1; i < argc; ++i)
	{
		for (int j = 0, letter; argv[i][j] != '\0'; ++j)
		{
			letter = argv[i][j];
			if (letter >= 'A' && letter <= 'Z')
				letter += 32;
			switch (letter) {
				case 'a':
					printf("%d,%d: '%c'\n", i, j, argv[i][j]);
					break;
				case 'e':
					printf("%d,%d: '%c'\n", i, j, argv[i][j]);
					break;
				case 'i':
					printf("%d,%d: '%c'\n", i, j, argv[i][j]);
					break;
				case 'o':
					printf("%d,%d: '%c'\n", i, j, argv[i][j]);
					break;
				case 'u':
					printf("%d,%d: '%c'\n", i, j, argv[i][j]);
					break;
				case 'y':
					if (j > 2) {
						printf("%d,%d: '%c'\n", i, j, argv[i][j]);
					}
					break;
				default:
					printf("%d,%d: %c is not a vowel\n", i, j, argv[i][j]);
			}
		}
	}

	return 0;
}

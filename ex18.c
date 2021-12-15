#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

/** Our old friend die from ex17. */
void	die(const char *message)
{
	if (errno)
		perror(message);
	else
		printf("ERROR: %s\n", message);

	exit(1);
}

typedef int	(*compare_cb)(int a, int b);

int	*bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int		temp = 0;
	int		i = 0;
	int		j = 0;
	int		*target = malloc(count * sizeof(int));

	// selection sort is stable if new space was provided.
	// bubble sort
	// while (i < count)
	// {
	// 		j = 0;
	//		while (j < count - 1)
	//		{
	//			if (cmp(numbers[j], numbers[j + 1]) > 0)
	//			{
	//				temp = numbers[j];
	//				numbers[j] = numbers[j + 1];
	//				numbers[j + 1] = temp;
	//			}
	//			++j;
	//		}
	//		++i;
	// }
	// memcpy(target, numbers, count);

	// selection sort with additional O(n) space
	while (i < count - 1)
	{
		int		min = i;
		j = i + 1;
		while (j < count)
		{
			if (cmp(numbers[min], numbers[j]) < 0)
				min = j;
			++j;
		}
		target[i] = numbers[min];
	}
}

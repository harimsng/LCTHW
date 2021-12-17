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

int	*selection_sort(int *numbers, int count, compare_cb cmp)
{
//	int		temp = 0;
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
		++i;
	}
	return (target);
}

int	sorted_order(int a, int b)
{
	return (a - b);
}

int	reverse_order(int a, int b)
{
	return (b - a);
}

int	strange_order(int a, int b)
{
	if (a == 0 || b == 0) {
		return (0);
	} else {
		return (a % b);
	}
}

/*
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void	test_sorting(int *numbers, int count, compare_cb cmp)
{
	int	i = 0;
	int	*sorted = selection_sort(numbers, count, cmp);
	
	if (!sorted)
		die("Failed to sort as required.");

	for (i = 0; i < count; ++i) {
		printf("%d ", sorted[i]);
	}
	printf("\n");

	free(sorted);
}

int	main(int argc, char *argv[])
{
	if (argc < 2)
		die("USAGE: ex18 4 3 1 5 6");

	int	i = 0;
	int count = argc - 1;
	int	*numbers = malloc(sizeof(int) * count);
	if (!numbers)
		die("Memory error.");

	for (i = 0; i < count; ++i)
	{
		numbers[i] = atoi(argv[i + 1]);
	}

	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);

	free(numbers);

	return (0);
}

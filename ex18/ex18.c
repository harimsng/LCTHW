#include "dbg.h"
#include <time.h>
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
	int	i = 0;
	int j = 0;
	int	*target = malloc(sizeof(int) * count);

	 memcpy(target, numbers, sizeof(int) * count);
	 i = 0;
	 while (i < count)
	 {
	 		j = 0;
			while (j < count - 1)
			{
				if (cmp(target[j], target[j + 1]) > 0)
				{
					int temp = target[j];
					target[j] = target[j + 1];
					target[j + 1] = temp;
				}
				++j;
			}
			++i;
	 }
	 return (target);
}

int	*insertion_sort(int *numbers, int count, compare_cb cmp)
{
	int		i = 0;
	int		j = 0;
	int		*target = malloc(sizeof(int) * count);

	memcpy(target, numbers, sizeof(int) * count);
	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j > 0)
		{
			if (cmp(target[j], target[j - 1]) < 0)
			{
				int temp = target[j];
				target[j] = target[j - 1];
				target[j - 1] = temp;
			}
			--j;
		}
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
	int	*sorted1;
	int	*sorted2;
	clock_t	start, end;
	double	time1, time2;

	start = clock();
	sorted1 = bubble_sort(numbers, count, cmp);
	end = clock();
	time1 = (double)(end - start) / CLOCKS_PER_SEC;

	start = clock();
	sorted2 = insertion_sort(numbers, count, cmp);
	end = clock();
	time2 = (double)(end - start) / CLOCKS_PER_SEC;
//	unsigned char	*data = (unsigned char *)cmp;
	
	if (!sorted1 || !sorted2)
		die("Failed to sort as required.");

	printf("\nsorting algorithm comparison\n");

	printf("first : %f, second : %f\n", time1, time2);
//	printf("first sorting algorithm\n");
//	for (i = 0; i < count; ++i) {
//		printf("%d ", sorted1[i]);
//	}
//
//	printf("second sorting algorithm\n");
//	for (i = 0; i < count; ++i) {
//		printf("%d ", sorted2[i]);
//	}
//
//	for (i = 0; i < 25; ++i) {
//		printf("%02x:", data[i]);
//	}
//	printf("\n");

	free(sorted1);
	free(sorted2);
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

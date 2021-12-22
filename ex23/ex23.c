// From the result of my_device speed test,
// the speed of combination of pointer arithmatic and dereference
// is faster than using array index.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dbg.h"

#define SWITCH_DUPLICATE(N) case (N): *dest++ = *src++;\
case (N+1): *dest++ = *src++;\
case (N+2): *dest++ = *src++;\
case (N+3): *dest++ = *src++;\
case (N+4): *dest++ = *src++;\
case (N+5): *dest++ = *src++;\
case (N+6): *dest++ = *src++;\
case (N+7): *dest++ = *src++;

#define SWITCH_DOUBLE_DUP(N) SWITCH_DUPLICATE(N)\
SWITCH_DUPLICATE(N + 8)\
SWITCH_DUPLICATE(N + 16)\
SWITCH_DUPLICATE(N + 24)\
SWITCH_DUPLICATE(N + 32)\
SWITCH_DUPLICATE(N + 40)\
SWITCH_DUPLICATE(N + 48)\
SWITCH_DUPLICATE(N + 56)

#define LOOP_DUPLICATE *dest++ = *src++;\
*dest++ = *src++;\
*dest++ = *src++;\
*dest++ = *src++;\
*dest++ = *src++;\
*dest++ = *src++;\
*dest++ = *src++;\
*dest++ = *src++;

#define	TEST_SIZE (10000000)
#define	TEST_BIT (128)

typedef struct
{
	long long int	data[16];
}		t_word;

typedef	size_t	(*t_copy_func)(char *, char *, size_t);

size_t	copy_comp(t_copy_func copy_func, char *dest, char *src, size_t count);
size_t	normal_copy(char *dest, char *src, size_t count);
size_t	normal_copy_with_pointer(char *dest, char *src, size_t count);
size_t	duffs_device(char *dest, char *src, size_t count);
size_t	zeds_device(char *dest, char *src, size_t count);
size_t	my_device(char *dest, char *src, size_t count);
int		valid_copy(char *data, size_t count, char expects);

int	main(int argc, char *argv[])
{
//	char	dest[TEST_SIZE] = {'a', };
//	char	src[TEST_SIZE] = {'c', };
	char	*dest = malloc(TEST_SIZE);
	char	*src = malloc(TEST_SIZE);
	int		rc = 0;
	clock_t	start, end;
	double	time_measure;
	
	// set up the src to have some stuff
	memset(src, 'x', TEST_SIZE);
	// set dest to a failure mode
	memset(dest, 'y', TEST_SIZE);
	CHECK(valid_copy(dest, TEST_SIZE, 'y'), "Not initialized right.");

	// normal copy
	LOG_INFO("normal copy");
	rc = copy_comp(normal_copy, dest, src, TEST_SIZE);
	CHECK(rc == TEST_SIZE, "Normal copy failed: %d", rc);
	CHECK(valid_copy(dest, TEST_SIZE, 'x'), "Normal copy failed.");

	// reset
	memset(dest, 'y', TEST_SIZE);

	// normal copy with pointer
	LOG_INFO("normal copy with pointer");
	rc = copy_comp(normal_copy_with_pointer, dest, src, TEST_SIZE);
	CHECK(rc == TEST_SIZE, "Normal copy with pointer failed: %d", rc);
	CHECK(valid_copy(dest, TEST_SIZE, 'x'), "Normal copy with pointer failed.");

	// reset
	memset(dest, 'y', TEST_SIZE);

	// duffs version
	LOG_INFO("duffs version");
	rc = copy_comp(duffs_device, dest, src, TEST_SIZE);
	CHECK(rc == TEST_SIZE, "duffs copy failed: %d", rc);
	CHECK(valid_copy(dest, TEST_SIZE, 'x'), "duffs copy failed.");

	// reset
	memset(dest, 'y', TEST_SIZE);

	// zeds version
	LOG_INFO("zeds version");
	rc = copy_comp(zeds_device, dest, src, TEST_SIZE);
	CHECK(rc == TEST_SIZE, "zeds copy failed: %d", rc);
	CHECK(valid_copy(dest, TEST_SIZE, 'x'), "zeds copy failed.");

	// reset
	memset(dest, 'y', TEST_SIZE);

	// my version
	LOG_INFO("my version");
	rc = copy_comp(my_device, dest, src, TEST_SIZE);
	CHECK(rc == TEST_SIZE, "my copy failed: %d", rc);
	CHECK(valid_copy(dest, TEST_SIZE, 'x'), "my copy failed.");

	// reset
	memset(dest, 'y', TEST_SIZE);

	// memcpy
	LOG_INFO("memcpy");
	start = clock();
	memcpy(dest, src, TEST_SIZE);
	end = clock();
	time_measure = (double)(end - start) / CLOCKS_PER_SEC;
	LOG_INFO("copy time taken : %f", time_measure);
	CHECK(valid_copy(dest, TEST_SIZE, 'x'), "memcpy failed.");

	// reset
	memset(dest, 'y', TEST_SIZE);

	// memmove
	LOG_INFO("memmove");
	start = clock();
	memmove(dest, src, TEST_SIZE);
	end = clock();
	time_measure = (double)(end - start) / CLOCKS_PER_SEC;
	LOG_INFO("copy time taken : %f", time_measure);
	CHECK(valid_copy(dest, TEST_SIZE, 'x'), "memmove failed.");

	// memset
	LOG_INFO("memset");
	start = clock();
	memset(dest, 'y', TEST_SIZE);
	end = clock();
	time_measure = (double)(end - start) / CLOCKS_PER_SEC;
	LOG_INFO("copy time taken : %f", time_measure);
	CHECK(valid_copy(dest, TEST_SIZE, 'y'), "memset failed.");

	return (0);
error:
	return (1);
}

size_t	copy_comp(t_copy_func copy_func, char *dest, char *src, size_t count)
{
	clock_t	start, end;
	double 	time_measure;
	size_t	ret = 0;

	start = clock();
	ret = copy_func(dest, src, count);
	end = clock();
	time_measure = (double)(end - start) / CLOCKS_PER_SEC;
	LOG_INFO("copy time taken : %f", time_measure);
	return (ret);
}

size_t	normal_copy(char *dest, char *src, size_t count)
{
	size_t	i = 0;

	for (i = 0; i < count; ++i)
		dest[i] = src[i];

	return (i);
}

size_t	normal_copy_with_pointer(char *dest, char *src, size_t count)
{
	size_t	iteration = count;

	while (iteration-- > 0)
		*dest++ = *src++;
	return (count);
}

size_t	duffs_device(char *dest, char *src, size_t count)
{
	if (count == 0)
		return (0);
	{
		size_t	n = (count + TEST_BIT - 1) / TEST_BIT;
	
		switch (count % TEST_BIT) {
			case 0:
				do {
					*dest++ = *src++;
					SWITCH_DOUBLE_DUP(64)
					SWITCH_DUPLICATE(56)
					SWITCH_DUPLICATE(48)
					SWITCH_DUPLICATE(40)
					SWITCH_DUPLICATE(32)
					SWITCH_DUPLICATE(24)
					SWITCH_DUPLICATE(16)
					SWITCH_DUPLICATE(8)
					case 7:
					*dest++ = *src++;
					case 6:
					*dest++ = *src++;
					case 5:
					*dest++ = *src++;
					case 4:
					*dest++ = *src++;
					case 3:
					*dest++ = *src++;
					case 2:
					*dest++ = *src++;
					case 1:
					*dest++ = *src++;
				} while (--n > 0);
		}
	}

	return (count);
}

size_t	zeds_device(char *dest, char *src, size_t count)
{
	if (count == 0)
		return (0);
	{
		size_t	n = (count + TEST_BIT - 1) / TEST_BIT;
	
		switch (count % TEST_BIT) {
			case 0:
repeat:			
				*dest++ = *src++;
				SWITCH_DOUBLE_DUP(64);
				SWITCH_DUPLICATE(56)
				SWITCH_DUPLICATE(48)
				SWITCH_DUPLICATE(40)
				SWITCH_DUPLICATE(32)
				SWITCH_DUPLICATE(24)
				SWITCH_DUPLICATE(16)
				SWITCH_DUPLICATE(8)
			case 7:
				*dest++ = *src++;
			case 6:
				*dest++ = *src++;
			case 5:
				*dest++ = *src++;
			case 4:
				*dest++ = *src++;
			case 3:
				*dest++ = *src++;
			case 2:
				*dest++ = *src++;
			case 1:
				*dest++ = *src++;
			if (--n > 0)
				goto repeat;
		}
	}

	return (count);
}

// when index was used, this function's speed was almost same as normal copy.
size_t	my_device(char *dest, char *src, size_t count)
{
	size_t			n = count / TEST_BIT;
	int				i = count % TEST_BIT;
	t_word			*dword, *sword;

	for (; i > 0; --i)
		*dest++ = *src++;
	dword = (t_word *)dest;
	sword = (t_word *)src;
	while (n-- > 0)
	{
/*		LOOP_DUPLICATE
		LOOP_DUPLICATE
		LOOP_DUPLICATE
		LOOP_DUPLICATE
		LOOP_DUPLICATE
		LOOP_DUPLICATE
		LOOP_DUPLICATE
		LOOP_DUPLICATE
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;
		*dword++ = *sword++;*/
		*dword++ = *sword++;
	}

	return (count);
}

int	valid_copy(char *data, size_t count, char expects)
{
	size_t	i = 0;

	while (i < count)
	{
		if (data[i] != expects)
		{
			LOG_ERR("[%zu] %c != %c", i, data[i], expects);
			return (0);
		}
			++i;
	}
	return (1);
}

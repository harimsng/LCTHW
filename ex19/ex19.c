#include "dbg.h"
#include <stdlib.h>
#include <stdio.h>

void	test_debug()
{
	// notice you don't need the \n
	DEBUG("I have Brown Hair.");

	// passing in arguments like printf
	DEBUG("I am %d years old.", 37);
}

void	test_log_err()
{
	LOG_ERR("I believe everything is broken.");
	LOG_ERR("There are %d problems in %s", 0, "space");
}

void	test_log_warn()
{
	LOG_WARN("You can safely ignore this.");
	LOG_WARN("Maybe consider looking at: %s.", "/etc/passwd");
}

void	test_log_info()
{
	LOG_INFO("Well I did something mundane.");
	LOG_INFO("It happend %f times today.", 1.3f);
}

int	test_check(char *file_name)
{
	FILE	*input = NULL;
	char	*block = NULL;

	block = malloc(100);
	CHECK_MEM(block); // should work

	input = fopen(file_name, "r");
	CHECK(input, "Failed to open %s.", file_name);

	free(block);
	fclose(input);
	return (0);

error:
	if (block)
		free(block);
	if (input)
		fclose(input);
	return (-1);
}

int	test_sentinel(int code)
{
	char	*temp = malloc(100);
	CHECK_MEM(temp);

	switch (code) {
		case 1:
			LOG_INFO("It worked.");
			break;
		default:
			SENTINEL("I shouldn't run.");
	}

	free(temp);
	return (0);

error:
	if (temp)
		free(temp);
	return (-1);
}

int	test_check_mem()
{
	char	*test = NULL;
	CHECK_MEM(test);

	free(test);
	return (1);

error:
	return (-1);
}

int	test_check_debug()
{
	int	i = 0;
	CHECK_DEBUG(i != 0, "Oops, I was 0.");

	return (0);
error:
	return (-1);
}

int	main(int argc, char *argv[])
{
	CHECK(argc == 2, "Need an argument.");

	test_debug();
	test_log_err();
	test_log_warn();
	test_log_info();

	CHECK(test_check("ex19.c") == 0, "failed with ex19.c");
	CHECK(test_check(argv[1]) == -1, "failed with argv");
	CHECK(test_sentinel(1) == 0, "test_sentinel failed.");
	CHECK(test_sentinel(100) == -1, "test_sentinel failed.");
	CHECK(test_check_mem() == -1, "test_check_mem failed.");
	CHECK(test_check_debug() == -1, "test_check_debug failed.");

	return (0);
error:
	return (1);
}

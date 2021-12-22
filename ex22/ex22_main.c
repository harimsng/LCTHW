#include "ex22.h"
#include "dbg.h"

static const char	*g_my_name = "Zed A. Shaw";

void	scope_demo(int count);

int	main(void)
{
	// test out g_age accessors
	LOG_INFO("my name: %s, age: %d", g_my_name, get_age());

	set_age(100);

	LOG_INFO("my name: %s, age: %d", g_my_name, get_age());

	// test out g_size extern
	LOG_INFO("size: %d", g_size);
	print_size();

	g_size = 0;

	LOG_INFO("size: %d", g_size);
	print_size();

	// test the ratio function static
	double	*addr;
	LOG_INFO("Ratio at first: %f", update_ratio(2.0, &addr));
	*addr = 15.5;
	LOG_INFO("Ratio again: %f", update_ratio(10.0, &addr));
	LOG_INFO("Ratio once more: %f", update_ratio(99.9, &addr));

	// test scope demo
	int		count = 4;
	scope_demo(count);
	scope_demo(count * 20);

	LOG_INFO("count after calling scope demo: %d", count);

	return (0);
}

void	scope_demo(int count)
{
	LOG_INFO("Count is: %d", count);
	if (count > 10) {
		int	count = 100;	// BAD! BUGS!

		LOG_INFO("Count in this scope: %d", count);
	}

	LOG_INFO("Count is at exit: %d", count);

	count = 1000;

	LOG_INFO("Count after assign: %d", count);
}

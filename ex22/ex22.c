#include <stdio.h>
#include "dbg.h"
#include "ex22.h"

int			g_size = 1000;
static int	g_age = 37;

int		get_age(void)
{
	return (g_age);
}

void	set_age(int	new_age)
{
	g_age = new_age;
}

double	update_ratio(double new_ratio, double **addr)
{
	static double	ratio = 1.0;

	double			old_ratio = ratio;

	*addr = &ratio;	
	ratio = new_ratio;
	return (old_ratio);
}

void	print_size(void)
{
	LOG_INFO("I think size is :%d", g_size);
}

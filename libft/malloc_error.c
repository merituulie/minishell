
#include "libft.h"

void	malloc_error(void)
{
	ft_putstr_fd("Memory allocation failed\n", 2, 1);
	exit(1);
}

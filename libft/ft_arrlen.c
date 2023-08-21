
#include "libft.h"

int	ft_arrlen(char **array)
{
	int	counter;

	counter = 0;
	while (*array)
	{
		counter++;
		array++;
	}
	return (counter);
}

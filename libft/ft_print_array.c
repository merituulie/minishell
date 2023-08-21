
#include "libft.h"

int	ft_print_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1, 0);
		ft_putstr_fd("\n", 1, 0);
		i++;
	}
	return (0);
}

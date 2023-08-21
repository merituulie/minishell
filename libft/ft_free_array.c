
#include "libft.h"

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		array[i] = NULL;
		i++;
	}
	if (array)
		free(array);
}

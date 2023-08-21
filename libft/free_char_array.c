
#include "libft.h"

void	free_char_array(char **str)
{
	int		i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
	if (str)
		free(str);
}

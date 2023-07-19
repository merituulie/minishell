#include "libft.h"

void	free_char_array(char **str)
{
	int		i;
	char	*input;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		input = str[i];
		free(input);
		i++;
	}
	free(str);
}

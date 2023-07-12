#include "libft.h"

void	freemystuff(char **str)
{
	int		i;
	char	*input;

	i = 0;
	if (str == NULL)
		exit(1);
	while (str[i])
	{
		input = str[i];
		free(input);
		i++;
	}
	free(str);
}
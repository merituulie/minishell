
#include "../../headers/minishell.h"

int	check_quote_cases(t_data **ms, char c)
{
	if (c == 34 && !(*ms)->s_quotes && !(*ms)->d_quotes)
		(*ms)->d_quotes = 1;
	else if (c == 34 && (*ms)->d_quotes)
		(*ms)->d_quotes = 0;
	else if (c == 39 && !(*ms)->s_quotes && !(*ms)->d_quotes)
		(*ms)->s_quotes = 1;
	else if (c == 39 && (*ms)->s_quotes)
		(*ms)->s_quotes = 0;
	else
		return (0);
	return (1);
}

char	**realloc_stack(char **str, int count)
{
	char	**cpy;
	int		i;
	int		j;

	cpy = (char **)ft_calloc(count + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (i < count)
	{
		if (str[j] != NULL)
		{
			cpy[i] = ft_strdup(str[j]);
			i++;
		}
		free(str[j]);
		j++;
	}
	free(str);
	return (cpy);
}

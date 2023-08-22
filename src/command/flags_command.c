
#include "../../headers/minishell.h"

char	*parse_flags(char **input, int	*index)
{
	int	cur_index;

	cur_index = *index;
	if (input[*index][0] == '-')
	{
		(*index)++;
		return (input[cur_index]);
	}
	else
		return (NULL);
}

void	put_to_flags(t_command **cmd, int track, char *str)
{
	if (!str)
		(*cmd)[track].flags = NULL;
	else
	{
		(*cmd)[track].flags = ft_strdup(str);
		if (!(*cmd)[track].flags)
			malloc_error();
	}
}

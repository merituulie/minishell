
#include "../../headers/parsing.h"

void	delete_quotes2(char *str, int index, int size, t_data *ms)
{
	int	i;

	i = 0;
	index = 0;
	while (i < size && str[index + i])
	{
		if (((index + i) == ms->start || (index + i) == ms->end) \
								&& ms->start != ms->end - 1)
			index++;
		else if ((index + i) == ms->start && ms->start == ms->end - 1)
			index = index + 2;
		if (!str[index + i])
			break ;
		ms->out[i] = str[index + i];
		i++;
	}
	ms->out[i] = '\0';
}

/*reallocate the string and delete the first matching quotes*/
void	delete_quotes(char *str, int index, int size, t_data *ms)
{
	char	quote;

	quote = str[index];
	ms->start = index;
	while (str[++index])
	{
		if (str[index] == quote)
		{
			size = size - 2;
			break ;
		}
	}
	ms->end = index;
	ms->out = ft_calloc(size + 1, sizeof(char));
	if (!ms->out)
		malloc_error();
	delete_quotes2(str, index, size, ms);
}

static void	delete_quotes_fname(char **str, t_data *ms, int i, int j)
{
	delete_quotes(str[i], j, ft_strlen(str[i]), ms);
	free(str[i]);
	str[i] = ft_strdup(ms->out);
	if (!str[i])
		malloc_error();
	free(ms->out);
	ms->out = NULL;
	j = ms->end - 2;
}

/**
 * @brief check if the str has double quotes that comes after redir.
 * Only quotes for the file names are removed here.
 */
char	**concatenate(char **str, t_data *ms)
{
	int	i;
	int	j;

	i = -1;
	quotes_init(ms);
	while (str[++i])
	{
		if (ft_strchr_null("<>", str[i][0]))
		{
			i++;
			j = -1;
			while (str[i][++j])
			{
				if (str[i][j] == 34 || str[i][j] == 39)
				{
					delete_quotes_fname(str, ms, i, j);
				}
				if (str[i][0] == '\0')
					break ;
			}
		}
	}
	return (str);
}

//This function help for the line too long in expand_env.c:
int	extend_expand_quote_check2(t_data *ms, char **str)
{
	str[ms->i] = ft_strdup(expand_var(ms, str[ms->i], ms->j));
	if (!str[ms->i])
		return (1);
	if (ms->out)
	{
		free(ms->out);
		ms->out = NULL;
	}
	if (ms->end - 1 >= (int)ft_strlen(str[ms->i]))
		return (1);
	ms->j = ms->end - 1;
	return (0);
}

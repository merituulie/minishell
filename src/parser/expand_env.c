/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:53:38 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/03 17:01:55 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../libft/libft.h"
#include <string.h>

/*check if the word comes after '$' is expandable part
using env variables.*/
void	expand_var(t_data *ms, char *str, int start)
{
	char	*var;

	ms->start = start;
	ms->end = start + 1;
	if (!ft_isalnum(str[ms->end]))
	{
		ms->out = ft_calloc(0, sizeof(char));
		return ;
	}
	while (ft_isalnum(str[ms->end]))
			ms->end++;
	printf("str[end] is %c\n", str[ms->end]);
	var = ft_substr(str, ms->start, ms->end - ms->start);
	if (!var)
		printf(" malloc fail!\n");
	printf("var is %s\n", var);
	realloc_var(ms, str, var, ft_strlen(str));
	free(var);
}

 /*finding matching variable and send the value back.
	 If no matches, return NULL*/
char	*find_env(t_data *ms, char *var, int var_size)
{
	int		i;
	// t_node	*node;
	char	*search;

	i = -1;
	var_size--;
	search = ft_calloc(var_size, sizeof(char));
	while (i++ < var_size)
		search[i] = var[1 + i];
	printf("var without $, search str is: %s\n", search);
	// i = 0;
	// node = get_value((ms->env)->vars, search);
	// return (node->value);
	// free(search);
	// return(NULL);
	// -----from here down, this is just to check before env is ready, the codes
	// commented out is the version for the minishell------
	i = 0;
	while (ms->env[i])
	{
		if (!ft_strncmp(ms->env[i], search, ft_strlen(search)))
		{
			printf("expanded to environment variables\n");
			free(search);
			return (ms->env[i]);
		}
		i++;
	}
	printf("no variables. null string\n");
	free(search);
	return (NULL);
}

/*takes back the expanded result from '$something'
and append it to original string in its space*/
void	realloc_var(t_data *ms, char *str, char *var, int old_size)
{
	int		leftover;
	int		new_size;
	char	*new;
	int		i;

	printf("realloc var is %s\n", var);
	printf("old_size is %d\n", old_size);
	new = find_env(ms, var, ft_strlen(var));
	printf("new is %s\n", new);
	new_size = ft_strlen(str) - ft_strlen(var) + ft_strlen(new);
	printf("new_size is %d\n", new_size);
	ms->out = ft_calloc(new_size, sizeof(char));
	ms->out = ft_memcpy(ms->out, str, ms->start);
	printf("memcpy after ms->out is %s\n", ms->out);
	printf("ms->start is %d\n", ms->start);
	i = 0;
	while (new[i])
	{
		ms->out[ms->start + i] = new[i];
		i++;
	}
	printf("append env expand ms->out is %s\n", ms->out);
	leftover = ms->start + i;
	i = 0;
	printf("str[ms->end + i] is %c\n", str[ms->end + i]);
	while ((leftover + i) < new_size)
	{
		ms->out[leftover + i] = str[ms->end + i];
		i++;
	}
	printf("ms->out is %s\n", ms->out);
}

/*check the occurence of double quotes '"'
s_quotes is single quote, d_quote is double quote.
s_quotes will be 1 if it happens before d_quotes but if it closes,
it will become 0.
expanding to env only happens if there is $ and something after, and
if there is no single quote in front of it. it does not count if double quote
exists or not.*/
char	**expand_quote_check(t_data *ms, char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 34 && !ms->s_quotes)
			{
				printf("d_quote = 1, str[%d][%d] is %c\n", i, j, str[i][j]);	
				ms->d_quotes = 1;
			}
			else if (str[i][j] == 39 && !ms->s_quotes && !ms->d_quotes)
			{
				printf("s_quote = 1, str[%d][%d] is %c\n", i, j, str[i][j]);
				ms->s_quotes = 1;
			}
			else if (str[i][j] == 39 && ms->s_quotes)
			{
				printf("s_quote = 0, matched! str[%d][%d] is %c\n", i, j, str[i][j]);
				ms->s_quotes = 0;
			}
			else if (str[i][j] == '$' && !ms->s_quotes)
			{
				printf("s_quote no exist! str[%d][%d] is %c\n", i, j, str[i][j]);
				expand_var(ms, str[i], j);
				free(str[i]);
				str[i] = ft_strdup(ms->out);
				free(ms->out);
				printf("Final print is %s\n", str[i]);
				break ;
			}
		}
	}
	return (str);
}

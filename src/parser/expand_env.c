/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:53:38 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/16 10:40:09 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../headers/hashmap.h"
#include "../../headers/minishell.h"
#include "../../headers/parsing.h"

/*check if the word comes after '$' is expandable part
using env variables.*/
char	*expand_var(t_data *ms, char *str, int start)
{
	char	*var;

	var = expand_var_init(ms, str, start);
	if (str[ms->end] == '?')
	{
		var = ft_strdup("$?");
		ms->end++;
	}
	else if (str[ms->end] != ' ' && !ft_isalnum(str[ms->end]))
		return (special_expand(ms, str));
	else if (str[ms->end] == ' ')
	{
		ms->out = ft_strdup(str);
		free(str);
		return (ms->out);
	}
	while (ft_isalnum(str[ms->end]))
		ms->end++;
	if (!var)
		var = ft_substr(str, ms->start, ms->end - ms->start);
	if (!var)
		return (NULL);
	realloc_var(ms, str, var, ft_strlen(str));
	free(str);
	return (ms->out);
}

/*finding matching variable and send the value back
 If no matches, return NULL*/
char	*find_env(t_data *ms, char *var, int var_size)
{
	int		i;
	t_node	*node;
	char	*search;

	i = -1;
	if (!ft_strncmp_all(var, "$?"))
		return (get_exit_code());
	var_size--;
	search = ft_calloc(var_size + 1, sizeof(char));
	if (!search)
		ft_putstr_fd("Memory allocation failure!\n", 2, 1);
	while (i++ < var_size)
		search[i] = var[1 + i];
	i = 0;
	node = get_value((ms->env)->vars, search);
	free(search);
	if (!(node))
		return (NULL);
	search = ft_strdup(node->value);
	if (!search)
		ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
	return (search);
}

/*takes back the expanded result from '$something'
and append it to original string in its space*/
void	realloc_var(t_data *ms, char *str, char *var, int size)
{
	int		leftover;
	char	*new;

	new = find_env(ms, var, ft_strlen(var));
	size = count_size(str, var, new);
	if (size == 0)
		ms->out = NULL;
	else
	{
		ms->out = ft_calloc(size + 1, sizeof(char));
		if (!ms->out)
			return ;
		ms->out = ft_memcpy(ms->out, str, ms->start);
		leftover = ms->start;
		if (new)
		{
			ms->k = -1;
			while (new[++(ms->k)])
				ms->out[ms->start + ms->k] = new[ms->k];
			leftover = ms->start + ms->k;
			free(new);
		}
		realloc_var2(ms, leftover, size, str);
	}
	free(var);
}

// the function extend expand quote check2 is in the 
// concatenate.c:
static char	**expand_quote_check2(t_data *ms, char **str)
{
	while (str[++(ms->i)])
	{
		ms->j = -1;
		while (str[ms->i][++(ms->j)])
		{
			if (str[ms->i][ms->j] == 34 && !ms->s_quotes && !ms->d_quotes)
				ms->d_quotes = 1;
			else if (str[ms->i][ms->j] == 34 && ms->d_quotes)
				ms->d_quotes = 0;
			else if (str[ms->i][ms->j] == 39 && !ms->s_quotes && !ms->d_quotes)
				ms->s_quotes = 1;
			else if (str[ms->i][ms->j] == 39 && ms->s_quotes)
				ms->s_quotes = 0;
			else if (str[ms->i][ms->j] == '$' && str[ms->i][ms->j + 1] \
													&& !ms->s_quotes)
			{
				str[ms->i] = ft_strdup(expand_var(ms, str[ms->i], ms->j));
				if (break_in_expand_quote(str[ms->i], ms) == -1)
					break ;
				ms->j = ms->end - 1;
			}
		}
	}
	return (str);
}

/*check the occurence of double quotes '"'
s_quotes is single quote, d_quote is double quote.
s_quotes will be 1 if it happens before d_quotes but if it closes,
it will become 0.
Expanding to env only happens if there is $ and something after, and
if there is no single quote in front of it. it does not count if double quote
exists or not.*/

char	**expand_quote_check(t_data *ms, char **str)
{
	char	**res;

	ms_init(ms);
	ms->i = -1;
	res = expand_quote_check2(ms, str);
	if (res == NULL)
		return (NULL);
	return (res);
}

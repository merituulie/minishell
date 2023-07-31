/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:53:38 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/30 13:11:44 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../libft/libft.h"

/*check if the word comes after '$' is expandable part
using env variables.*/
char	*expand_var(t_data *ms, char *str, int start)
{
	char	*var;

	ms->start = start;
	ms->end = start + 1;
	var = NULL;
	if (str[ms->end] == '?')
		var = ft_strdup("$?");
	else if (!ft_isalnum(str[ms->end]))
		return ("");
	while (ft_isalnum(str[ms->end]))
		ms->end++;
	if (var)
		ms->end++;
	else
		var = ft_substr(str, ms->start, ms->end - ms->start);
	if (!var)
		return (NULL);
	realloc_var(ms, str, var, ft_strlen(str));
	free(var);
	free(str);
	if (!(ms->out))
		return (NULL);
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
		return (get_exit_value());
	var_size--;
	search = ft_calloc(var_size, sizeof(char));
	if (!search)
		return (NULL); // printf("allocation fail!\n");
	while (i++ < var_size)
		search[i] = var[1 + i];
	i = 0;
	node = get_value((ms->env)->vars, search);
	if (!(node))
		return (NULL);
	free(search);
	return (node->value);
}

/*takes back the expanded result from '$something'
and append it to original string in its space*/
void	realloc_var(t_data *ms, char *str, char *var, int size)
{
	int		leftover;
	char	*new;

	new = find_env(ms, var, ft_strlen(var));
	if (!new)
		size = ft_strlen(str) - ft_strlen(var);
	else
		size = ft_strlen(str) - ft_strlen(var) + ft_strlen(new);
	ms->out = ft_calloc(size, sizeof(char));
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
	}
	ms->k = -1;
	while ((leftover + (++(ms->k))) < size)
		ms->out[leftover + ms->k] = str[ms->end + ms->k];
	ms->out[leftover + ms->k] = '\0';
	ms->end = leftover;
}

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
			else if (str[ms->i][ms->j] == '$' && !ms->s_quotes)
			{
				str[ms->i] = ft_strdup(expand_var(ms, str[ms->i], ms->j));
				if (!str[ms->i])
					return(NULL);
				free(ms->out);
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
expanding to env only happens if there is $ and something after, and
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

// char	**expand_quote_check(t_data *ms, char **str)
// {
// 	ms_init(ms);
// 	ms->i = -1;
// 	return (expand_quote_check2(ms, str));
// }

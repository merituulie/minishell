/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:53:38 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/25 07:18:31 by jhusso           ###   ########.fr       */
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
	if (!ft_isalnum(str[ms->end])) //
	{
		ms->out = ft_calloc(0, sizeof(char));
		if (!(ms->out))
			//PROTECT
		return (ms->out);
	}
	while (ft_isalnum(str[ms->end]))
			ms->end++;
	var = ft_substr(str, ms->start, ms->end - ms->start);
	if (!var)
		//PROTECT
	realloc_var(ms, str, var, ft_strlen(str)); // returns what if failed?
	free(var);
	free(str);
	ms->out = ft_strdup();
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
	var_size--;
	search = ft_calloc(var_size, sizeof(char)); // protect
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
	int		i;

	new = find_env(ms, var, ft_strlen(var));
	if (!new)
		size = ft_strlen(str) - ft_strlen(var); // what case is this?
	else
		size = ft_strlen(str) - ft_strlen(var) + ft_strlen(new);
	ms->out = ft_calloc(size, sizeof(char)); //PROTECT
	ms->out = ft_memcpy(ms->out, str, ms->start);
	leftover = ms->start;
	if (new)
	{
		i = -1;
		while (new[++i])
			ms->out[ms->start + i] = new[i];
		leftover = ms->start + i;
	}
	i = -1;
	while ((leftover + (++i)) < size)
		ms->out[leftover + i] = str[ms->end + i];
	ms->out[leftover + i] = '\0'; // is needed? already calloced
	ms->end = leftover;
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
	ms_init(ms);
	ms->i = -1;
	while (str[++(ms->i)])
	{
		ms->j = -1;
		// quotes_init(ms);
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
				str[ms->i] = expand_var(ms, str[ms->i], ms->j); // this segfaults if expand_var returns NULL or 0
				// needs to be protected because expand_var is allocating memory!
				free(ms->out);
				ms->j = ms->end - 1;
			}
		}
	}
	return (str);
}

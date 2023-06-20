/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enxpand_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:53:38 by meskelin          #+#    #+#             */
/*   Updated: 2023/06/20 14:01:01 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

/*finding matching variable and send the value back.
If no matches, return NULL*/
char	*find_env(t_data ms, char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ms.env->key == str[i])
			return (ms.env->value);
		i++;
	}
	return (NULL);
}

/*check if the word comes after '$' is expandable part
using env variables. */
char	*expand_var(t_data ms, char *str, int start)
{
	int		end;
	int		start;
	char	*var;

	end = start + 1;
	if (!ft_isalnum(str[end]))
		return ;
	while (ft_isalnum(str[end]))
			end++;
	var = ft_substr(str, start, end - start);
	if (!var)
		return (malloc_failure);
	var = find_env(ms, var);
	//realloc the string and send it back.
}

/*check the occurence of double quotes '"'
s_quotes is single quote, d_quote is double quote.
s_quotes will be 1 if it happens before d_quotes but if it closes,
it will become 0.
expanding to env only happens if there is $ and something after, and
if there is no single quote in front of it. it does not count if double quote
exists or not.*/
char	**expand_quote_check(t_data ms, char **str)
{
	int	i;
	int	j;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	s_quotes = 0;
	d_quotes = 0;
	while (str[i][j])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '\"')
				d_quotes = 1;
			else if (str[i][j] == '\'' && !d_quotes)
				s_quotes = 1;
			else if (str[i][j] == '$' && str[i][j + 1] && !s_quotes)
				str[i] = expand_var(ms, str[i], i);
			else if (str[i][j] == '\'' && s_quotes == 1)
				s_quotes = 0;
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	ms;
	char	**str;

	str = malloc(sizeof(char *) * 10);
	str[0] = ft_strdup("<file1");
	str[1] = "wc";
	str[2] = "-l";
	str[3] = "|";
	str[4] = ">";
	str[5] = "file2";
	str[6] = "\"$user it's me hi I'm the problem it's me\"";
	str[6] = "hel\"lo'$userit'smehi\" I'm the problem it's me'";
	str[7] = "user'name\"$user\"?hds'af";
	str[8] = NULL;
	(void)argc;
	(void)argv;
	ms.env = envp;

	return (0);
}

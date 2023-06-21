/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enxpand_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:53:38 by meskelin          #+#    #+#             */
/*   Updated: 2023/06/21 11:25:57 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

/*finding matching variable and send the value back.
If no matches, return NULL*/
char	*find_env(t_data ms, char *var)
{
	int	i;

	i = 0;
	while (ms.env->key[i])
	{
		if (ms.env->key[i] == var)
			return (ms.env->value[i]);
		i++;
	}
	return (NULL);
}

/*check if the word comes after '$' is expandable part
using env variables.
Allocates memory for the result string based on the lengths of the strings involved.
Copies the portion of str1 before the substring to the result using strncpy.
Concatenates str2 to the result using strcat.
Copies the remaining portion of str1 after the substring to the result using strcat.
Reallocates memory for str1 to match the length of the result string.
Copies the result string to str1 using strcpy.
Frees the memory allocated for the result string.
//I THINK THIS SOLUTION IS STUPIDO///
I DO REALLOCATE FUNCTION AND REALLOCATE THE WHOLE STRING
BUT HOWWWWWWWWWWWWWWWWWWWWWWWWWW// */
char	*expand_var(t_data ms, char *str, int start)
{
	int		end;
	int		size;
	char	*var;
	char	*new;
	char	*out;

	end = start + 1;
	if (!ft_isalnum(str[end]))
		return ;
	while (ft_isalnum(str[end]))
			end++;
	var = ft_substr(str, start, end - start);
	if (!var)
		return (malloc_failure);
	new = find_env(ms, var);
	size = ft_strlen(str) - (end - start);
	size = size + ft_strlen(var);
	out = malloc(sizeof(char) * size);
	out = ft_strncpy(out, str, start);
	free(var);
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
	str[1] = ft_strdup("wc");
	str[2] = ft_strdup("-l");
	str[3] = ft_strdup("|");
	str[4] = ft_strdup(">");
	str[5] = ft_strdup("file2");
	str[6] = ft_strdup("\"$user it's me hi I'm the problem it's me\"");
	str[6] = ft_strdup("hel\"lo'$userit'smehi\" I'm the problem it's me'");
	str[7] = ft_strdup("user'name\"$user\"?hds'af");
	str[8] = NULL;
	(void)argc;
	(void)argv;
	ms.env = envp;

	return (0);
}

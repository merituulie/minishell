/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonseonlee <yoonseonlee@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:53:38 by meskelin          #+#    #+#             */
/*   Updated: 2023/06/28 13:07:19 by yoonseonlee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"
#include <string.h>

// /*finding matching variable and send the value back.
// If no matches, return NULL*/
// char	*find_env(t_data ms, char *var)
// {
// 	int	i;

// 	i = 0;
// 	while (ms.env->key[i])
// 	{
// 		if (ms.env->key[i] == var)
// 			return (ms.env->value[i]);
// 		i++;
// 	}
// 	return (NULL);
// }

// /*check if the word comes after '$' is expandable part
// using env variables.
// Allocates memory for the result string based on the lengths of the strings involved.
// Copies the portion of str1 before the substring to the result using strncpy.
// Concatenates str2 to the result using strcat.
// Copies the remaining portion of str1 after the substring to the result using strcat.
// Reallocates memory for str1 to match the length of the result string.
// Copies the result string to str1 using strcpy.
// Frees the memory allocated for the result string.
// //I THINK THIS SOLUTION IS STUPIDO///
// I DO REALLOCATE FUNCTION AND REALLOCATE THE WHOLE STRING
// BUT HOWWWWWWWWWWWWWWWWWWWWWWWWWW// */
// char	*expand_var(t_data *ms, char *str, int start)
// {
// 	int		end;
// 	int		size;
// 	char	*var;
// 	char	*new;
// 	char	*out;

// 	end = start + 1;
// 	if (!ft_isalnum(str[end]))
// 		return ;
// 	while (ft_isalnum(str[end]))
// 			end++;
// 	var = ft_substr(str, start, end - start);
// 	if (!var)
// 		printf(" malloc fail!\n");
// 	new = find_env(ms, var);
// 	size = ft_strlen(str) - (end - start);
// 	size = size + ft_strlen(var);
// // 	out = malloc(sizeof(char) * size);
// // 	out = ft_strncpy(out, str, start);
// // 	free(var);
// // 	//realloc the string and send it back.
// 	return (NULL);
// }



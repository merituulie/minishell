/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:08:29 by rmakinen          #+#    #+#             */
/*   Updated: 2023/07/06 13:38:49 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"
#include "../../headers/env.h"
#include "../../headers/hashmap.h"

static char *find_value(char *cmd)
{
	int i;
	int j;
	int len;
	char *value;

	i = 0;
	j = 0;
	while (cmd[i] != '=')
		i++;
	len = ft_strlen(cmd);
	value = ft_calloc((len - i), sizeof(char));
	if (!value)
		return (NULL);
	i += 1;
	while (i < len)
	{
		value[j]= cmd[i];
		i++;
		j++;
	}
	value[j] = '\0';
	return(value);
}

char	*ft_pwd(t_env *env, int isPiped)
{
	char *new_value;

	new_value = find_value("pwd");
	if (isPiped == 0)
	{
		printf("%s", new_value);
		return (NULL);
	}
	else
		return (new_value);
}

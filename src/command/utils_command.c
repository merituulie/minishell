/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:31:26 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/02 11:57:10 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

/*returns null if nothing matches. If matches, return something*/
char	*ft_strchr_null(const char *s, int c)
{
	if (c == '\0')
		return (NULL);
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

void	put_to_flags(t_command **cmd, int track, char *str)
{
	if (str == NULL)
		(*cmd)[track].flags = NULL;
	else
	{
		(*cmd)[track].flags = ft_strdup(str);
		if (!(*cmd)[track].flags)
			printf("strdup allocation fail 2!\n");
	}
}

void	put_to_input(t_command **cmd, int track, char *str)
{
	if (str == NULL)
		(*cmd)[track].input = NULL;
	else
	{
		(*cmd)[track].input = ft_strdup(str);
		if (!(*cmd)[track].input)
			printf("strdup allocation fail 3!\n");
	}
}

void	put_fullcmd(t_command *cmd, int i, int track)
{
	cmd[i].full_cmd[0] = ft_strdup(cmd[track].command);
	if (!cmd[i].full_cmd[0])
		printf("strdup fail!\n");
	if (!cmd[track].flags && cmd[track].input)
	{
		cmd[i].full_cmd[1] = ft_strdup(cmd[track].input);
		if (!cmd[i].full_cmd[1])
			printf("strdup fail!\n");
	}
	else if (cmd[track].flags && !cmd[track].input)
	{
		cmd[i].full_cmd[1] = ft_strdup(cmd[track].flags);
		if (!cmd[i].full_cmd[1])
			printf("strdup fail!\n");
	}
	else if (cmd[track].flags && cmd[track].input)
	{
		cmd[i].full_cmd[1] = ft_strdup(cmd[track].flags);
		if (!cmd[i].full_cmd[1])
			printf("strdup fail!\n");
		cmd[i].full_cmd[2] = ft_strdup(cmd[track].input);
		if (!cmd[i].full_cmd[2])
			printf("strdup fail!\n");
	}
}

void	full_cmd(t_command *cmd, int struct_count, int track)
{
	int	i;

	if (struct_count == 1 && cmd->command == NULL)
		return ;
	track = -1;
	i = 0;
	while (++track < struct_count)
	{
		if (track >= struct_count)
			break ;
		if (!cmd[track].flags && !cmd[track].input)
			cmd[i].full_cmd = ft_calloc(2, sizeof (char *));
		else if ((!cmd[track].flags && cmd[track].input) || \
				(cmd[track].flags && !cmd[track].input))
			cmd[i].full_cmd = ft_calloc(3, sizeof (char *));
		else
			cmd[i].full_cmd = ft_calloc(4, sizeof (char *));
		if (!cmd[i].full_cmd)
			printf("calloc fail!\n");
		put_fullcmd(cmd, i, track);
		i++;
	}
}

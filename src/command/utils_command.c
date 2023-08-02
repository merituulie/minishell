/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:31:26 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/02 12:46:09 by yoonslee         ###   ########.fr       */
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

void	put_to_flags(t_command *cmd, int track, char *str)
{
	if (str == NULL)
		cmd[track].flags = NULL;
	else
	{
		cmd[track].flags = ft_strdup(str);
		if (!cmd[track].flags)
			printf("strdup allocation fail!\n");
	}
}

void	put_fullcmd(t_command *cmd, int i, int track)
{
	cmd[i].full_cmd[0] = ft_strdup(cmd[track].command);
	if (!cmd[i].full_cmd[0])
		printf("strdup fail!\n");
	if (!cmd[track].flags && cmd[track].input)
		put_fullcmd_input(cmd, i, track, 1);
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
		put_fullcmd_input(cmd, i, track, 2);
	}
}

void	full_cmd(t_command *cmd, int struct_count, int track)
{
	int	i;

	track = -1;
	i = 0;
	while (++track < struct_count)
	{
		if (ft_strchr("<>", cmd[track].command[0]))
			track++;
		if (track >= struct_count)
			break ;
		if (!cmd[track].flags && !cmd[track].input)
			cmd[i].full_cmd = ft_calloc(2, sizeof (char *));
		else if (cmd[track].flags && !cmd[track].input)
			cmd[i].full_cmd = ft_calloc(3, sizeof (char *));
		else if (!cmd[track].flags && cmd[track].input)
			cmd[i].full_cmd = ft_calloc(ft_arrlen(cmd[track].input) + 2, \
			sizeof (char *));
		else
			cmd[i].full_cmd = ft_calloc(ft_arrlen(cmd[track].input) + 3, \
			sizeof (char *));
		if (!cmd[i].full_cmd)
			printf("calloc fail!\n");
		put_fullcmd(cmd, i, track);
		i++;
	}
}

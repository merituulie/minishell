/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvu <vvu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:04:49 by vvu               #+#    #+#             */
/*   Updated: 2023/07/11 17:52:50 by vvu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strjoin_mini(char const *s1, char const *s2)
{
	size_t	i;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (i + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (*s1)
	{
		join[i] = *s1;
		i++;
		s1++;
	}
	join[i++] = '\0';
	while (*s2)
	{
		join[i] = *s2;
		i++;
		s2++;
	}
	join[i] = '\0';
	return (join);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*parse_flag(char *cmd)
{
	int		i;
	char	*str;
	
	i = 0;
	while (cmd[i])
		i++;
	str = malloc(sizeof(char) * i);
	i = 0;
	while (cmd[i])
	{
		str[i] = cmd[i];
		i++;
	}
	str[i] = "\0";
	return (str);
}

static t_command *init_cmd(char **cmd, int *index)
{
	t_command 	*new_cmd;
	int			cur;
	char		*join_cmd;
	
	cur = 0;
	join_cmd = "\0";
	new_cmd = (t_command *)ft_calloc(1, sizeof(*new_cmd)); 
	while (cmd[*index])
	{
		while (cmd[cur] && ft_strncmp(cmd[cur], "|", 1))
		{
			join_cmd = ft_strjoin_mini(cmd[cur], " ");
			cur++;
		}
		new_cmd->full_cmd = join_cmd;
		// handle full command always before the index++
		new_cmd->command = cmd[*index++];
		if (cmd[*index][0] == '-')
			new_cmd->flags = parse_flags(cmd[*index++]);
		new_cmd->input = cmd[*index];
	}
	return (new_cmd);
}

void	init_cmds(t_command *cmd, char **input)
{
	// get pid, pass it to init_cmd
	// loop through the cmd input string and pass to init_cmd the i whenever there is a new pipe
	// free the input string
	int	index;
	int	pipe_count;
	
	index = 0;
	pipe_count = 0;
	cmd->pid = -2; 
	while (input[index])
	{
		if (!ft_strncmp(input[index], "|", 1))
		{	
			index++;
			pipe_count++;
		}
		else
		{
			cmd = init_cmd(input, &index);
			index++;
			cmd++;
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:31:26 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/19 15:17:19 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

char	*ft_strchr_null(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

int	count_struct(char **input, int struct_count)
{
	int	index;

	index = 0;
	while (input[index])
	{
		if ((ft_strchr("<|>", input[index][0])) || index == 0)
		{
			if (ft_strchr_null("<", input[index][0]) && \
								(index + 2) < ft_arrlen(input))
			{
				if (input[index + 2][0] && !ft_strchr_null("<|>", \
									input[index + 2][0]))
					struct_count++;
			}
			struct_count++;
			index++;
		}
		else
			index++;
	}
	return (struct_count);
}

void	strdup_if_not_null(t_command *cmd, int track, char *name, char *str)
{
	if (!ft_strncmp_all("flags", name))
	{
		if (str == NULL)
			cmd[track].flags = NULL;
		else
		{
			cmd[track].flags = ft_strdup(str);
			if (!cmd[track].flags)
				printf("strdup allocation fail!\n");
		}
		str = NULL;
	}
	else if (!ft_strncmp_all("input", name))
	{
		if (str == NULL)
			cmd[track].input = NULL;
		else
		{
			cmd[track].input = ft_strdup(str);
			if (!cmd[track].input)
				printf("strdup allocation fail!\n");
		}
		str = NULL;
	}
}

void	strdup_filename(t_command *cmd, int track, char *str)
{
	if (cmd[track].command[0] == '<')
	{
		cmd[track].infile_name = ft_strdup(str);
		if (!cmd[track].infile_name)
			printf("strdup allocation fail!\n");
		str = NULL;
	}
	else if (cmd[track].command[0] == '>')
	{
		cmd[track].outfile_name = ft_strdup(str);
		if (!cmd[track].outfile_name)
			printf("strdup allocation fail!\n");
		str = NULL;
	}
}

void	put_full_cmd(t_command *cmd, int struct_count, int track)
{
	int	i;

	track = -1;
	i = 0;
	printf("here\n");
	while (++track < struct_count)
	{
		if (ft_strchr("<>", cmd[track].command[0]))
			track++;
		if (track >= struct_count)
			break ;
		cmd[i].full_cmd = ft_calloc(4, sizeof (char *));
		cmd[i].full_cmd[0] = ft_strdup(cmd[track].command);
		if (!cmd[track].flags && cmd[track].input)
			cmd[i].full_cmd[1] = ft_strdup(cmd[track].input);
		else if (cmd[track].flags && !cmd[track].input)
			cmd[i].full_cmd[1] = ft_strdup(cmd[track].flags);
		else if (cmd[track].flags && cmd[track].input)
		{
			cmd[i].full_cmd[1] = ft_strdup(cmd[track].flags);
			cmd[i].full_cmd[2] = ft_strdup(cmd[track].input);
		}
		i++;
	}
}


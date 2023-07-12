/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvu <vvu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:04:49 by vvu               #+#    #+#             */
/*   Updated: 2023/07/12 18:53:49 by vvu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"

static int	count_struct(char **input, int	struct_count)
{
	int	index;

	index = 0;
	while (input[index])
	{
		if (ft_strchr("|", input[index][0])) 
		{
			struct_count++;
			index++;
		}
		else
			index++;
	}
	return (struct_count);
}

/*static t_command	*full_cmd_strjoin(t_command *cmd, int track)
{
	char	*first_join;


	printf("here 0\n");
	printf("command: %s flags: %s input: %s\n", cmd[track].command, cmd[track].flags, cmd[track].input);
	//first_join = NULL;
	if (cmd[track].flags == NULL) 
		cmd[track].flags = "";
	first_join = ft_strjoin(cmd[track].command, cmd[track].flags);
	printf("first_join: %s\n", first_join);
	cmd[track].full_cmd = ft_strjoin(first_join, cmd[track].input);
	free(first_join);
	printf("full_cmd: %s\n", cmd[track].full_cmd);	
	
	printf("heree\n");
	printf("command: %s flags: %s input: %s\n", cmd[track].command, cmd[track].flags, cmd[track].input);
	//first_join = NULL;
	first_join = ft_strjoin(cmd[track].command, cmd[track].flags);
	printf("first_join: %s\n", first_join);
	cmd[track].full_cmd = ft_strjoin(first_join, cmd[track].input);
	free(first_join);
	printf("full_cmd: %s\n", cmd[track].full_cmd);
	return (cmd);
}*/

static t_command	*put_cmd_to_struct(t_command *cmd, int index, int struct_count, char **input)
{
	int	track;

	track = -1;
	while (track++ < struct_count)
	{
		if (input[index] && ft_strncmp("|", input[index], 1))
		{
			cmd[track].command = input[index++];
			if (input[index][0] == '-')
				cmd[track].flags = input[index++];
			cmd[track].input = input[index++];
		}
		else if (!ft_strncmp("|", input[index++], 1))
		{
			cmd[track].command = input[index++];
			if (input[index][0] == '-')
				cmd[track].flags = input[index++];
			cmd[track].input = input[index++];
		}
		//cmd = full_cmd_strjoin(cmd, track);
	}
	return (cmd);	
}

t_command	*init_cmds(t_command *cmd, char **input)
{
	int	index;
	int	struct_count;
	
	index = 0;
	struct_count = 0;
	struct_count = count_struct(input, struct_count);
	cmd = ft_calloc(struct_count, sizeof(t_command));
	cmd = put_cmd_to_struct(cmd, index, struct_count, input);
	return (cmd);
}
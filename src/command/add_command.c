/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:48:42 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/01 15:52:17 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

static void	print_command(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i].command)
	{
		if (cmd[i].command)
			printf("cmd[%d].command is %s$\n", i, cmd[i].command);
		if (cmd[i].full_cmd[0])
			printf("cmd[%d].full_cmd[0] is %s$\n", i, cmd[i].full_cmd[0]);
		if (cmd[i].full_cmd[1])
			printf("cmd[%d].full_cmd[1] is %s$\n", i, cmd[i].full_cmd[1]);
		if (cmd[i].flags)
			printf("cmd[%d].flags is %s$\n", i, cmd[i].flags);
		if (cmd[i].input)
			printf("cmd[%d].input is %s$\n", i, cmd[i].input);
		if (cmd[i].infile_name)
			printf("cmd[%d].infile is %s$\n", i, cmd[i].infile_name);
		if (cmd[i].outfile_name)
			printf("cmd[%d].outfile is %s$\n", i, cmd[i].outfile_name);
	}
}

char	*parse_input(char **input, int *index)
{
	int		str_len;
	int		cur_index;
	char	*str;
	int		space_count;

	space_count = -1;
	str_len = 0;
	cur_index = *index;
	if (ft_strchr_null("<|>", input[*index][0]))
		return (NULL);
	while ((*index) < ft_arrlen(input) && \
	!ft_strchr_null("<|>", input[*index][0]))
	{
		str_len += ft_strlen(input[*index]);
		(*index)++;
		space_count++;
	}
	str = ft_calloc((str_len + space_count + 1), sizeof(char));
	if (!str)
		printf("memory allocation error\n");
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	while (++cur_index < *index)
	{
		ft_strlcat(str, " ", str_len + space_count + 1);
		ft_strlcat(str, input[cur_index], str_len + space_count + 1);
	}
	return (str);
}

char	*parse_flags(char **input, int	*index)
{
	int	cur_index;

	cur_index = *index;
	if (input[*index][0] == '-')
	{
		(*index)++;
		return (input[cur_index]);
	}
	else
		return (NULL);
}

static char	*parse_redirection_filename(char **input, int index)
{
	int		str_len;
	int		cur_index;
	char	*str;

	str_len = 0;
	cur_index = index;
	if (ft_strchr_null("<|>", input[index][0]))
		return (NULL);
	str_len += ft_strlen(input[index]);
	(index)++;
	str = ft_calloc((str_len + 1), sizeof(char));
	if (!str)
		printf("memory allocation fail\n");
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	return (str);
}

void	handle_redirection(t_command *cmd, int *index, int track, char **input)
{
	char		*str;

	str = NULL;
	cmd[track].token = NONE;
	while (ft_strchr_null("<>", input[(*index)][0]) \
	&& !ft_strchr_null("<", input[(*index)][1]))
	{
		if (ft_strncmp(input[(*index)], "<", 1) && cmd[track].infile_name)
			close_file(g_info.redir_fds[cmd->redir_fd_index]);
		if (ft_strncmp(input[(*index)], ">", 1) && cmd[track].outfile_name)
			close_file(g_info.redir_fds[cmd->redir_fd_index]);
		str = parse_redirection_filename(input, (*index + 1));
		parse_redirection(cmd, track, str, input[(*index)]);
		open_redirection_file(&cmd[track]);
		if (!input[(*index + 2)])
		{
			(*index) += 2;
			break ;
		}
		else
			(*index) += 2;
	}
	free(str);
}


// static int	handle_heredoc(t_command *cmd, int *index, int *track, char **input)
// {
// 	int	org_index;

// 	org_index = 0;
// 	if (!ft_strncmp_all("<<", input[(*index)]))
// 	{
// 		org_index = (*index);
// 		if ((*index) > 0 && input[(*index) - 1][0] \
// 		&& input[(*index) - 1][0] != '|')
// 		{
// 			parse_command(cmd, (*track), index, input);
			// while ((*index) >= 0 && ft_strchr("<|>", input[(*index)][0]))
			// 	(*index)--;
// 			(*track)++;
// 			printf("here in handle heredoc\n");
// 			return (org_index);
// 		}
// 		if (input[(*index) + 1][0] && input[(*index) + 2] \
// 		&& input[(*index) + 2][0] != '|')
// 		{
// 			cmd[(*track)].command = ft_strdup(input[(*index++)]);
// 			cmd[(*track)].input = ft_strdup(input[(*index++)]);
// 			print_command(cmd);
// 			track++;
// 		}
// 	}
// 	return (0);
// }


static int	handle_heredoc(t_command *cmd, int *index, int *track, char **input)
{
	int	is_heredoc;

	is_heredoc = 0;
	printf("not triggered1\n");
	if (!ft_strncmp_all("<<", input[(*index)]))
	{
		if ((*index) > 0 && input[(*index) - 1][0] \
		&& input[(*index) - 1][0] != '|')
		{
			printf("triggered1??\n");
			cmd[(*track)].infile_name = "heredoc.txt";
			(*index) += 2;
			return(1);
		}
		else if (input[(*index) + 1][0] && input[(*index) + 2] \
		&& input[(*index) + 2][0] != '|')
		{
			printf("triggered2??\n");
			cmd[(*track)].infile_name = "heredoc.txt";
			(*index) += 2;
			printf("index after infile_add %i\n", (*index));
			return(1);
		}
		else if (input[(*index) + 1] && input[(*index) + 1][0] != '|')
		{
			printf("we should trigger this input[%i][%s]\n", (*index + 1), input[*index + 1]);
			(*index) += 2;
			return (1);
		}
	}
	printf("not triggered2\n");
	return (0);
}

static void	parse_command(t_command *cmd, int track, int *index, char **input)
{
	char	*str;

	cmd[track].command = ft_strdup(input[(*index)++]);
	printf("index after command %i [%s]\n", (*index), input[(*index)]);
	if (!cmd[track].command)
		printf("strdup allocation fail!");
	if (!input[(*index)])
		return ;
	str = parse_flags(input, &(*index));
	put_to_flags(&cmd, track, str);
	printf("str after flags %s\n", str);
	if (!input[(*index)])
		return ;
	str = parse_input(input, index);
	put_to_input(&cmd, track, str);
	printf("str after input %s\n", str);
	printf("cmd->input after input %s, %s\n", cmd[track].input, cmd->input);
	print_command(cmd);
}

void	put_cmds_to_struct(t_command *cmd, char **input, t_data *ms)
{
	int		index;
	//int		org_index;
	int		track;

	index = 0;
	track = 0;
	while (input[index])
	{
		if (handle_heredoc(cmd, &index, &track, input))
		{
			ft_heredoc(cmd, track, &ms->env, input[index - 1]);
			printf("completed heredoc index is now:%i [%s] \n", index, input[index]);
		}
		// if (org_index)
		// 	index = org_index;
		handle_redirection(cmd, &index, track, input);
		if (!input[index])
			break ;
		if (ft_strchr("|", input[index][0]))
		{
			index++;
			track++;
		}
		parse_command(cmd, track, &index, input);
	}
}

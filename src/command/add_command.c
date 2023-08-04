/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/08/04 06:58:04 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

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

void	clear_failed_redir(t_command *cmd)
{
	int	j;

	if (cmd->command)
		cmd->command = NULL;
	if (cmd->flags)
		cmd->flags = NULL;
	if (cmd->input)
	{
		j = 0;
		while (cmd->input[j])
		{
			cmd->input[j] = NULL;
			j++;
		}
	}
	if (cmd->infile_name)
		cmd->infile_name = NULL;
	if (cmd->outfile_name)
		cmd->outfile_name = NULL;
	if (cmd->redir_fd_index)
		cmd->redir_fd_index = 0;
	if (cmd->token)
		cmd->token = NONE;
}

int	handle_redirection(t_command *cmd, int *index, int track, char **input)
{
	char	*str;

	str = NULL;
	while (ft_strchr_null("<>", input[(*index)][0]) \
	&& ft_strncmp_all("<<", input[(*index)]))
	{
		if (ft_strncmp(input[(*index)], "<", 1) && cmd[track].infile_name)
			close_file(g_info.redir_fds[cmd->redir_fd_index]);
		else if (ft_strncmp(input[(*index)], ">", 1) && cmd[track].outfile_name)
			close_file(g_info.redir_fds[cmd->redir_fd_index]);
		str = parse_redirection_filename(input, (*index + 1));
		parse_redirection(cmd, track, str, input[(*index)]);
		if (open_redirection_file(&cmd[track]) == -1)
		{
			clear_failed_redir(&cmd[track]);
			return (-1);
		}
		if (!input[(*index + 2)])
		{
			(*index) += 2;
			break ;
		}
		else
			(*index) += 2;
	}
	free(str);
	return (0);
}

static void	parse_command(t_command *cmd, int track, int *index, char **input)
{
	char	*str;
	char	**not_echo;

	not_echo = NULL;
	str = NULL;
	cmd[track].command = ft_strdup(input[(*index)++]);
	if (!cmd[track].command)
		printf("strdup allocation fail!");
	if (!input[(*index)] || ft_strchr_null("<|>", input[*index][0]))
		return ;
	str = parse_flags(input, &(*index));
	put_to_flags(&cmd, track, str);
	if (str)
		free(str);
	if (!input[(*index)] || ft_strchr_null("<|>", input[*index][0]))
		return ;
	if (!ft_strncmp_all(cmd[track].command, "echo"))
		str = parse_input(input, index);
	else
		not_echo = copy_input(input, index);
	put_to_input(cmd, track, str, not_echo);
	if (str)
		free(str);
	if (not_echo)
		free_char_array(not_echo);
}

void	put_cmds_to_struct(t_command *cmd, char **input, t_data *ms)
{
	int		index;
	int		track;

	index = 0;
	track = 0;
	while (input[index])
	{
		if (handle_heredoc(cmd, &index, track, input))
			ft_heredoc(&cmd[track], &ms->env, input[index - 1]);
		if (!input[index])
			break ;
		if (handle_redirection(cmd, &index, track, input) == -1)
		{
			while (input[index] && !ft_strchr("|", input[index][0]))
				index++;
		}
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

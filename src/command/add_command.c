/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:08:21 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/06 09:23:24 by yoonslee         ###   ########.fr       */
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
		ft_putstr_fd("Memory allocation failure!\n", 2);
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	return (str);
}

int	handle_redirection(t_command *cmd, int *index, int track, char **input)
{
	char	*str;

	str = NULL;
	while (ft_strchr_null("<>", input[(*index)][0]) \
	&& ft_strncmp_all("<<", input[(*index)]))
	{
		if (!(ft_strncmp(input[(*index)], "<", 1))&& cmd[track].infile_name)
		{
			free(cmd[track].infile_name);
			cmd[track].infile_name = NULL;
			close_file(g_info.redir_fds[cmd->redir_fd_index]);
			g_info.redir_fds[cmd->redir_fd_index] = -1;
		}
		else if (!(ft_strncmp(input[(*index)], ">", 1)) && cmd[track].outfile_name)
		{
			free(cmd[track].outfile_name);
			cmd[track].outfile_name = NULL;
			close_file(g_info.redir_fds[cmd->redir_fd_index]);
			g_info.redir_fds[cmd->redir_fd_index] = -1;
		}
		str = parse_redirection_filename(input, (*index + 1));
		parse_redirection(cmd, track, str, input[(*index)]);
		if (str)
			free(str);
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
		ft_putstr_fd("Strdup memory allocation failure!\n", 2);
	if (!input[(*index)] || ft_strchr_null("<|>", input[*index][0]))
		return ;
	str = ft_strdup(parse_flags(input, &(*index)));
	put_to_flags(&cmd, track, str);
	if (str)
		free(str);
	if (!input[(*index)] || ft_strchr_null("<|>", input[*index][0]))
		return ;
	if (!ft_strncmp_all(cmd[track].command, "echo"))
		str = parse_input(input, index);
	else
		not_echo = copy_input(input, index, not_echo);
	put_to_input(cmd, track, str, not_echo);
}

int	check_null_index_handle_redirs(t_command *cmd, int track, \
char **input, int *index)
{
	if (!input[(*index)])
		return (-1);
	if (handle_redirection(cmd, index, track, input) == -1)
	{
		while (input[(*index)] && !ft_strchr("|", input[(*index)][0]))
			(*index)++;
	}
	if (!input[(*index)])
		return (-1);
	return (0);
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
		{
			ft_heredoc(&cmd[track], &ms->env, input[index - 1]);
			continue ;
		}
		if (check_null_index_handle_redirs(cmd, track, input, &index) == -1)
			break ;
		if (ft_strchr("|", input[index][0]))
		{
			index++;
			track++;
			continue ;
		}
		parse_command(cmd, track, &index, input);
	}
}

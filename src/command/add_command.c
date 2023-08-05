/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:08:21 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/05 10:21:20 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

// static void	print_cmd_line(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		printf("not_echo str is %s\n", str[i]);
// 		i++;
// 	}
// }

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
		if (ft_strncmp(input[(*index)], "<", 1) && cmd[track].infile_name)
		{
			free(cmd[track].infile_name);
			close_file(g_info.redir_fds[cmd->redir_fd_index]);
		}
		else if (ft_strncmp(input[(*index)], ">", 1) && cmd[track].outfile_name)
		{
			free(cmd[track].outfile_name);
			close_file(g_info.redir_fds[cmd->redir_fd_index]);
		}
		str = parse_redirection_filename(input, (*index + 1));
		parse_redirection(cmd, track, str, input[(*index)]);
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
	{
		printf("I'm echo and I come here\n");
		str = parse_input(input, index);
	}
	else
	{
		printf("I'm %s and I come here\n", cmd[track].command);
		not_echo = copy_input(input, index, not_echo);
	}
	put_to_input(cmd, track, str, not_echo);
	if (str)
		free(str);
	printf("here8\n");
	// if (not_echo)
	// {
	// 	printf("echo should not come here\n");
	// 	print_cmd_line(not_echo);
	// 	free_char_array(not_echo);
	// }
	printf("here9\n");
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
			continue ;
		}
		parse_command(cmd, track, &index, input);
	}
}

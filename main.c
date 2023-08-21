/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/08/21 17:15:38 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

t_command	*ft_parser(t_data *ms, char **cmd_line)
{
	t_command	*temp;

	cmd_line = expand_quote_check(ms, cmd_line);
	if (cmd_line == NULL)
		return (NULL);
	cmd_line = concatenate(cmd_line, ms);
	if (cmd_line == NULL)
		return (NULL);
	temp = init_cmds(ms, cmd_line);
	free_char_array(cmd_line);
	if (temp == NULL)
		return (NULL);
	return (temp);
}

static int	process_input_line(t_data *ms, char *input_line)
{
	char		**cmd_line;
	t_command	*cmd;

	cmd_line = ft_lexer(input_line);
	if (input_line)
	{
		free(input_line);
	}
	if (cmd_line == NULL)
		return (1);
	cmd = ft_parser(ms, cmd_line);
	if (cmd == NULL || (ms->struct_count == 1 && cmd->command == NULL))
	{
		free_in_minishell(cmd, ms->struct_count);
		return (1);
	}
	execute_commands(cmd, ms->struct_count, &ms->env);
	free_in_minishell(cmd, ms->struct_count);
	return (0);
}

void	minishell(t_data *ms)
{
	char		*line;

	while (42)
	{
		line = readline(PINK "PinkShell: " BORING);
		ctrl_d_cmd(line, ms);
		if (line && (line[0] == '\0' || line[0] == '\n'))
		{
			free(line);
			continue ;
		}
		else
			add_history(line);
		if (space_newline(line))
		{
			free(line);
			continue ;
		}
		if (process_input_line(ms, line) == 1)
			continue ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	ms;

	(void)argv;
	if (argc == 1)
	{
		ms.env = NULL;
		fill_env(envp, &ms.env);
		add_shlvl(&ms.env);
		set_signal_action(&ms);
		minishell(&ms);
		restore_terminal(&ms);
		free_in_main(&ms);
		return (0);
	}
	ft_putstr_fd("If you tried to run minishell, please try with\
	./minishell and NO arguments\n", 2, 0);
	return (1);
}

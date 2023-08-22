/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:00:36 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 14:40:29 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static t_command	*ft_parser(t_data *ms, char **cmd_line)
{
	t_command	*temp;

	cmd_line = expand_quote_check(ms, cmd_line);
	if (!cmd_line)
		return (NULL);
	cmd_line = concatenate(cmd_line, ms);
	if (!cmd_line)
		return (NULL);
	temp = init_cmds(ms, cmd_line);
	free_char_array(cmd_line);
	if (!temp)
		return (NULL);
	return (temp);
}

static int	process_input_line(t_data *ms, char *input_line)
{
	char		**cmd_line;
	t_command	*cmd;

	if (!input_line)
		return (0);
	cmd_line = ft_lexer(input_line);
	if (input_line)
		free(input_line);
	if (!cmd_line)
		return (1);
	cmd = ft_parser(ms, cmd_line);
	if (!cmd || (ms->struct_count == 1 && !cmd->command))
	{
		free_in_minishell(cmd, ms->struct_count);
		return (1);
	}
	execute_commands(cmd, ms->struct_count, &ms->env);
	free_in_minishell(cmd, ms->struct_count);
	return (0);
}

static char	*readline_setstatus(void)
{
	g_info.sig_status = 0;
	return (readline(""));
}

static void	minishell(t_data *ms)
{
	char		*line;

	while (42)
	{
		if (g_info.sig_status == 2)
			line = readline_setstatus();
		else
			line = readline(PURPLE "minishell: " BORING);
		ctrl_d_cmd(line, ms);
		if (line && (line[0] == '\n' || !line[0]))
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
		process_input_line(ms, line);
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
	./minishell with no arguments\n", 2, 0);
	return (1);
}

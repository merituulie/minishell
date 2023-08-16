/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:36:36 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/16 10:22:11 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "headers/parsing.h"
#include "headers/lexer.h"
#include "headers/minishell.h"
#include "libft/libft.h"
#include <termios.h>

// static void	print_cmd_line(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		printf("cmd_line is %s\n", str[i]);
// 		i++;
// 	}
// }

// //printf("cmd[%d].input is %s$\t%p\n", i, cmd[i].input, &(*cmd[i].input));
// static void	print_full_command(t_command *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (cmd[++i].full_cmd)
// 	{
// 		j = 0;
// 		while (cmd[(i)].full_cmd[j])
// 		{
// 			printf("cmd[%d].full_cmd[%d] is %s\n", i, j, cmd[i].full_cmd[j]);
// 			j++;
// 		}
// 	}
// }

// static void	print_command(t_command *cmd)
// {
// 	int	i;
// 	int	j;
// static void	print_command(t_command *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (cmd[++i].command)
// 	{
// 		if (cmd[i].command)
// 			printf("cmd[%d].command is %s\n", i, cmd[i].command);
// 		if (cmd[i].full_cmd)
// 		{
// 			j = 0;
// 			while (cmd[i].full_cmd[j])
// 			{
// 				printf("cmd[%d].full_cmd[%d] is %s\n", i, j, cmd[i].full_cmd[j]);
// 				j++;
// 			}
// 		}
// 		if (cmd[i].flags)
// 			printf("cmd[%d].flags is %s\n", i, cmd[i].flags);
// 		if (cmd[i].input)
// 		{
// 			j = 0;
// 			while (cmd[i].input[j])
// 			{
// 				printf("cmd[%d].input[%d] is %s\n", i, j, cmd[i].input[j]);
// 				j++;
// 			}
// 		}
// 		if (cmd[i].infile_name)
// 			printf("cmd[%d].infile is %s\n", i, cmd[i].infile_name);
// 		if (cmd[i].outfile_name)
// 			printf("cmd[%d].outfile is %s\n", i, cmd[i].outfile_name);
// 	}
// }
// 	i = -1;
// 	while (cmd[++i].command)
// 	{
// 		if (cmd[i].command)
// 			printf("cmd[%d].command is %s\n", i, cmd[i].command);
// 		if (cmd[i].full_cmd)
// 		{
// 			j = 0;
// 			while (cmd[i].full_cmd[j])
// 			{
// 				printf("cmd[%d].full_cmd[%d] is %s\n", i, j, cmd[i].full_cmd[j]);
// 				j++;
// 			}
// 		}
// 		if (cmd[i].flags)
// 			printf("cmd[%d].flags is %s\n", i, cmd[i].flags);
// 		if (cmd[i].input)
// 		{
// 			j = 0;
// 			while (cmd[i].input[j])
// 			{
// 				printf("cmd[%d].input[%d] is %s\n", i, j, cmd[i].input[j]);
// 				j++;
// 			}
// 		}
// 		if (cmd[i].infile_name)
// 			printf("cmd[%d].infile is %s\n", i, cmd[i].infile_name);
// 		if (cmd[i].outfile_name)
// 			printf("cmd[%d].outfile is %s\n", i, cmd[i].outfile_name);
// 	}
// }

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
		if (line && (space_newline(line) \
					|| line[0] == '\0' || line[0] == '\n'))
		{
			free(line);
			continue ;
		}
		else
			add_history(line);
		if (process_input_line(ms, line) == 1)
			continue ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	ms;

	(void)argc;
	(void)argv;
	ms.env = NULL;
	fill_env(envp, &ms.env);
	add_shlvl(&ms.env);
	set_signal_action(&ms);
	minishell(&ms);
	restore_terminal(&ms);
	free_in_main(&ms);
	return (0);
}

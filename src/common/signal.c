/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:44:29 by                   #+#    #+#             */
/*   Updated: 2023/08/04 11:57:01 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../headers/minishell.h"

static void	handle_sig(int signo)
{
	if (signo == SIGINT)
	{
		g_info.sig_status = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ctrl_d_cmd(char *line, t_data *cmd)
{
	if (line == NULL)
	{
		ft_putstr_fd(PINK "Jose's PinkShell: ", 0);
		write(1, "exit\n", 5);
		restore_terminal(cmd);
		exit(EXIT_SUCCESS);
	}
}

void	restore_terminal(t_data *cmd)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(cmd->old_tio));
}

void	set_signal_action(t_data *cmd)
{
	struct termios	new_tio;

	tcgetattr(STDIN_FILENO, &(cmd->old_tio));
	new_tio = cmd->old_tio;
	new_tio.c_lflag &= (~ICANON & ~ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
	if (signal(SIGINT, handle_sig) == SIG_ERR)
		ft_putstr_fd("\nCannot catch SIGINT\n", 2);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		ft_putstr_fd("\nCannot catch SIGQUIT\n", 2);
}

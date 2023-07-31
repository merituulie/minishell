/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/31 15:40:22 by meskelin         ###   ########.fr       */
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
		ft_putstr_fd(PINK "Jose's PinkShell:", 0);
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
	struct	termios new_tio;

	tcgetattr(STDIN_FILENO, &(cmd->old_tio));
	new_tio = cmd->old_tio;
	new_tio.c_lflag &= (~ICANON & ~ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
	if (signal(SIGINT, handle_sig) == SIG_ERR)
		printf("\nCannot catch SIGINT\n");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		printf("\nCannot catch SIGQUIT\n");
}

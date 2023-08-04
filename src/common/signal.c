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

void	ctrl_d_cmd(char *line, t_data *ms)
{
	if (line == NULL)
	{
		restore_terminal(ms);
		ft_putstr_fd(PINK "Jose's PinkShell: exit\n"BORING, 0);
		exit(EXIT_SUCCESS);
	}
}

void	restore_terminal(t_data *ms)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(ms->old_tio));
}

void	set_signal_action(t_data *ms)
{
	tcgetattr(STDIN_FILENO, &(ms->old_tio));
	ms->new_tio = ms->old_tio;
	ms->new_tio.c_lflag &=  ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &(ms->new_tio));
	ms->sa.sa_handler = &handle_sig;
	sigemptyset(&(ms->sa.sa_mask));
	ms->sa.sa_flags = 0;
	sigaction(SIGINT, &(ms->sa), NULL);
	signal(SIGQUIT, SIG_IGN);
}

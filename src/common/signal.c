/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:25:34 by vvu               #+#    #+#             */
/*   Updated: 2023/07/24 14:25:37 by vvu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../headers/minishell.h"

void	handle_sig(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		rl_clear_signals();
		return ;
	}	
}

void	restore_terminal(t_data *ms)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &(ms->old_tio));
}

void	set_signal_action(t_data *ms)
{
	struct termios new_tio;

	tcgetattr(STDIN_FILENO, &(ms->old_tio));
	new_tio = ms->old_tio;
	new_tio.c_lflag &=(~ICANON & ~ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);

	if (signal(SIGINT, handle_sig) == SIG_ERR)
		printf("\nCannot catch SIGINT\n");
	if (signal(SIGQUIT, handle_sig) == SIG_ERR)
		printf("\nCannot catch SIGQUIT\n");
}

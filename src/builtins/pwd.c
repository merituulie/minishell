/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:56:50 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:56:51 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_pwd(t_env *env)
{
	char	*pwd;

	(void)env;
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1, 0);
	ft_putchar_fd('\n', 1);
	return (0);
}

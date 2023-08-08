/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:24:40 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/08 17:49:07 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	accessable_for_write(char *filename, char *path, int accessable)
{
	if (accessable != 0)
		return (1);
	accessable = access(path, W_OK);
	if (accessable != 0)
	{
		ft_putstr_fd(filename, 2, 1);
		ft_putstr_fd(": Permission denied.\n", 2, 0);
		return (0);
	}
	return (1);
}

static int	accessable_for_read(char *filename, char *path, int accessable)
{
	if (accessable != 0)
	{
		ft_putstr_fd(filename, 2, 1);
		ft_putstr_fd(": No such file or directory.\n", 2, 0);
		return (0);
	}
	accessable = access(path, R_OK);
	if (accessable != 0)
	{
		ft_putstr_fd(filename, 2, 1);
		ft_putstr_fd(": Permission denied.\n", 2, 0);
		return (0);
	}
	return (1);
}

int	accessable_for_open(char *filename, int flags)
{
	char	*path;
	int		accessable;

	path = ft_strjoin("./", filename);
	accessable = access(path, F_OK);
	if (flags == O_RDONLY)
		return accessable_for_read(filename, path, accessable);
	else if (flags >= O_WRONLY)
		return accessable_for_write(filename, path, accessable);
	return (1);
}

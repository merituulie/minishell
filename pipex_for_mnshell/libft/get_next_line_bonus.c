/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonseonlee <yoonseonlee@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:44:32 by yoonslee          #+#    #+#             */
/*   Updated: 2023/02/22 19:53:35 by yoonseonlee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_line_bonus(char *stash, int fd)
{
	int		byte_read;
	char	*buf;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	byte_read = 1;
	while (!ft_strchr(stash, '\n') && byte_read != 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[byte_read] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*get_single_line_bonus(char *stash)
{
	int		i;
	char	*out;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	out = ft_calloc(i + 2, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		out[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		out[i] = '\n';
	i++;
	out[i] = '\0';
	return (out);
}

char	*save_line_bonus(char	*stash)
{
	char	*ud_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	ud_stash = ft_calloc((ft_strlen(stash) - i + 1), sizeof(char));
	if (!ud_stash)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		ud_stash[j++] = stash[i++];
	ud_stash[j] = '\0';
	free(stash);
	return (ud_stash);
}

char	*get_next_line_bonus(int fd)
{
	static char	*stash[4096];
	char		*out;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!stash[fd])
	{
		stash[fd] = ft_calloc(1, 1);
		if (!stash[fd])
			return (NULL);
		stash[fd][0] = '\0';
	}
	stash[fd] = read_line_bonus(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	out = get_single_line_bonus(stash[fd]);
	stash[fd] = save_line_bonus(stash[fd]);
	return (out);
}

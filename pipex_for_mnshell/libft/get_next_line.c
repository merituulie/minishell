/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonseonlee <yoonseonlee@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:46:00 by yoonslee          #+#    #+#             */
/*   Updated: 2023/02/22 19:54:11 by yoonseonlee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_line(char *stash, int fd)
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
			buf = NULL;
			free(stash);
			stash = NULL;
			return (NULL);
		}
		buf[byte_read] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	buf = NULL;
	return (stash);
}

char	*get_single_line(char *stash)
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

char	*save_line(char	*stash)
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
		stash = NULL;
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
	stash = NULL;
	return (ud_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*out;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!stash)
	{
		stash = ft_calloc(1, 1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = read_line(stash, fd);
	if (!stash)
		return (NULL);
	out = get_single_line(stash);
	stash = save_line(stash);
	return (out);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 07:50:19 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/13 07:49:31 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/parsing.h"
#include "../../libft/libft.h"

static char	*find_env_here(char *var, int var_size, t_env **env)
{
	int		i;
	t_node	*node;
	char	*search;

	i = -1;
	if (!ft_strncmp_all(var, "$?"))
		return (get_exit_value());
	var_size--;
	search = ft_calloc(var_size, sizeof(char));
	if (!search)
		ft_putstr_fd("Memory allocation failure!\n", 2);
	while (i++ < var_size)
		search[i] = var[1 + i];
	i = 0;
	node = get_value((*env)->vars, search);
	if (!(node))
		return (NULL);
	free(search);
	return (node->value);
}

static void	realloc_var_here(t_data *ms, char *str, char *var, t_env **env)
{
	int		leftover;
	char	*new;
	int		size;

	size = ft_strlen(str);
	new = find_env_here(var, ft_strlen(var), env);
	if (!new)
		size = ft_strlen(str) - ft_strlen(var);
	else
		size = ft_strlen(str) - ft_strlen(var) + ft_strlen(new);
	ms->out = ft_calloc(size, sizeof(char));
	if (!ms->out)
		ft_putstr_fd("Memory allocation failure!\n", 2);
	ms->out = ft_memcpy(ms->out, str, ms->start);
	leftover = ms->start;
	if (new)
	{
		ms->k = -1;
		while (new[++(ms->k)])
			ms->out[ms->start + ms->k] = new[ms->k];
		leftover = ms->start + ms->k;
	}
	ms->k = -1;
	while ((leftover + (++(ms->k))) < size)
		ms->out[leftover + ms->k] = str[ms->end + ms->k];
	ms->out[leftover + ms->k] = '\0';
	ms->end = leftover;
}

static char	*expand_var_here(t_data *ms, char *str, int start, t_env **env)
{
	char	*var;

	ms->start = start;
	ms->end = start + 1;
	var = NULL;
	if (str[ms->end] == '?')
		var = ft_strdup("$?");
	else if (!ft_isalnum(str[ms->end]))
		return ("");
	while (ft_isalnum(str[ms->end]))
		ms->end++;
	if (var)
		ms->end++;
	else
		var = ft_substr(str, ms->start, ms->end - ms->start);
	if (!var)
		ft_putstr_fd("Memory allocation failure!\n", 2);
	realloc_var_here(ms, str, var, env);
	free(var);
	free(str);
	if (!(ms->out))
		return (NULL);
	return (ms->out);
}

static int	find_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_heredoc(t_command *command, t_env **env, char *delim)
{
	int		fd;
	char	*line;
	t_data	ms;

	g_info.sig_status = 0;
	fd = open_file(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC);
	line = readline("> ");
	while (line)
	{
		if (!ft_strncmp_all(line, delim) || g_info.sig_status)
		{
			free(line);
			break ;
		}
		if (find_index(line, '$') != -1)
			line = expand_var_here(&ms, line, find_index(line, '$'), env);
		if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
			ft_putstr_fd("Heredoc writing error.\n", 2);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	close(fd);
	if (command->infile_name && !ft_strncmp_all(command->infile_name, HEREDOC))
		update_command_redir(command);
	else
		unlink(HEREDOC);
	return (-1);
}

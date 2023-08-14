/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:08:21 by                   #+#    #+#             */
/*   Updated: 2023/08/14 18:56:14 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

char	*add_input_part(int str_len, int space_count,
		char **input, int cur_index)
{
	char	*str;

	str = ft_calloc((str_len + space_count + 1), sizeof(char));
	if (!str)
		ft_putstr_fd("Memory allocation failure!\n", 2, 1);
	ft_strlcpy(str, input[cur_index], ft_strlen(input[cur_index]) + 1);
	return (str);
}

char	*parse_input(char **input, int *index)
{
	int		str_len;
	int		cur_index;
	int		space_count;
	char	*str;

	space_count = -1;
	str_len = 0;
	cur_index = *index;
	if (ft_strchr_null("<|>", input[*index][0]))
		return (NULL);
	while ((*index) < ft_arrlen(input)
		&& !ft_strchr_null("<|>", input[*index][0]))
	{
		str_len += ft_strlen(input[(*index)++]);
		space_count++;
	}
	str = add_input_part(str_len, space_count, input, cur_index);
	while (++cur_index < *index)
	{
		ft_strlcat(str, " ", str_len + space_count + 1);
		ft_strlcat(str, input[cur_index], str_len + space_count + 1);
	}
	return (str);
}

char	**copy_input(char **input, int *index, char **not_echo)
{
	int		cur_index;
	int		i;

	i = 0;
	cur_index = *index;
	if (ft_strchr_null("<|>", input[*index][0]))
		return (NULL);
	while ((*index) < ft_arrlen(input) && \
			!ft_strchr_null("<|>", input[*index][0]) && input[*index])
		(*index)++;
	not_echo = ft_calloc(((*index) - cur_index + 1), sizeof(char *));
	if (!not_echo)
		ft_putstr_fd("Memory allocation failure!\n", 2, 1);
	while (cur_index < (*index))
	{
		not_echo[i] = ft_strdup(input[cur_index]);
		i++;
		cur_index++;
	}
	not_echo[i] = NULL;
	return (not_echo);
}

static void	put_to_input2(t_command *cmd, int track, char **not_echo)
{
	int	i;
	int	len;

	i = 0;
	if (not_echo == NULL)
		cmd[track].input = NULL;
	len = ft_arrlen(not_echo);
	cmd[track].input = ft_calloc(len + 1, sizeof (char *));
	if (!cmd[track].input)
		ft_putstr_fd("Memory allocation failure!\n", 2, 1);
	while (not_echo[i])
	{
		cmd[track].input[i] = ft_strdup(not_echo[i]);
		if (!cmd[track].input[i])
			ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
		i++;
	}
	cmd[track].input[i] = NULL;
	if (not_echo)
		free_char_array(not_echo);
}

void	put_to_input(t_command *cmd, int track, char *str, char **not_echo)
{
	if (!ft_strncmp_all(cmd[track].command, "echo"))
	{
		if (str == NULL)
			cmd[track].input = NULL;
		else
		{
			cmd[track].input = ft_calloc(2, sizeof (char *));
			if (!cmd[track].input)
				ft_putstr_fd("Memory allocation failure!\n", 2, 1);
			cmd[track].input[0] = ft_strdup(str);
			if (!cmd[track].input[0])
				ft_putstr_fd("Strdup memory allocation failure!\n", 2, 1);
			cmd[track].input[1] = NULL;
		}
		if (str)
			free(str);
	}
	else
		put_to_input2(cmd, track, not_echo);
}

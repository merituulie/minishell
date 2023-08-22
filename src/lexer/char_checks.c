/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:55:00 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:55:01 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"

bool	is_delim(char c)
{
	char	*delims;

	delims = " \t\n";
	while (*delims)
	{
		if (c == *delims)
			return (true);
		delims++;
	}
	return (false);
}

bool	is_operand(char c)
{
	char	*operands;

	operands = "<|>";
	while (*operands)
	{
		if (c == *operands)
			return (true);
		operands++;
	}
	return (false);
}

int	quote_index(char *str, int j)
{
	int	temp;

	temp = j;
	while (str[temp++])
	{
		if (str[temp] == str[j])
			return (temp);
	}
	return (j);
}

int	double_redir(char *str, int j)
{
	if (str[j] != '<' && str[j] != '>' && str[j] != '|')
		return (0);
	if (str[j] == '<' || str[j] == '>' || str[j] == '|')
	{
		if (str[j] == str[j + 1])
			return (2);
		else
			return (1);
	}
	return (0);
}

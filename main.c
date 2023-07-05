/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/04 17:25:25 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/minishell.h"
#include "./headers/hashmap.h"
#include "./libft/libft.h"
#include "./headers/lexer.h"

int main(int ac, char **av)
{
	char **parsed;
	int	i = -1;

	if (ac == 2)
	{
		parsed = ft_lexer(av[1]);
	}
	while (parsed[++i])
		printf("parsed is %s\n", parsed[i]);
	if (parsed)
		ft_free_array(parsed);
	return (0);
}
// int	main(void)
// {
// 	char	**cmd_line;

// 	while (1)
// 		cmd_line = ft_lexer(readline(PINK "Jose's PinkShell: " BORING));
// 	ft_free_array(cmd_line);
// 	return (0);
// }

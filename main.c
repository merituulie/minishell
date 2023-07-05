/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/05 09:44:05 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/minishell.h"
#include "./headers/hashmap.h"
#include "./libft/libft.h"
#include "./headers/lexer.h"

// int main(int ac, char **av)
// {
// 	char **cmd_line;
// 	int	i = -1;

// 	if (ac == 2)
// 	{
// 		cmd_line = ft_lexer(av[1]);
// 	}
// 	while (cmd_line[++i])
// 		printf("cmd_line is %s\n", cmd_line[i]);
// 	if (cmd_line)
// 		ft_free_array(cmd_line);
// 	return (0);
// }
int	main(void)
{
	char	 *line;
	char	**cmd_line;
	int i = -1;

	line = readline(PINK "Jose's PinkShell: " BORING);
	cmd_line = ft_lexer(line);
	free(line);
	while (cmd_line[++i])
		printf("cmd_line is %s\n", cmd_line[i]);
	if (cmd_line)
		ft_free_array(cmd_line);
	return (0);
}

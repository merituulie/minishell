/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:57:34 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/07 09:23:52 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/06 09:43:13 by jhusso           ###   ########.fr       */
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
	char	*line;
	char	**cmd_line;
	int		i;

	line = readline(PINK "Jose's PinkShell: " BORING);
	cmd_line = ft_lexer(line);
	free(line);
	i = -1;
	while (cmd_line[++i])
		printf("cmd_line is:\t %s\n", cmd_line[i]);
	if (cmd_line)
		ft_free_array(cmd_line);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:50:18 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/07 11:18:52 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf, perror
#include "headers/parsing.h"
#include "libft/libft.h"

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
int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**cmd_line;
	int		i;
	t_data	ms;

	(void)argc;
	(void)argv;
	line = readline(PINK "Jose's PinkShell: " BORING);
	cmd_line = ft_lexer(line);
	free(line);
	while (cmd_line[++i])
		printf("cmd_line is:\t %s\n", cmd_line[i]);
	ms.env = NULL;
	fill_env(envp, &ms.env);
	ms.end = 0;
	ms.start = 0;
	ms.s_quotes = 0;
	ms.d_quotes = 0;
	cmd_line = expand_quote_check(&ms, cmd_line);
	printf("here\n");
	cmd_line = concatenate(cmd_line, &ms);
	i = -1;
	while (cmd_line[++i])
	{
		printf("cmd [%d] is %s\n", i, cmd_line[i]);
	}
	free_str_array(cmd_line);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_data	ms;
// 	char	**str;
// 	int i = -1;

// 	str = ft_calloc(9, sizeof(char *));
// 	str[0] = ft_strdup("\'$USE'R/hello");
// 	str[1] = ft_strdup("\"\'\"$US\'ER\"\' it's me hi I'm the problem it's me\'");
// 	str[2] = ft_strdup("\'$USER\'");
// 	str[3] = ft_strdup("\"$USER-*r> $USERit's me hi I'm the problem it's me\"");
// 	str[4] = ft_strdup("\"Hel\"\'lo\'\"\"");
// 	(void)argc;
// 	(void)argv;
// 	// while (str[++i])
// 	// {
// 	// 	printf("string [%d] is %s\n", i, str[i]);
// 	// }
// 	return (0);
// }

	// str = malloc(sizeof(char *) * 10);
	// str[0] = ft_strdup("<file1");
	// str[1] = ft_strdup("wc");
	// str[2] = ft_strdup("-l");
	// str[3] = ft_strdup("|");
	// str[4] = ft_strdup("\"$USER-*r> it's me hi I'm the problem it's me\"");
	// str[5] = ft_strdup("'file2'");
	// str[6] = ft_strdup("\"\'\"$US\'ER\"\' it's me hi I'm the problem it's me\"");
	// str[7] = ft_strdup("hel\"lo'$userit'smehi\" I'm the problem it's me'");
	// str[8] = ft_strdup("user'name\"$user\"?hds'af");
	// str[9] = ft_strdup("\0");
		// int i = 0;
		// str[1] = ft_strdup("'$file2'");
	// str[2] = ft_strdup("hel\"lo'$userit'smehi\" I'm the problem it's me'");
	// str[3] = ft_strdup("user'name\"$user\"?hds'af");
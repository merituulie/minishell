/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:50:18 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/03 16:06:56 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf, perror
#include "headers/parsing.h"
#include "../../libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	ms;
	char	**str;

	str = malloc(sizeof(char *) * 2);
	str[0] = ft_strdup("\"\'\"$US\'ER\"\' it's me hi I'm the problem it's me\"");
	str[1] = ft_strdup("\0");
	(void)argc;
	(void)argv;
	ms.env = envp;
	// ms.env = NULL;
	// fill_env(envp, &ms.env);
	// ms.env = env;
	// node = get_value(ms.env->vars, "PWD");
	// printf("node is %p\n", node);
	// printf("value is : %s\n", node->value);
	ms.end = 0;
	ms.start = 0;
	ms.s_quotes = 0;
	ms.d_quotes = 0;
	expand_quote_check(&ms, str);
	return (0);
}

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
	// while (str[i])
	// {
	// 	printf("string [%d] is %s\n", i, str[i]),
	// 	i++;
	// }
		// str[1] = ft_strdup("'$file2'");
	// str[2] = ft_strdup("hel\"lo'$userit'smehi\" I'm the problem it's me'");
	// str[3] = ft_strdup("user'name\"$user\"?hds'af");
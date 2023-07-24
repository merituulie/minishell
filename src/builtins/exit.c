/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 12:53:15 by emmameinert       #+#    #+#             */
/*   Updated: 2023/07/22 13:28:07 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	print_command(t_command *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i].command)
	{
		if (cmd[i].command)
			printf("cmd[%d].command is %s$\n", i, cmd[i].command);
		if (cmd[i].flags)
			printf("cmd[%d].flags is %s$\n", i, cmd[i].flags);
		if (cmd[i].input)
			printf("cmd[%d].input is %s$\n", i, cmd[i].input);
		if (cmd[i].infile_name)
			printf("cmd[%d].infile is %s$\n", i, cmd[i].infile_name);
		if (cmd[i].outfile_name)
			printf("cmd[%d].outfile is %s$\n", i, cmd[i].outfile_name);
	}
}	

static int  ft_is_number(char *input)
{
    int i;
    i = 0;

    printf("input int ft_is_number: %s\n", input);
    while (input[i] != ' ' || input[i] != '\0')
    {
        if (!ft_isdigit(input[i]))
        {
            // printf("input int ft_is_number: %c", input[i]);
            return (0);
        }
        // printf("input[%i]: %c\n",i, input[i]);
        i++;
    }
    return (1);
}

static  int num_arg_check(char *input, int exit_code)
{
    if (ft_is_number(input) ==  1)
    {
        exit_code = ft_atoi_exit(input);
        if (exit_code > 255 || exit_code < 0)
            exit_code = exit_code - 256;
        return (exit_code);
    }    
    else
    {
        printf("exit\n");
        printf("minishell: exit: %s: numeric argument required\n",  input);
        exit_code = 255;
        exit(exit_code);
    }
}
static int  amount_check(char *command)
{
    char **splitted;
    int count;
    printf("input int amount_check: %s", command);
    count = 0;
    splitted = ft_split(command, ' ');
    while (splitted)
        count++;
    if (count > 1)
    {
        printf("minishell: exit: too many arguments\n");
        return (1);
    }
    return (0);
}


void    ft_exit(t_command *command)
{
    int flag;
    int count; 
    int exit_code;
    
    exit_code = 0;
    count = 0;
    // printf("command->id %d\n", command->id);
    // printf("command->input: %s\n", command->input);
    print_command(command);
    exit_code = num_arg_check(command->input, 0);
    flag = amount_check(command->input);
    printf("exit\n");
    if (flag)
        exit(1); 
    else
       exit(exit_code);
}

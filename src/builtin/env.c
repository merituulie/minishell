#include "../../headers/minishell.h"
#include "../../libft/libft.h"

//this is the normal builtin of env, it just prints out the current status of envp
//since we do not need any options thats all!

//str is just envp right now, will replaced later with access to our own envp


int ft_env(char **str) 
{
    int i;
    
    i = 0;
    while (str[i])
    {
        printf("%s\n", str[i]);
        i++;
    }
    return (0); //exits 0 on success, with >0 on error
}


// int	main(int argc, char **argv, char **envp)
// {
// 	if (argc > 2 || !argv[1])
// 		return (0);
// 	if (ft_strncmp(argv[1], "env", 3) == 0)
// 		ft_env(envp);
// 	else
// 		printf("Error, command not found\n");
// 	return (0);
// }
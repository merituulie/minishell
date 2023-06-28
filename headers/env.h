#ifndef ENV_H
    #define ENV_H

#include "hashmap.h"

typedef struct s_env 
{
    struct s_node **vars;
}   t_env;

void    fill_env(char **envp, t_env **env);

#endif  
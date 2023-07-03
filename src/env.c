#include "../headers/minishell.h"
#include "../headers/env.h"

void    print_env(t_node **head)
{
    t_node  *temp;

    temp = *head;
    while (temp)
    {
        printf("%s=%s\n", temp->key, temp->value);
        temp = temp->next;
    }
}
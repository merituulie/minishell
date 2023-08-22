
#ifndef HASHMAP_H
# define HASHMAP_H

# include "minishell.h"

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}	t_node;

t_node	*new_node(char *key, char *value);
t_node	*get_last(t_node **head);
t_node	**set_value(t_node **head, char *key, char *value);
void	clear_hashmap(t_node **head);
t_node	*get_value(t_node **head, char *key);
t_node	*check_value(t_node **head, char *value);
void	delete_value(t_node **head, char *key);
int		hashmap_size(t_node **head);

#endif

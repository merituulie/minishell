
#include "libft.h"

/*free the str & null terminates the entire str and return it*/
char	*ft_free_null_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
	return (str);
}

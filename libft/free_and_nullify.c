
#include "libft.h"

void	free_and_nullify(void *to_be_freed)
{
	free(to_be_freed);
	to_be_freed = NULL;
}

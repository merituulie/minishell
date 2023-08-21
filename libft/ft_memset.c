
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)b;
	while (len-- > 0)
	{
		*p = (unsigned char)c;
		p++;
	}
	p = NULL;
	return (b);
}

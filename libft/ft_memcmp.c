
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*pt1;
	const unsigned char	*pt2;

	pt1 = s1;
	pt2 = s2;
	if (pt1 && ft_strlen((const char *)pt1) == 0)
		return (1);
	while (n--)
	{
		if (*pt1++ != *pt2++)
			return (*(--pt1) - *(--pt2));
	}
	return (0);
}

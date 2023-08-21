
#include "libft.h"

int	ft_strchr_index(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (ft_strlen(s));
	return (0);
}

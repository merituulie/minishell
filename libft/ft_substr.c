
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && len > 0)
	{
		sub[i] = s[start + i];
		i++;
		len--;
	}
	sub[i] = '\0';
	return (sub);
}

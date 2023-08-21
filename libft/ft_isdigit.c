
#include "libft.h"

int	ft_isdigit(char c)
{
	int	answer;

	answer = 0;
	if (c >= '0' && c <= '9')
		answer = 1;
	else
		answer = 0;
	return (answer);
}

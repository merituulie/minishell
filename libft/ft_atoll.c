
#include "libft.h"

long long	ft_atoll(const char *str)
{
	long		i;
	long long	result;
	long long	sign;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (sign == 1 && result > 9223372036854775807)
			return (-1);
		else if (sign == -1 && result > 9223372036854775807)
			return (0);
	}
	return (sign * result);
}

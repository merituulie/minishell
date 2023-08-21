
int	ft_isalpha(int n)
{
	int	answer;

	answer = 0;
	if ((n > 64 && n < 91) || (n > 96 && n < 123))
		answer = 1;
	else
		answer = 0;
	return (answer);
}

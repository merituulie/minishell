
#include <stdio.h> //printf, perror
#include "headers/parsing.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if (count == 0 || size == 0)
	{
		str = malloc (1);
		if (!str)
			return (NULL);
		return (str);
	}
	if (count * size / size != count)
		return (NULL);
	str = (void *)malloc(count * size);
	if (!str)
		return (0);
	while (i < count * size)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	str = malloc (sizeof(char) *(len + 1));
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*out;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	out = malloc (sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}

/*return 0 if two strings are same*/
int	ft_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	while (st1[i] && st2[i] && st1[i] == st2[i])
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	i = 0;
	st1 = (unsigned char *) s1;
	st2 = (unsigned char *) s2;
	while ((i < n) && ((*st1 != '\0') || (*st2 != '\0')))
	{
		if (*st1 == *st2)
		{
			st1++;
			st2++;
			i++;
		}
		else
		{
			return (*st1 - *st2);
		}
	}
	return (0);
}

void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	size_t	i;
	void	*dest;

	i = 0;
	if (!src && !dst)
		return (0);
	dest = dst;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

// /*check if the word comes after '$' is expandable part
// using env variables.
// Allocates memory for the result string based on the lengths of the strings involved.
// Copies the portion of str1 before the substring to the result using strncpy.
// Concatenates str2 to the result using strcat.
// Copies the remaining portion of str1 after the substring to the result using strcat.
// Reallocates memory for str1 to match the length of the result string.
// Copies the result string to str1 using strcpy.
// Frees the memory allocated for the result string.
// //I THINK THIS SOLUTION IS STUPIDO///
// I DO REALLOCATE FUNCTION AND REALLOCATE THE WHOLE STRING
// BUT HOWWWWWWWWWWWWWWWWWWWWWWWWWW// */
char	*expand_var(t_data *ms, char *str, int start)
{
	char	*var;
	char 	*out;

	ms->start = start;
	ms->end = start + 1;
	if (!ft_isalnum(str[ms->end]))
		out = ft_calloc(0, sizeof(char));
	while (ft_isalnum(str[ms->end]))
			ms->end++;
	printf("str[end] is %c\n", str[ms->end]);
	var = ft_substr(str, ms->start, ms->end - ms->start);
	if (!var)
		printf(" malloc fail!\n");
	printf("var is %s\n", var);
	realloc_var(ms, str, var, ft_strlen(str));
	// printf("out is %s\n");
	free(var);
	return (out);
}

 /*finding matching variable and send the value back.
	 If no matches, return NULL*/
char	*find_env(t_data *ms, char *var, int var_size)
{
	int	i;
	char *search;

	i = -1;
	var_size--;
	search = ft_calloc(var_size, sizeof(char));
	while (i++ < var_size)
		search[i] = var[1 + i];
	printf("cutted var is %s\n", search);
	// i = 0;
	// while (ms->env.key[i])
	// {
	// 	if (ms->env.key[i] == search)
	//	{
	//		free(search);
	// 		return(ms.env.value[i]);
	// 	}
	//	i++;
	// }
	//free(search);
	//return(NULL);
	i = 0;
	while (ms->env[i])
	{
		if (!ft_strncmp(ms->env[i], search, ft_strlen(search)))
		{
			printf("expanded to environment variables\n");
			free(search);
			return(ms->env[i]);
		}
		i++;
	}
	printf("no variables. null string\n");
	free(search);
	return(NULL);
}


void	realloc_var(t_data *ms, char *str, char *var, int old_size)
{
	int		leftover;
	int		new_size;
	char	*new;
	int		i;

	printf("realloc var is %s\n", var);
	printf("old_size is %d\n", old_size);
	new = find_env(ms, var, ft_strlen(var));
	printf("new is %s\n", new);
	new_size = ft_strlen(str) - ft_strlen(var) + ft_strlen(new);
	printf("new_size is %d\n", new_size);
	ms->out = ft_calloc(new_size, sizeof(char));
	ms->out = ft_memcpy(ms->out, str, ms->start);
	printf("memcpy after ms->out is %s\n", ms->out);
	printf("ms->start is %d\n", ms->start);
	i = 0;
	while(new[i])
	{
		ms->out[ms->start + i] = new[i];
		i++;
	}
	printf("append env expand ms->out is %s\n", ms->out);
	leftover = ms->start + i;
	i = 0;
	printf("str[ms->end + i] is %c\n", str[ms->end + i]);
	while((leftover + i) < new_size)
	{
		ms->out[leftover + i] = str[ms->end + i];
		i++;
	}
	printf("ms->out is %s\n", ms->out);
// // 	//realloc the string and send it back.
}

/*check the occurence of double quotes '"'
s_quotes is single quote, d_quote is double quote.
s_quotes will be 1 if it happens before d_quotes but if it closes,
it will become 0.
expanding to env only happens if there is $ and something after, and
if there is no single quote in front of it. it does not count if double quote
exists or not.*/
char	**expand_quote_check(t_data *ms, char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			// printf("d_quote = 1, str[%d][%d] is %c\n", i, j, str[i][j]);	
			if (str[i][j] == 34 && !ms->s_quotes)
			{
				printf("d_quote = 1, str[%d][%d] is %c\n", i, j, str[i][j]);	
				ms->d_quotes = 1;
			}
			else if (str[i][j] == 39 && !ms->s_quotes && !ms->d_quotes)
			{
				printf("s_quote = 1, str[%d][%d] is %c\n", i, j, str[i][j]);
				ms->s_quotes = 1;
			}
			else if (str[i][j] == 39 && ms->s_quotes)
			{
				printf("s_quote = 0, matched! str[%d][%d] is %c\n", i, j, str[i][j]);
				ms->s_quotes = 0;
			}
			else if (str[i][j] == '$' && !ms->s_quotes)
			{
				printf("s_quote no exist! str[%d][%d] is %c\n", i, j, str[i][j]);
				expand_var(ms, str[i], j);
				free(str[i]);
				str[i] = ft_strdup(ms->out);
				free(ms->out);
				printf("Final print is %s\n", str[i]);
				break;
			}
			j++;
		}
		i++;
	}
	return(str);
}


int	main(int argc, char **argv, char **envp)
{
	t_data	ms;
	char	**str;

	str = malloc(sizeof(char *) * 10);
	str[0] = ft_strdup("<file1");
	str[1] = ft_strdup("wc");
	str[2] = ft_strdup("-l");
	str[3] = ft_strdup("|");
	str[4] = ft_strdup("\"$USER-*r> it's me hi I'm the problem it's me\"");
	str[5] = ft_strdup("'file2'");
	str[6] = ft_strdup("\"\'\"$US\'ER\"\' it's me hi I'm the problem it's me\"");
	str[7] = ft_strdup("hel\"lo'$userit'smehi\" I'm the problem it's me'");
	str[8] = ft_strdup("user'name\"$user\"?hds'af");
	str[9] = ft_strdup("\0");
	// str = malloc(sizeof(char *) * 2);
	// str[0] = ft_strdup("\"$USER-*r> it's me hi I'm the problem it's me\"");
	// str[1] = ft_strdup("'$file2'");
	// str[2] = ft_strdup("hel\"lo'$userit'smehi\" I'm the problem it's me'");
	// str[3] = ft_strdup("user'name\"$user\"?hds'af");
	// str[1] = ft_strdup("\0");
	printf("print the str[6] : %s\n", str[6]);
	(void)argc;
	(void)argv;
	ms.env = envp;
	ms.end = 0;
	ms.start = 0;
	ms.s_quotes = 0;
	ms.d_quotes = 0;
	expand_quote_check(&ms, str);
	// int i = 0;
	// while (str[i])
	// {
	// 	printf("string [%d] is %s\n", i, str[i]),
	// 	i++;
	// }
	return (0);
}
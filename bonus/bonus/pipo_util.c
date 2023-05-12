#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

int	str_n_compare(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if (*s1 != *s2)
			return (0);
		if (*s1 == 0)
			return (0);
		n--;
		s1++;
		s2++;
	}
	return (1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subbstr;
	size_t	i;

	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s + start);
	subbstr = malloc(len + 1);
	if (!subbstr)
		return (0);
	i = 0;
	while (len - i && start + i < ft_strlen(s))
	{
		*(subbstr + i) = *(s + (start + i));
		i++;
	}
	*(subbstr + i) = '\0';
	return (subbstr);
}

size_t	count_on_me(char const *s, char c)
{
	int	word;
	int	skip;

	skip = 0;
	word = 0;
	while (*s)
	{
		if (*s == c && skip == 1)
			skip = 0;
		if (*s != c && skip == 0)
		{
			word++;
			skip = 1;
		}
		s++;
	}
	return (word);
}

size_t	how_long(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			return (count);
		count++;
		s++;
	}
	return (count);
}
// split

char	**ft_split(char const *s, char c)
{
	char	**resplit;
	size_t	i;
	size_t	big_i;

	if (!s)
		return (0);
	i = 0;
	big_i = 0;
	resplit = (char **)malloc((sizeof(char *)) * (count_on_me(s, c) + 1));
	if (!resplit)
		return (0);
	while (s[i] && i <= ft_strlen(s))
	{
		if (s[i] != c)
		{
			resplit[big_i] = ft_substr(s, i, how_long(&s[i], c));
			i = i + how_long(&s[i], c);
			big_i++;
		}
		if (s[i] == c)
			i++;
	}
	resplit[big_i] = NULL;
	return (resplit);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*j_str;
	char	*str_joined;

	if (!s1 || !s2)
		return (0);
	j_str = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!j_str)
		return (0);
	str_joined = j_str;
	while (*s1)
	{
		*j_str = *s1;
		s1++;
		j_str++;
	}
	while (*s2)
	{
		*j_str = *s2;
		s2++;
		j_str++;
	}
	*j_str = '\0';
	return (str_joined);
}

#include "pars.h"

static int	lenght_str(char const *str, int x, char c)
{
	int	len;

	len = 0;
	while (str[x] != c && str[x] != '\0')
	{
		x++;
		len++;
	}
	return (len);
}

static char	**fill_mtx(int spl, char **mtx, const char *s, char c)
{
	int	i;
	int	x;
	int	len;
	int	j;

	i = 0;
	x = 0;
	while (i < spl && s[x])
	{
		while (s[x] == c && s[x])
			x++;
		len = lenght_str(s, x, c);
		mtx[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!mtx[i])
			free (mtx);
		j = 0;
		while (s[x] != c && s[x])
			mtx[i][j++] = s[x++];
		mtx[i++][j] = '\0';
	}
	mtx[i] = NULL;
	return (mtx);
}

static int	ft_len_sep(const char *str, char c)
{
	int	i;
	int	spl;

	i = 0;
	spl = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			spl++;
			while (str[i] != c && str[i])
				i++;
			i--;
		}
		i++;
	}
	return (spl);
}

char	**ft_split(const char *str, char c)
{
	int		spl;
	char	**mtx;

	if (str)
	{
		spl = ft_len_sep(str, c);
		mtx = (char **)malloc(sizeof(char *) * (spl + 1));
		if (!mtx)
			return (NULL);
		return (fill_mtx (spl, mtx, str, c));
	}
	return (NULL);
}
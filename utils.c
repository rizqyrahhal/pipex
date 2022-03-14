/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 19:45:21 by rarahhal          #+#    #+#             */
/*   Updated: 2022/03/14 19:47:17 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dist, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dist[i] = src[i];
			i++;
		}
		dist[i] = '\0';
	}
	return (ft_strlen(src));
}

char	**ft_malloc_error(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

int	num_of_words(const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

char	*next_str(char const *s, char c)
{
	int		i;
	char	*tab;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	tab = (char *)malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s, i + 1);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		strs_len;
	char	**tab;

	if (!s)
		return (NULL);
	strs_len = num_of_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (strs_len + 1));
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < strs_len)
	{
		while (s[0] == c)
			s++;
		tab[i] = next_str(s, c);
		if (!tab[i])
			return (ft_malloc_error(tab));
		s = s + ft_strlen(tab[i]);
	}
	tab[i] = 0;
	return (tab);
}
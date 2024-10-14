/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:20:01 by htemsama          #+#    #+#             */
/*   Updated: 2023/11/26 14:20:02 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_calculcount(char const *s, char c)
{
	size_t	i;
	size_t	count;
	char	**str;

	i = 0;
	count = 0;
	if (s[0] != c && s[0] != '\0')
		count++;
	while (s[i] != '\0')
	{
		if (s[i] == c && (s[i + 1] != c && s[i + 1] != '\0'))
			count++;
		i++;
	}
	count++;
	str = (char **)malloc(count * sizeof(char *));
	if (!str)
	{
		return (NULL);
	}
	return (str);
}

char	**ft_mini_split(char const *s, char c, char **str, size_t i)
{
	size_t	m;
	size_t	j;

	m = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			j = 0;
			while (s[i + j] != '\0' && s[i + j] != c)
				j++;
			str[m] = ft_substr(s, i, j);
			if (!str[m])
			{
				while (m > 0)
					free(str[--m]);
				free(str);
				return (NULL);
			}
			m++;
			i = i + j - 1;
		}
		i++;
	}
	return (str);
}

static size_t	ft_calculsize(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (i == 0 && s[i] != c && s[i] != '\0')
			count++;
		if (s[i] == c && (s[i + 1] != c && s[i + 1] != '\0'))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	index;

	i = 0;
	if (!s)
		return (NULL);
	str = ft_calculcount(s, c);
	if (!str)
		return (NULL);
	str = ft_mini_split(s, c, str, i);
	if (!str)
		return (NULL);
	index = ft_calculsize(s, c);
	str[index] = NULL;
	return (str);
}

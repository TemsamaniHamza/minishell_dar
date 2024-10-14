/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:13:15 by htemsama          #+#    #+#             */
/*   Updated: 2023/10/30 17:13:18 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_str(char const c, char const *set)
{
	size_t	i;

	i = 0;
	if (c != set[i])
	{
		while (c != set[i] && set[i] != '\0')
			i++;
	}
	if (c == set[i] && set[i] != '\0')
		return (1);
	return (0);
}

static int	get_first_position(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && (ft_int_str(s1[i], set) == 1))
		i++;
	return (i);
}

static int	get_last_position(char const *s, char const *set)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	while (i > 0 && (ft_int_str(s[i], set) == 1))
		i--;
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*ptr;

	len = get_last_position(s1, set) - get_first_position(s1, set);
	ptr = ft_substr(s1, get_first_position(s1, set), len);
	return (ptr);
}

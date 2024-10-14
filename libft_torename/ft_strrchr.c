/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:33:31 by htemsama          #+#    #+#             */
/*   Updated: 2023/11/10 20:33:37 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;
	char	ss;

	i = ft_strlen(s);
	str = (char *)s;
	ss = (char)c;
	if (str[i] == ss)
		return (&str[i]);
	while (i > 0)
	{
		if (str[i] == ss)
			return (&str[i]);
		i--;
	}
	if (str[i] == ss)
		return (&str[i]);
	return (NULL);
}

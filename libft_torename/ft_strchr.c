/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:07:26 by htemsama          #+#    #+#             */
/*   Updated: 2023/11/26 01:07:27 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;
	char	ss;

	ss = (char)c;
	i = 0;
	str = (char *)s;
	while (str[i] != '\0')
	{
		if (str[i] == ss)
			return (&str[i]);
		i++;
	}
	if (str[i] == '\0' && str[i] == ss)
		return (&str[i]);
	return (NULL);
}

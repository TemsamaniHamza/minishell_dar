/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:46:21 by htemsama          #+#    #+#             */
/*   Updated: 2023/10/30 16:20:45 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	slen;

	slen = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	if (start >= slen)
		return (ft_strdup("\0"));
	if (len > (slen - start))
		len = slen - start;
	str = ((char *)malloc((len + 1) * sizeof(char)));
	if (str == NULL)
		return (NULL);
	while (s[start] != '\0' && i < len)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

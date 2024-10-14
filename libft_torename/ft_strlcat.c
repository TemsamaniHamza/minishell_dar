/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 01:07:52 by htemsama          #+#    #+#             */
/*   Updated: 2023/11/26 01:07:54 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	j = ft_strlen(src);
	k = ft_strlen(dst);
	len = k;
	if (size == 0)
		return (j);
	if (size < k)
		return (size + j);
	while (src[i] != '\0' && len < size - 1)
	{
		dst[len] = src[i];
		len++;
		i++;
	}
	dst[len] = '\0';
	return (k + j);
}

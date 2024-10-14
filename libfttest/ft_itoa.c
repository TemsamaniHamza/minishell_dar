/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:52:34 by htemsama          #+#    #+#             */
/*   Updated: 2023/11/06 13:52:44 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_calculen(int n)
{
	int		nb;
	size_t	count;

	nb = n;
	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		nb *= -1;
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

static char	*ft_swap(char *str)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	temp;

	len = ft_strlen(str) - 1;
	i = 0;
	j = ft_strlen(str);
	while (i < len)
	{
		temp = str[i];
		str[i] = str[len];
		str[len] = temp;
		i++;
		len--;
	}
	str[j] = '\0';
	return (str);
}

static char	*ft_itoa_sub(int n, size_t len, size_t check)
{
	size_t	i;
	int		rest;
	char	*str;

	i = 0;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (n > 0 && len > 0)
	{
		rest = n % 10;
		str[i] = rest + '0';
		n = n / 10;
		len--;
		i++;
	}
	if (check > 0)
		str[i++] = '-';
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	size_t	check;

	check = 0;
	len = ft_calculen(n);
	if (n < 0)
	{
		len++;
		n *= -1;
		check++;
	}
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	str = ft_itoa_sub(n, len, check);
	if (str == NULL)
		return (NULL);
	ft_swap(str);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:32:43 by ibenaven          #+#    #+#             */
/*   Updated: 2024/10/27 22:35:06 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nlen(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nbr;
	size_t	len;
	char	*str;

	nbr = n;
	len = ft_nlen(nbr);
	str = ft_calloc (len + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = '0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	len--;
	while (nbr != 0)
	{
		str[len] = nbr % 10 + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 02:55:47 by ibenaven          #+#    #+#             */
/*   Updated: 2024/10/27 22:31:03 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] != '\0') && ((nptr[i] == '\t') || (nptr[i] == '\n')
			|| (nptr[i] == '\v') || (nptr[i] == '\f')
			|| (nptr[i] == '\r') || (nptr[i] == ' ')))
		i++;
	if ((nptr[i] != '\0') && ((nptr[i] == '-') || (nptr[i] == '+')))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:21:49 by ibenaven          #+#    #+#             */
/*   Updated: 2025/03/26 01:35:04 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_hex(unsigned int n, char format)
{
	if (n > 15)
	{
		ft_putnbr_hex(n / 16, format);
		ft_putnbr_hex(n % 16, format);
	}
	else
	{
		if (n < 10)
			ft_print_char(n + '0');
		else
		{
			if (format == 'x')
				ft_print_char(n - 10 + 'a');
			else if (format == 'X')
				ft_print_char(n - 10 + 'A');
		}
	}
}

static int	ft_hex_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

int	ft_print_int(int n)
{
	char	*output;
	int		len;

	output = ft_itoa(n);
	len = ft_print_str(output);
	free(output);
	return (len);
}

int	ft_print_uint(unsigned int n)
{
	char	*output;
	int		len;

	output = ft_uitoa(n);
	len = ft_print_str(output);
	free(output);
	return (len);
}

int	ft_print_hex(unsigned int n, char format)
{
	if (n == 0)
		return (ft_print_char('0'));
	else
		ft_putnbr_hex(n, format);
	return (ft_hex_len(n));
}

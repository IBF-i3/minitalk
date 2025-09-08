/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:51:43 by ibenaven          #+#    #+#             */
/*   Updated: 2025/03/26 01:35:21 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_ptr(unsigned long long p)
{
	if (p > 15)
	{
		ft_putnbr_ptr(p / 16);
		ft_putnbr_ptr(p % 16);
	}
	else
	{
		if (p < 10)
			ft_print_char(p + '0');
		else
			ft_print_char(p - 10 + 'a');
	}
}

static int	ft_ptr_len(unsigned long long p)
{
	int	len;

	len = 0;
	while (p != 0)
	{
		len++;
		p /= 16;
	}
	return (len);
}

int	ft_print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_print_str(char *s)
{
	int	len;

	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		len = 6;
	}
	else if (s[0] == '\0')
	{
		ft_putstr_fd("", 1);
		len = 0;
	}
	else
	{
		ft_putstr_fd(s, 1);
		len = ft_strlen(s);
	}
	return (len);
}

int	ft_print_ptr(void *p)
{
	int	len;

	len = 0;
	if (p == NULL)
		return (ft_print_str("(nil)"));
	len = ft_print_str("0x");
	ft_putnbr_ptr((unsigned long long)p);
	len += ft_ptr_len((unsigned long long)p);
	return (len);
}

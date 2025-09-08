/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:07:58 by ibenaven          #+#    #+#             */
/*   Updated: 2025/03/28 18:15:25 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_format_characters(char format, va_list args)
{
	if (format == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (format == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_print_ptr(va_arg(args, void *)));
	else if (format == 'd' || format == 'i')
		return (ft_print_int(va_arg(args, int)));
	else if (format == 'u')
		return (ft_print_uint(va_arg(args, unsigned int)));
	else if (format == 'x' || format == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), format));
	else if (format == '%')
		return (ft_print_char('%'));
	else
		return (0);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		str_len;

	va_start(args, str);
	str_len = 0;
	while (*str != '\0')
	{
		if (*str == '%' && ft_strchr("cspdiuxX%", *(str + 1)))
		{
			str_len += ft_format_characters(*(str + 1), args);
			str++;
		}
		else
			str_len += ft_print_char(*str);
		str++;
	}
	va_end(args);
	return (str_len);
}

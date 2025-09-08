/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:08:40 by ibenaven          #+#    #+#             */
/*   Updated: 2025/07/19 19:13:53 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

// Function inluded in ft_printf.c
int			ft_printf(char const *str, ...);
// Functions included in ft_print_text.c
int			ft_print_char(char c);
int			ft_print_str(char *s);
int			ft_print_ptr(void *p);
// Functions included in ft_print_nbr.c
int			ft_print_int(int n);
int			ft_print_uint(unsigned int n);
int			ft_print_hex(unsigned int n, char format);

#endif

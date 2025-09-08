/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 03:39:29 by ibenaven          #+#    #+#             */
/*   Updated: 2024/10/27 22:36:41 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	temp = (unsigned char *)src;
	while (n--)
		((unsigned char *)dest)[n] = temp[n];
	return (dest);
}

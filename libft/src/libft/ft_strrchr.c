/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:28:56 by ibenaven          #+#    #+#             */
/*   Updated: 2024/10/27 22:44:48 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len > 0)
	{
		if (s[len] == (unsigned char)c)
			return ((char *)&s[len]);
		len--;
	}
	if (s[len] == (unsigned char)c)
		return ((char *)&s[len]);
	return (NULL);
}

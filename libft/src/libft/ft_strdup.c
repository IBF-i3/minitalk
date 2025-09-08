/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:06:41 by ibenaven          #+#    #+#             */
/*   Updated: 2024/10/27 22:39:53 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;

	len = ft_strlen(s) + 1;
	str = malloc(len * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, len);
	return (str);
}

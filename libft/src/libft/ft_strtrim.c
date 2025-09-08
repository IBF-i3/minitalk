/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:32:43 by ibenaven          #+#    #+#             */
/*   Updated: 2024/10/27 22:51:58 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	s1_len = ft_strlen(s1);
	while (i < s1_len && ft_strrchr(set, s1[s1_len - 1]))
		s1_len--;
	return (ft_substr(s1, i, s1_len - i));
}

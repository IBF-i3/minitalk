/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:06:04 by ibenaven          #+#    #+#             */
/*   Updated: 2025/08/19 14:31:44 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_len(const char *str, char c, int i)
{
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

static size_t	ft_separator(const char *str, char c, int i)
{
	while (str[i] != '\0' && str[i] == c)
		i++;
	return (i);
}

static size_t	ft_word_counter(const char *str, char c)
{
	size_t	word_count;
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	word_count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			word_count++;
			i = ft_word_len(str, c, i);
		}
		i = ft_separator(str, c, i);
	}
	return (word_count);
}

void	*ft_free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	while (i--)
		free(array[i]);
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i_s;
	size_t	i_array;
	size_t	word_count;

	word_count = ft_word_counter(s, c);
	array = ft_calloc(word_count + 1, sizeof(char *));
	if (s == NULL || array == NULL)
		return (NULL);
	i_s = 0;
	i_array = 0;
	while (i_array < word_count)
	{
		i_s = ft_separator(s, c, i_s);
		array[i_array] = ft_substr(s, i_s, ft_word_len(s, c, i_s) - i_s);
		if (array[i_array] == NULL)
			return (ft_free_split(array));
		i_s = ft_word_len(s, c, i_s);
		i_array++;
	}
	return (array);
}

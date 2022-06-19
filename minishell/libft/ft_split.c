/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:43:20 by sghajdao          #+#    #+#             */
/*   Updated: 2021/11/03 12:16:42 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_is_separator(char c, char charset)
{
	int	i;

	i = 0;
	if (c == charset)
		return (1);
	if (c == '\0')
		return (1);
	return (0);
}

static int	count_words(char const *str, char charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i + 1], charset) == 1
			&& char_is_separator(str[i], charset) == 0)
			words++;
		i++;
	}
	return (words);
}

static void	write_word(char *dst, char *from, char charset)
{
	int	i;

	i = 0;
	while (char_is_separator(from[i], charset) == 0)
	{
		dst[i] = from[i];
		i++;
	}
	dst[i] = '\0';
}

static void	write_split(char **split, char const *str, char charset)
{
	int		i;
	int		j;
	int		words;
	char	*str2;

	words = 0;
	i = 0;
	str2 = (char *)str;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (char_is_separator(str[i + j], charset) == 0)
				j++;
			split[words] = (char *)malloc(sizeof(char) * (j + 1));
			write_word(split[words], str2 + i, charset);
			i += j;
			words++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (!res)
	{
		free(res);
		return (NULL);
	}
	res[words] = 0;
	write_split(res, s, c);
	return (res);
}

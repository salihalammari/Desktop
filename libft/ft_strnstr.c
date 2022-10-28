/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:55:01 by sghajdao          #+#    #+#             */
/*   Updated: 2021/11/04 11:04:01 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (find[0] == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] && i < len)
	{
		j = 0;
		if (str[i] == find[j])
		{
			while (i + j < len && str[i + j] == find[j])
			{
				j++;
				if (!find[j])
					return ((char *)&str[i]);
			}
		}
		i++;
	}
	return (0);
}

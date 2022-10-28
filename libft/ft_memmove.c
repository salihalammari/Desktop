/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:46:39 by sghajdao          #+#    #+#             */
/*   Updated: 2021/11/04 10:33:37 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	char		*last_src;
	char		*last_dst;

	d = dst;
	s = src;
	if (dst == src)
		return (dst);
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
	{
		last_src = (char *)s + (len - 1);
		last_dst = d + (len - 1);
		while (len--)
			*last_dst-- = *last_src--;
	}
	return (dst);
}

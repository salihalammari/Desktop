/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:21:56 by sghajdao          #+#    #+#             */
/*   Updated: 2021/11/03 11:11:38 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*ptr;
	char	str;

	ptr = (char *)b;
	str = (char)c;
	while (len-- > 0)
		*(ptr + len) = str;
	return (b);
}

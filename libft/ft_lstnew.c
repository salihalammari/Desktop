/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:29:23 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/18 09:48:30 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*c;

	c = (t_list *)malloc(sizeof(t_list));
	if (!c)
		return (NULL);
	c -> content = ft_strdup(content);
	c -> next = NULL;
	return (c);
}

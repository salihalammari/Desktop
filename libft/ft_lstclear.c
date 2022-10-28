/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 09:32:27 by sghajdao          #+#    #+#             */
/*   Updated: 2021/11/06 09:34:01 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;

	if (!del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		elem = (*lst);
		*lst = elem->next;
		free(elem);
	}
	*lst = NULL;
}

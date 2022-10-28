/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:29:55 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/18 10:07:39 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	envlen(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char	*env_to_string(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	env = malloc(BUFF_SIZE);
	if (!env)
		return (NULL);
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->value[i])
		{
			env[j] = lst->value[i];
			j++;
			i++;
		}
		env[j] = '\n';
		++j;
		lst = lst->next;
	}
	env[j] = '\0';
	return (env);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*p;

	if (!*alst)
		*alst = new;
	else
	{
		p = *alst;
		while (p -> next)
			p = p -> next;
		p -> next = new;
	}
}

t_env	*ft_lstnew_env(void *content)
{
	t_env	*c;

	c = (t_env *)malloc(BUFF_SIZE);
	if (!c)
		return (NULL);
	c -> value = ft_strdup(content);
	if (!c->value)
		return (NULL);
	c -> next = NULL;
	return (c);
}

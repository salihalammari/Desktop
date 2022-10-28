/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:23:42 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/19 12:13:02 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_istype(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

int	has_atype_of(t_token *token, char *types)
{
	if (ft_strchr(types, 'X') && ft_istype(token, CMD))
		return (1);
	else if (ft_strchr(types, 'x') && ft_istype(token, ARG))
		return (1);
	else if (ft_strchr(types, 'T') && ft_istype(token, TRUNC))
		return (1);
	else if (ft_strchr(types, 'A') && ft_istype(token, APPEND))
		return (1);
	else if (ft_strchr(types, 'H') && ft_istype(token, HEREDOC))
		return (1);
	else if (ft_strchr(types, 'I') && ft_istype(token, INPUT))
		return (1);
	else if (ft_strchr(types, 'P') && ft_istype(token, PIPE))
		return (1);
	return (0);
}

int	has_type(t_token *token, int type)
{
	while (token)
	{
		if (ft_istype(token, type))
			return (1);
		token = token->next;
	}
	return (0);
}

int	has_pipe(t_token *token)
{
	while (token)
	{
		if (ft_istype(token, PIPE))
			return (1);
		token = token->next;
	}
	return (0);
}

t_token	*next_type(t_token *token, int type, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != type)
		token = token->next;
	return (token);
}

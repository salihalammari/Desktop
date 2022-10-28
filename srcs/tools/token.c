/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:23:36 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/18 10:07:39 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	rearrengement(t_mini *mini, t_token *token, t_token *previous)
{
	while (is_first_arg(previous) == 0)
		previous = previous->prev;
	token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	token->prev = previous;
	if (previous)
		token->next = previous->next;
	else
	{
		token->next = mini->start;
		previous = token;
	}
	previous->next->prev = token;
	if (mini->start->prev)
		mini->start = mini->start->prev;
	else
		previous->next = token;
}

t_token	*next_separator(t_token *token, int skip)
{
	if (skip && token)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

t_token	*previous_separ(t_token *token, int skip)
{
	if (skip && token)
		token = token->prev;
	while (token && token->type < TRUNC)
		token = token->prev;
	return (token);
}

t_token	*last_token(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD)
			token = token->next;
	}
	return (token);
}

void	take_off_quotes(t_token *token, char *line, int *i)
{
	char	c;
	int		j;

	c = ' ';
	j = 0;
	while ((line[*i] != ' ' || c != ' ') && line[*i])
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
}

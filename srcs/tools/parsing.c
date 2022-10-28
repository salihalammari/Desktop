/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:23:29 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 23:09:29 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isseparator(char *line, int i, t_mini *mini)
{
	if (ft_strchr("<>|", line[i]) && is_quote_open(line, i, mini) == 0)
		return (1);
	else
		return (0);
}

int	is_quote_open(char *line, int index, t_mini *mini)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
	{
		if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
		{
			mini->type_quotes = 1;
			open = 0;
		}
		else if (open == 2 && line[i] == '\'')
		{
			if (line[i - 1] != '\'')
				mini->type_quotes = 2;
			open = 0;
		}
		i++;
	}
	return (open);
}

int	is_first_arg(t_token *token)
{
	t_token	*previous;

	if (!token || ft_istype(token, CMD) || ft_istype(token, ARG))
	{
		previous = previous_separ(token, NOSKIP);
		if (!previous || ft_istype(previous, PIPE))
			return (1);
		return (0);
	}
	else
		return (0);
}

static void	print_error(t_mini *mini, t_token *token, int flag)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", STDERR);
	if (flag)
	{
		if (token->next)
			ft_putstr_fd(token->next->str, STDERR);
		else
			ft_putstr_fd("newline", STDERR);
	}
	else
		ft_putstr_fd(token->str, STDERR);
	ft_putendl_fd("'", STDERR);
	mini->ret = 258;
}

int	check_syntax(t_mini *mini, t_token *token)
{
	while (token)
	{
		if (has_atype_of(token, "THAI")
			&& (!token->next || has_atype_of(token->next, "THAIP")))
		{
			print_error(mini, token, 1);
			return (0);
		}
		if (has_atype_of(token, "PE") && (!token->prev || \
			!token->next || has_atype_of(token->prev, "THAIP")))
		{
			print_error(mini, token, 0);
			return (0);
		}
		token = token->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:22:48 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 23:14:18 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	type_arg_parsing(t_token *token)
{
	if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<<") == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type = INPUT;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

void	arrengement_token(t_mini *mini)
{
	t_token	*token;
	t_token	*previous;

	token = mini->start;
	while (token)
	{
		previous = previous_separ(token, NOSKIP);
		if (ft_istype(token, ARG) && has_atype_of(previous, "TAI"))
			rearrengement(mini, token, previous);
		token = token->next;
	}
}

int	next_length(char *line, int *i)
{
	char	c;
	int		count;
	int		j;

	count = 0;
	j = 0;
	c = ' ';
	while ((line[*i + j] != ' ' || c != ' ') && line[*i + j])
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
	}
	return (j - count + 1);
}

t_token	*get_next_token(char *line, int *i)
{
	t_token	*token;

	token = malloc(BUFF_SIZE);
	if (!token)
		return (NULL);
	token->str = malloc(BUFF_SIZE);
	if (!token->str)
		return (NULL);
	take_off_quotes(token, line, i);
	return (token);
}

t_token	*tokenizer(char *line)
{
	t_token	*previous;
	t_token	*next;
	int		i;

	next = NULL;
	previous = NULL;
	i = 0;
	ft_skip_space(line, &i);
	while (line[i])
	{
		next = get_next_token(line, &i);
		if (!next)
			return (NULL);
		next->prev = previous;
		if (previous)
			previous->next = next;
		previous = next;
		type_arg_parsing(next);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

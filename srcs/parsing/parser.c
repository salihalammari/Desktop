/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:22:36 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/18 21:54:09 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parser(t_mini *mini)
{
	char	*line;
	t_token	*token;
	t_token	*tmp;

	line = lexer(mini);
	if (!line)
		return ;
	mini->start = tokenizer(line);
	ft_heredoc(mini, &mini->start);
	tmp = mini->start;
	ft_memdel(line);
	arrengement_token(mini);
	token = mini->start;
	while (token)
	{
		if (ft_istype(token, ARG))
			type_arg_parsing(token);
		token = token->next;
	}
}

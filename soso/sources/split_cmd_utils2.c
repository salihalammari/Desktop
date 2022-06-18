/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:42:40 by slammari          #+#    #+#             */
/*   Updated: 2022/06/18 15:42:41 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_cmd(char *in)
{
	int	i;

	i = 0;
	while (in[i + 1])
	{
		if ((in[i] == D_QUOTE || in[i] == QUOTE) \
			&& (in[i + 1] == D_QUOTE || in[i + 1] == QUOTE))
			return (1);
		i++;
	}
	return (0);
}

int	check_cmd(t_struct *mini)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (mini->line_read[i + 1])
	{
		if ((mini->line_read[i] == D_QUOTE || mini->line_read[i] == QUOTE) \
				&& mini->line_read[i + 1] == ' ')
			flag = 1;
		i++;
	}
	i = 0;
	while (mini->line_read[i + 1])
	{
		if ((mini->line_read[i] == D_QUOTE || mini->line_read[i] == QUOTE) \
				&& ft_isalnum(mini->line_read[i]) \
				&& mini->line_read[i + 1] == ' ')
			flag = 1;
		i++;
	}
	return (flag);
}

void	count_pipe_assist(t_struct *mini, char *in, int i)
{
	mini->commands[mini->split.n_comand] = ft_substr(in,
			mini->split.ini, mini->split.len);
	mini->split.ini = i;
	mini->split.len = 0;
	mini->split.n_comand++;
	if (in[i] == '>')
		mini->last_redir = 1;
	else
		mini->last_redir = 0;
	if (in[i] == in[i + 1])
	{
		i++;
		mini->split.len = 1;
	}
}

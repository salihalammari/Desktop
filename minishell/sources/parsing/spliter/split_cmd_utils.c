/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:47:34 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/23 18:35:22 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lock_unlock(t_struct *mini, int *i)
{
	while (*i < (int)ft_strlen(mini->line_read))
	{
		if (mini->split.q == 0 && (mini->line_read[*i] == D_QUOTE
				|| mini->line_read[*i] == QUOTE))
			mini->split.q = mini->line_read[*i];
		else
		{
			if (mini->split.q == mini->line_read[*i])
				mini->split.q = 0;
			else
				*i = count_pipe(mini, mini->line_read, *i);
		}
		mini->split.len++;
		(*i)++;
	}
}

int	cmd_quotes(t_struct *mini, int *i)
{
	char	*copy;

	if (ft_strlen(mini->line_read) > 0)
	{
		mini->commands[mini->split.n_comand] = \
					ft_substr(mini->line_read, mini->split.ini, *i);
		if (!check_quote_s1(mini->commands[mini->split.n_comand]))
			return (0);
		if (ft_strncmp(mini->commands[mini->split.n_comand], "export ", 7))
			take_off_quotes(mini->commands[mini->split.n_comand]);
		if (mini->commands[mini->split.n_comand][0] == '$')
		{
			copy = ft_strdup(mini->commands[mini->split.n_comand]);
			free(mini->commands[mini->split.n_comand]);
			mini->commands[mini->split.n_comand] = expander(mini, copy);
			if (find_env(mini, &mini->commands[mini->split.n_comand][1]))
				free(copy);
		}
		mini->split.n_comand++;
	}
	return (1);
}

void	redir_before_cmd_assist(t_struct *mini, char **split, int *n)
{
	char	*copy;
	char	*aux;

	while (ft_strncmp(split[*n], "|", 1) != 0 && split[*n])
	{
		aux = ft_strdup(split[*n]);
		malloc_check_strdup(aux);
		copy = ft_strdup(mini->commands[mini->split.n_comand]);
		malloc_check_strdup(copy);
		free(mini->commands[mini->split.n_comand]);
		mini->commands[mini->split.n_comand] = ft_strjoin(copy, " ");
		free(copy);
		copy = ft_strdup(mini->commands[mini->split.n_comand]);
		malloc_check_strdup(copy);
		free(mini->commands[mini->split.n_comand]);
		mini->commands[mini->split.n_comand] = ft_strjoin(copy, aux);
		free(copy);
		free(aux);
		(*n)++;
		if (!split[*n])
			break ;
	}
}

int	check_redir_before(char **split)
{
	if (!split[1])
		return (0);
	else if (split[1] && (split[0][ft_strlen(split[0]) - 1] == '>' \
		|| split[0][ft_strlen(split[0]) - 1] == '<') && !split[2])
		return (0);
	return (1);
}
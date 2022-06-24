/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:47:51 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/23 16:26:33 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_no_cmd(t_struct *mini, char **split, int j)
{
	if (((!split[1] && split[0][0] == '<' && split[0][1] == '<') \
				|| (split[0][2] == '\0' && split[0][1] == '<' \
					&& split[1] && !split[2]) || (!mini->commands[j + 1] \
						&& !mini->error_name_file)) && j < 1)
	{
		free_char_array(&split);
		return (0);
	}
	return (1);
}

void	fill_extend(char **extend, char *value)
{
	*extend = ft_strdup(value);
	malloc_check_strdup(*extend);
}

static void	join_swap(t_struct *mini, int i)
{
	int		j;
	char	*copy;

	copy = ft_strjoin(mini->tokens[i], " ");
	free(mini->tokens[i]);
	mini->tokens[i] = ft_strjoin(copy, mini->tokens[i + 1]);
	free(copy);
	j = i + 1;
	while (mini->tokens[j + 1])
	{
		copy = ft_strdup(mini->tokens[j]);
		free(mini->tokens[j]);
		mini->tokens[j] = ft_strdup(mini->tokens[j + 1]);
		free(mini->tokens[j + 1]);
		mini->tokens[j + 1] = ft_strdup(copy);
		free(copy);
		j++;
	}
	free(mini->tokens[j]);
	mini->tokens[j] = NULL;
}

void	traiter_export(t_struct *mini)
{
	int		i;

	i = 0;
	while (mini->tokens[i + 1])
	{
		if ((count_char(mini->tokens[i], '\"') == 1 \
			&& count_char(mini->tokens[i + 1], '\"') == 1) \
			|| (count_char(mini->tokens[i], '\'') == 1 \
			&& count_char(mini->tokens[i + 1], '\'') == 1))
			join_swap(mini, i);
		i++;
	}
}

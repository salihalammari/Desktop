/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:03:51 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:03:53 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_struct *mini)
{
	int	i;

	i = 1;
	while (mini->tokens[i])
	{
		if (find_env(mini, mini->tokens[i]))
		{
			rm_env(mini);
			if (!ft_strncmp(mini->tokens[i], "PATH", 4))
			{
				free_char_array(mini->path);
				mini->path = NULL;
			}
		}
		i++;
	}
	g_ret_number = 0;
}

void	rm_env(t_struct *mini)
{
	int	i;
	int	j;

	mini->env.len--;
	alloc_env_aux(mini);
	i = 0;
	j = 0;
	while (mini->env.key[i])
	{
		if (i != mini->env.index)
		{
			mini->env_aux.key[j] = ft_strdup(mini->env.key[i]);
			mini->env_aux.content[j] = ft_strdup(mini->env.content[i]);
			j++;
		}
		i++;
	}
	mini->env_aux.key[j] = NULL;
	mini->env_aux.content[j] = NULL;
	free_char_array(mini->env.key);
	free_char_array(mini->env.content);
	mini->env.key = mini->env_aux.key;
	mini->env.content = mini->env_aux.content;
}

void	alloc_env_aux(t_struct *mini)
{
	mini->env_aux.key = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->env_aux.key)
		exit(EXIT_FAILURE);
	mini->env_aux.content = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->env_aux.content)
		exit(EXIT_FAILURE);
}

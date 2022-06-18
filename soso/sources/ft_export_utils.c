/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:03:07 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/18 15:45:34 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	plus_search(char *key)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (key[i])
	{
		if (key[i] == '+')
			flag = 1;
		i++;
	}
	return (flag);
}

int	ft_strind(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	sort_2d_str(t_struct *mini, int len)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < len)
	{
		j = i;
		while (++j < len)
		{
			if (mini->sorted.key[j] && ft_strncmp(mini->sorted.key[i], \
						mini->sorted.key[j], \
						ft_strlen(mini->sorted.key[i])) > 0)
				sort_assist(mini, i, j);
		}
	}
	mini->sorted.env[i] = NULL;
}

void	copy_export(t_struct *mini, int flag)
{
	int	i;

	sorted_allocation(mini, flag);
	i = 0;
	while (mini->env.key[i])
	{
		mini->sorted.key[i] = ft_strdup(mini->env.key[i]);
		malloc_check_strdup(mini->sorted.key[i]);
		i++;
	}
	mini->sorted.key[i] = NULL;
	i = 0;
	while (mini->env.content[i])
	{
		mini->sorted.content[i] = ft_strdup(mini->env.content[i]);
		malloc_check_strdup(mini->sorted.content[i]);
		i++;
	}
	mini->sorted.content[i] = NULL;
}

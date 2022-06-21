/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:46:10 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:42:20 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_env(t_struct *mini, char *needle)
{
	int	i;
	int	len;
	int	len_needle;

	i = 0;
	mini->env.index = 0;
	len_needle = ft_strlen(needle);
	while (mini->env.key[i] && i < mini->env.len)
	{
		len = ft_strlen(mini->env.key[i]);
		if (!ft_strncmp(mini->env.key[i], needle, len_needle)
			&& len == len_needle)
		{
			mini->env.index = i;
			return (mini->env.content[i]);
		}
		i++;
	}
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:51:33 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/04 18:51:35 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expander(t_struct *mini, char *file)
{
	int		i;
	char	*new_file;

	i = 0;
	if (file[0] == '$')
	{
		while (mini->env.key[i])
		{
			if (ft_strncmp(mini->env.key[i], &file[1], ft_strlen(mini->env.key[i])) == 0 && (file[ft_strlen(mini->env.key[i]) + 1] == '\0' || file[ft_strlen(mini->env.key[i]) + 1] == ' '))
			{
				new_file = ft_strdup(mini->env.content[i]);
				return (new_file);
			}
			i++;
		}
	}
	return (file);
}

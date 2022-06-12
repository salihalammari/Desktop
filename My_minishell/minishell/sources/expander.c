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

void	echo_expander(t_struct *mini)
{
	char	**split;
	char	*copy;
	int		i;

	if ((find_char(mini->line, '$') != (int)ft_strlen(mini->line) - 1) && (mini->line[find_char(mini->line, '$') + 1] != '?'))
	{
		split = ft_split(mini->line, '$');
		i = 1;
		while (split[i])
		{
			copy = ft_strdup(split[i]);
			free(split[i]);
			split[i] = ft_strjoin("$", copy);
			free(copy);
			copy = ft_strdup(split[i]);
			if (split[i][ft_strlen(split[i]) - 1] != ' ')
			{
				free(split[i]);
				split[i] = ft_strjoin(copy, " ");
			}
			free(copy);
			if (!ft_isalnum(split[i][ft_strlen(split[i]) - 2]))
			{
				split[i][ft_strlen(split[i]) - 1] = split[i][ft_strlen(split[i]) - 2];
				split[i][ft_strlen(split[i]) - 2] = ' ';
			}
			i++;
		}
		i = 0;
		free(mini->line);
		copy = ft_strdup(split[0]);
		while (split[i] && split[i + 1])
		{
			mini->line = ft_strjoin(copy, split[i + 1]);
			copy = ft_strdup(mini->line);
			free(mini->line);
			i += 1;
		}
		mini->line = ft_strdup(copy);
		free(copy);
		free_char_array(split);
	}
}

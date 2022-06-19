/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:51:33 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:42:15 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*expander(t_struct *mini, char *file)
{
	int		i;
	char	*new_file;

	i = 0;
	if (file[0] == '$')
	{
		while (mini->env.key[i])
		{
			if (ft_strncmp(mini->env.key[i], &file[1], \
				ft_strlen(mini->env.key[i])) == 0 \
				&& (file[ft_strlen(mini->env.key[i]) + 1] == '\0' \
				|| file[ft_strlen(mini->env.key[i]) + 1] == ' '))
			{
				new_file = ft_strdup(mini->env.content[i]);
				malloc_check_strdup(new_file);
				return (new_file);
			}
			i++;
		}
	}
	return (file);
}

static void	define_value(t_struct *mini, char **split)
{
	char	*copy;
	int		i;

	i = 1;
	while (split[i])
	{
		equal_in_echo(mini, split, &i);
		init_expander(&copy, split, &i);
		if (split[i][ft_strlen(split[i]) - 1] != ' ')
		{
			free(split[i]);
			split[i] = ft_strjoin(copy, " ");
		}
		free(copy);
		if (!ft_isalnum(split[i][ft_strlen(split[i]) - 2]))
		{
			split[i][ft_strlen(split[i]) - 1] \
				= split[i][ft_strlen(split[i]) - 2];
			split[i][ft_strlen(split[i]) - 2] = ' ';
		}
		i++;
	}
}

static void	redefine_mini_line(t_struct *mini, char **split)
{
	char	*copy;
	int		i;

	i = 0;
	copy = ft_strdup(split[0]);
	malloc_check_strdup(copy);
	while (split[i] && split[i + 1])
	{
		mini->line = ft_strjoin(copy, split[i + 1]);
		free(copy);
		copy = ft_strdup(mini->line);
		malloc_check_strdup(copy);
		free(mini->line);
		mini->line = NULL;
		i += 1;
	}
	mini->line = ft_strdup(copy);
	malloc_check_strdup(mini->line);
	free(copy);
}

void	echo_expander(t_struct *mini)
{
	char	**split;
	int		i;

	if ((find_char(mini->line, '$') != (int)ft_strlen(mini->line) - 1) \
		&& (mini->line[find_char(mini->line, '$') + 1] != '?') \
		&& (find_char(mini->line, '$') != (int)ft_strlen(mini->line)))
	{
		split = ft_split(mini->line, '$');
		malloc_check_split(split);
		define_value(mini, split);
		i = 0;
		free(mini->line);
		mini->line = NULL;
		redefine_mini_line(mini, split);
		free_char_array(&split);
	}
}

int	redir_expander(t_struct *mini, char **line)
{
	char	*copy;

	copy = ft_strdup(*line);
	malloc_check_strdup(copy);
	free(*line);
	*line = NULL;
	*line = find_env(mini, &copy[1]);
	if (!*line)
	{
		printf("minishell: %s: ambiguous redirect\n", copy);
		g_ret_number = 1;
		free(copy);
		return (0);
	}
	free(copy);
	return (1);
}

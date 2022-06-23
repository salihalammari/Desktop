/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:46:35 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/20 10:32:41 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sort_assist(t_struct *mini, int i, int j)
{
	char	*tmp_k;
	char	*tmp_c;

	tmp_k = ft_strdup(mini->sorted.key[i]);
	malloc_check_strdup(tmp_k);
	tmp_c = ft_strdup(mini->sorted.content[i]);
	malloc_check_strdup(tmp_c);
	free(mini->sorted.key[i]);
	free(mini->sorted.content[i]);
	mini->sorted.key[i] = ft_strdup(mini->sorted.key[j]);
	malloc_check_strdup(mini->sorted.key[i]);
	mini->sorted.content[i] = ft_strdup(mini->sorted.content[j]);
	malloc_check_strdup(mini->sorted.content[i]);
	free(mini->sorted.key[j]);
	free(mini->sorted.content[j]);
	mini->sorted.key[j] = ft_strdup(tmp_k);
	malloc_check_strdup(mini->sorted.key[j]);
	mini->sorted.content[j] = ft_strdup(tmp_c);
	malloc_check_strdup(mini->sorted.content[j]);
	free(tmp_k);
	free(tmp_c);
}

void	sorted_allocation(t_struct *mini, int flag)
{
	int	i;

	if (flag == 1)
	{
		free_char_array(&mini->sorted.key);
		free_char_array(&mini->sorted.content);
		free_char_array(&mini->sorted.env);
	}
	mini->sorted.env = malloc(sizeof(char *) * (mini->env.len + 1));
	mini->sorted.key = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->sorted.key)
		exit(EXIT_FAILURE);
	mini->sorted.content = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->sorted.content)
		exit(EXIT_FAILURE);
	i = 0;
	while (mini->env.env[i])
	{
		mini->sorted.env[i] = ft_strdup(mini->env.env[i]);
		malloc_check_strdup(mini->sorted.env[i]);
		i++;
	}
	mini->sorted.env[i] = NULL;
}

int	equal_not_found(t_struct *mini, char **env_aux, int i)
{
	int	j;

	if (find_char(mini->tokens[i], '=') != (int)ft_strlen(mini->tokens[i]))
	{
		j = 0;
		while (mini->env.key[j])
		{
			if (ft_strncmp(mini->env.key[j], env_aux[0], \
						ft_strlen(env_aux[0])) == 0)
			{
				free(mini->env.content[j]);
				mini->env.content[j] = ft_strdup("\"\"");
				malloc_check_strdup(mini->env.content[j]);
				free_char_array(&env_aux);
				return (0);
			}
			j++;
		}
	}
	i++;
	return (1);
}

void	just_key_equal(t_struct *mini, char **env_aux, int i)
{
	if (find_char(mini->tokens[i], '=') == (int)ft_strlen(mini->tokens[i]) - 1)
	{
		add_env(mini, env_aux[0], "\"\"");
		free_char_array(&env_aux);
	}
	else
	{
		add_env(mini, env_aux[0], NULL);
		free_char_array(&env_aux);
	}
}

void	check_new_content(t_struct *mini, char *new_content, int i)
{
	if (new_content)
	{
		mini->env_aux.content[i] = ft_strdup(new_content);
		malloc_check_strdup(mini->env_aux.content[i]);
	}
	else
	{
		mini->env_aux.content[i] = ft_strdup("\0");
		malloc_check_strdup(mini->env_aux.content[i]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:45:15 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:41:50 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	env_aux_allocation(t_struct *mini, char ***env_aux, int i)
{
	*env_aux = ft_split(mini->tokens[i], '=');
	malloc_check_split(*env_aux);
}

static int	check_option(char ***env_aux, int *i)
{
	if (*env_aux[0][0] == '-')
	{
		printf("minishell: export: -s: invalid option\n");
		g_ret_number = 2;
		free_char_array(env_aux);
		(*i)++;
		return (0);
	}
	return (1);
}

void	control_export(t_struct *mini, char **env_aux, int i)
{
	while (mini->tokens[i])
	{
		env_aux_allocation(mini, &env_aux, i);
		if (!env_aux[1])
		{
			if (!check_quote_s1(env_aux[0]))
				return ;
			take_off_quotes(env_aux[0]);
			if (!check_option(&env_aux, &i))
				continue ;
			if (find_env(mini, env_aux[0]))
			{
				if (!equal_not_found(mini, env_aux, i))
					break ;
				continue ;
			}
			just_key_equal(mini, env_aux, i);
			i++;
			continue ;
		}
		exec_verify(mini, env_aux, i);
		i++;
	}
}

static int	check_in(t_struct *mini, char *key, char *value)
{
	if (if_plus(key, value, mini))
		return (0);
	if (key[0] == '-')
	{
		printf("minishell: export: -s: invalid option\n");
		g_ret_number = 2;
		return (0);
	}
	return (1);
}

void	exec_export_add(t_struct *mini, char **key, char **value, int i)
{
	if (!check_in(mini, *key, *value))
	{
		free(*key);
		free(*value);
		return ;
	}
	if (find_env(mini, *key))
	{
		free(mini->env.content[mini->env.index]);
		mini->env.content[mini->env.index] = ft_strdup(*value);
		malloc_check_strdup(mini->env.content[mini->env.index]);
	}
	else
		add_env(mini, *key, *value);
	if (!ft_strncmp(mini->tokens[i], "PATH", 4))
	{
		if (mini->path)
			free_char_array(&mini->path);
		init_path(mini);
	}
	free(*key);
	free(*value);
}

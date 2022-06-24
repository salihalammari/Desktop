/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:46:23 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:41:17 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_real_oldpwd(t_struct *mini, int i)
{
	char	**env_aux;

	env_aux = ft_split(mini->env.env[i], '=');
	malloc_check_split(env_aux);
	mini->env.key[i] = ft_strdup(env_aux[0]);
	malloc_check_strdup(mini->env.key[i]);
	if (env_aux[1] && ft_strncmp(env_aux[0], "OLDPWD", 6))
	{
		mini->env.content[i] = ft_strdup(env_aux[1]);
		malloc_check_strdup(mini->env.content[i]);
	}
	else if (env_aux[1] && ft_strncmp(env_aux[0], "OLDPWD", 6) == 0)
	{
		mini->env.content[i] = ft_strdup(find_env(mini, "PWD"));
		malloc_check_strdup(mini->env.content[i]);
	}
	else
	{
		mini->env.content[i] = ft_strdup("");
		malloc_check_strdup(mini->env.content[i]);
	}
	free_char_array(&env_aux);
	env_aux = NULL;
	i++;
}

void	take_off_oldpwd(t_struct *mini, int i)
{
	char	*copy;

	copy = ft_strdup(mini->env.key[i]);
	malloc_check_strdup(copy);
	free(mini->env.key[i]);
	mini->env.key[i] = ft_strdup(mini->env.key[i + 1]);
	malloc_check_strdup(mini->env.key[i]);
	free(mini->env.key[i + 1]);
	mini->env.key[i + 1] = ft_strdup(copy);
	malloc_check_strdup(mini->env.key[i + 1]);
	free(copy);
	copy = ft_strdup(mini->env.content[i]);
	malloc_check_strdup(copy);
	free(mini->env.content[i]);
	mini->env.content[i] = ft_strdup(mini->env.content[i + 1]);
	malloc_check_strdup(mini->env.content[i]);
	free(mini->env.content[i + 1]);
	mini->env.content[i + 1] = ft_strdup(copy);
	malloc_check_strdup(mini->env.content[i + 1]);
	free(copy);
}

void	just_oldpwd_things(t_struct *mini, int i)
{
	while (mini->env.key[i + 1])
	{
		take_off_oldpwd(mini, i);
		i++;
	}
	free(mini->env.key[i]);
	free(mini->env.content[i]);
	free(mini->env.content[i - 1]);
	mini->env.content[i - 1] = ft_strdup("/usr/bin/env");
	malloc_check_strdup(mini->env.content[i - 1]);
	mini->env.key[i] = NULL;
	mini->env.content[i] = NULL;
}

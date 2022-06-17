/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:01:51 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:01:53 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(t_struct *mini)
{
	int	i;

	i = 0;
	while (mini->env.key[i])
	{
		if (ft_strncmp(mini->env.key[i], "PWD", 3) == 0)
		{
			free(mini->env.content[i]);
			mini->env.content[i] = malloc(sizeof(char) * 2000);
			getcwd(mini->env.content[i], 2000);
			return ;
		}
		i++;
	}
}

void	change_oldpwd(t_struct *mini)
{
	int	i;

	i = 0;
	while (mini->env.key[i])
	{
		if (ft_strncmp(mini->env.key[i], "OLDPWD", 6) == 0)
		{
			free(mini->env.content[i]);
			mini->env.content[i] = malloc(sizeof(char) * 2000);
			getcwd(mini->env.content[i], 2000);
			return ;
		}
		i++;
	}
	if (find_env(mini, "PWD"))
		add_env(mini, "OLDPWD", find_env(mini, "PWD"));
	else
		add_env(mini, "OLDPWD", "\"\"");
}

int	ft_cd(t_struct *mini)
{
	bool	home;

	home = there_is_home(mini);
	if (mini->tokens[1])
	{
		if (!cd_home__(mini, home))
			return (0);
		else if (!cd_to_oldpwd(mini))
			return (0);
	}
	if (get_cd_path(mini, home))
		return (1);
	if (g_ret_number == -1)
	{
		g_ret_number = 1;
		printf("minishell: cd: %s: %s", mini->tokens[1], ERROR_DIR);
	}
	change_pwd(mini);
	return (0);
}

bool	there_is_home(t_struct *mini)
{
	if (find_env(mini, "HOME"))
		return (true);
	else
		return (false);
}

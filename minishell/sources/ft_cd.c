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

static void	change_pwd(t_struct *mini)
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

static void	change_oldpwd(t_struct *mini)
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
	add_env(mini, "OLDPWD", find_env(mini, "PWD"));
}

int	ft_cd(t_struct *mini)
{
	char	*token_aux;
	char	*path;
	int		i;
	bool	home;

	home = there_is_home(mini);
	if (mini->tokens[1])
	{
		if (ft_strncmp(mini->tokens[1], "--", 2) == 0 && mini->tokens[1][2] == '\0')
		{
			if (home == false)
			{
				printf(ERROR_HOME);
				return (1);
			}
			path = ft_strdup(mini->home);
			token_aux = ft_strdup(path);
			free(path);
			change_oldpwd(mini);
			g_ret_number = chdir(token_aux);
			change_pwd(mini);
			free(token_aux);
			return (0);
		}
		else if (ft_strncmp(mini->tokens[1], "-", 1) == 0 && mini->tokens[1][1] == '\0')
		{
			if (!find_env(mini, "OLDPWD"))
			{
				printf("minishell: cd: OLDPWD not set\n");
				return (1);
			}
			i = 0;
			path = ft_strdup(find_env(mini, "OLDPWD"));
			token_aux = ft_strdup(path);
			free(path);
			i = 0;
			while (mini->env.key[i])
			{

				if (ft_strncmp(mini->env.key[i], "OLDPWD", 6) == 0)
					break ;
				i++;
			}
			change_oldpwd(mini);
			g_ret_number = chdir(token_aux);
			change_pwd(mini);
			printf("%s\n", mini->env.content[i]);
			free(token_aux);
			return (0);
		}
	}
	if (mini->tokens[1])
		token_aux = ft_strdup(mini->token.to_print);
	else
	{
		if (home == true)
			token_aux = ft_strdup(mini->home);
		else
		{
			g_ret_number = 1;
			printf(ERROR_HOME);
			return (1);
		}
	}
	change_oldpwd(mini);
	g_ret_number = chdir(token_aux);
	if (g_ret_number == -1)
		printf("minishell: cd: %s: %s", mini->tokens[1], ERROR_DIR);
	change_pwd(mini);
	free(token_aux);
	return (0);
}

bool	there_is_home(t_struct *mini)
{
	if (find_env(mini, "HOME"))
		return (true);
	else
		return (false);
}

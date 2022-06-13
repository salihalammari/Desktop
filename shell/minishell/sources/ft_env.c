/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:02:21 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:02:23 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_struct *mini)
{
	int	i;

	i = 0;
	if (mini->tokens[1])
	{
		printf("env: %s: No such file or directory\n", mini->tokens[1]);
		g_ret_number = 127;
		return ;
	}
	while (mini->env.key[i])
	{
		if (mini->env.content[i][1] != '\"' && mini->env.content[i][0] != '\0')
		{
			ft_putstr_fd(mini->env.key[i], mini->out_fd);
			ft_putchar_fd('=', mini->out_fd);
			ft_putendl_fd(mini->env.content[i], mini->out_fd);
		}
		else if (mini->env.content[i][1] == '\"')
		{
			ft_putstr_fd(mini->env.key[i], mini->out_fd);
			ft_putendl_fd("=", mini->out_fd);
		}
		i++;
	}
	g_ret_number = 0;
}

void	create_env(t_struct *mini, char **my_env)
{
	int		i;
	char	**env_aux;
	char	*copy;

	if (mini->env_flag == 0)
		mini->env.env = my_env;
	len_env(mini);
	init_struct_env(mini);
	i = 0;
	while (mini->env.env[i])
	{
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
		free_char_array(env_aux);
		env_aux = NULL;
		i++;
	}
	mini->env.key[i] = NULL;
	mini->env.content[i] = NULL;
	i = 0;
	while (mini->env.key[i])
	{
		if (ft_strncmp(mini->env.key[i], "OLDPWD", 6) == 0)
		{
			while (mini->env.key[i + 1])
			{
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
				i++;
			}
			free(mini->env.key[i]);
			free(mini->env.content[i]);
			free(mini->env.content[i - 1]);
			mini->env.content[i - 1] = ft_strdup("/usr/bin/env");
			malloc_check_strdup(mini->env.content[i - 1]);
			mini->env.key[i] = NULL;
			mini->env.content[i] = NULL;
			break ;
		}
		i++;
	}
	copy_export(mini, 0);
}

void	len_env(t_struct *mini)
{
	int	i;

	i = 0;
	while (mini->env.env[i])
		i++;
	mini->env.len = i;
}

void	init_struct_env(t_struct *mini)
{
	mini->env.key = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->env.key)
		exit(EXIT_FAILURE);
	mini->env.content = malloc(sizeof(char *) * (mini->env.len + 1));
	if (!mini->env.content)
		exit(EXIT_FAILURE);
}

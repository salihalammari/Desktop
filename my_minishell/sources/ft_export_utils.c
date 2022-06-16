/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:03:07 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:03:09 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	plus_search(char *key)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (key[i])
	{
		if (key[i] == '+')
			flag = 1;
		i++;
	}
	return (flag);
}

int	ft_strind(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void    sort_2D_str(t_struct *mini, int len)
{
    int        i;
    int        j;

    i = -1;
    j = 0;
    while(++i < len)
    {
        j = i;
        while (++j < len)
        {
            if (mini->sorted.key[j] && ft_strncmp(mini->sorted.key[i], mini->sorted.key[j], ft_strlen(mini->sorted.key[i])) > 0)
				sort_assist(mini, i, j);
        }
    }
    mini->sorted.env[i] = NULL;
}

void	copy_export(t_struct *mini, int flag)
{
	int		i;

	sorted_allocation(mini, flag);
	i = 0;
	while (mini->env.key[i])
	{
		mini->sorted.key[i] = ft_strdup(mini->env.key[i]);
		malloc_check_strdup(mini->sorted.key[i]);
		i++;
	}
	mini->sorted.key[i] = NULL;
	i = 0;
	while (mini->env.content[i])
	{
		mini->sorted.content[i] = ft_strdup(mini->env.content[i]);
		malloc_check_strdup(mini->sorted.content[i]);
		i++;
	}
	mini->sorted.content[i] = NULL;
}

void    print_export(t_struct *mini)
{
    int i;

    if (!mini->tokens[1])
	{
		copy_export(mini, 1);
		sort_2D_str(mini, mini->env.len);
		i = 0;
    	while (mini->sorted.key[i])
    	{
			if (!(mini->sorted.content[i][0] == '\"' && mini->sorted.content[i][1] == '\"') && mini->sorted.content[i][0] != '\0')
				printf("declare -x %s=\"%s\"\n", mini->sorted.key[i], mini->sorted.content[i]);
			else if (mini->sorted.content[i][0] == '\0')
				printf("declare -x %s\n", mini->sorted.key[i]);
			else
				printf("declare -x %s=%s\n", mini->sorted.key[i], mini->sorted.content[i]);
    	    i++;
    	}
	}
}

void	exec_verify(t_struct *mini, char **env_aux, int i)
{
	if (env_aux[1])
		verify_if_env_exists(mini, env_aux, i);
	else if (mini->tokens[i][ft_strlen(mini->tokens[1]) - 1] == '=')
	{
		free(env_aux[1]);
		env_aux[1] = ft_strdup("");
		malloc_check_strdup(env_aux[1]);
		verify_if_env_exists(mini, env_aux, i);
	}
	free_char_array(&env_aux);
}

void	exec_export_add(t_struct *mini, char *key, char *value, int i)
{
	if (if_plus(key, value, mini))
	{
		free(key);
		free(value);
		return ;
	}
	if (key[0] == '-')
	{
		printf("minishell: export: -s: invalid option\n");
		return ;
	}
	if (find_env(mini, key))
	{
		free(mini->env.content[mini->env.index]);
		mini->env.content[mini->env.index] = ft_strdup(value);
		malloc_check_strdup(mini->env.content[mini->env.index]);
	}
	else
		add_env(mini, key, value);
	if (!ft_strncmp(mini->tokens[i], "PATH", 4))
	{
		if (mini->path)
			free_char_array(&mini->path);
		init_path(mini);
	}
	free(key);
	free(value);
}

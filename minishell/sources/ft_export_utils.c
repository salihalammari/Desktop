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

void    print_export(t_struct *mini)
{
    int i;

    if (!mini->tokens[1])
	{
		i = 0;
    	while (i < mini->env.len)
    	{
			if (!(mini->env.content[i][0] == '\"' && mini->env.content[i][1] == '\"') && mini->env.content[i][0] != '\0')
    	    	printf("declare -x %s=\"%s\"\n", mini->env.key[i], mini->env.content[i]);
			else if (mini->env.content[i][0] == '\0')
				printf("declare -x %s\n", mini->env.key[i]);
			else
				printf("declare -x %s=%s\n", mini->env.key[i], mini->env.content[i]);
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
		env_aux[1] = ft_strdup("");
		verify_if_env_exists(mini, env_aux, i);
	}
	free(env_aux[0]);
	free(env_aux[1]);
	free(env_aux);
	env_aux = NULL;
}

void	exec_export_add(t_struct *mini, char *key, char *value, int i)
{
	if (if_plus(key, value, mini))
	{
		free(key);
		free(value);
		return ;
	}
	if (find_env(mini, key))
	{
		free(mini->env.content[mini->env.index]);
		mini->env.content[mini->env.index] = ft_strdup(value);
	}
	else
		add_env(mini, key, value);
	if (!ft_strncmp(mini->tokens[i], "PATH", 4))
	{
		if (mini->path)
			free_char_array(mini->path);
		init_path(mini);
	}
	free(key);
	free(value);
}

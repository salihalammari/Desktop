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
    char    *tmp;

    i = -1;
    j = 0;
    while(++i < len)
    {
        j = i;
        while (++j < len)
        {
            if (mini->sorted.env[j] && ft_strncmp(mini->sorted.env[i], mini->sorted.env[j], ft_strlen(mini->sorted.env[i])) > 0)
            {
                tmp = ft_strdup(mini->sorted.env[i]);
                free(mini->sorted.env[i]);
                mini->sorted.env[i] =ft_strdup(mini->sorted.env[j]);
                free(mini->sorted.env[j]);
                mini->sorted.env[j] = ft_strdup(tmp);
                free(tmp);
            }
        }
    }
    mini->sorted.env[i] = NULL;
}

void    print_export(t_struct *mini)
{
    int i;
	char	**env_aux;

	i = 0;
	mini->sorted.env = malloc(sizeof(char *) * (mini->env.len + 1));
	while (mini->env.env[i])
	{
		mini->sorted.env[i] = ft_strdup(mini->env.env[i]);
		i++;
	}
	i = 0;
	while (mini->sorted.env[i])
		i++;
	mini->sorted.len = i;
	mini->sorted.key = malloc(sizeof(char *) * (mini->sorted.len + 1));
	if (!mini->sorted.key)
		exit(EXIT_FAILURE);
	mini->sorted.content = malloc(sizeof(char *) * (mini->sorted.len + 1));
	if (!mini->sorted.content)
		exit(EXIT_FAILURE);
	sort_2D_str(mini, mini->sorted.len);
	i = 0;
	while (mini->sorted.env[i])
	{
		env_aux = ft_split(mini->sorted.env[i], '=');
		if (!env_aux)
		{
			printf("malloc error\n");
			exit(1);
		}
		mini->sorted.key[i] = ft_strdup(env_aux[0]);
		if (env_aux[1] && ft_strncmp(env_aux[0], "OLDPWD", 6))
			mini->sorted.content[i] = ft_strdup(env_aux[1]);
		else if (env_aux[1] && ft_strncmp(env_aux[0], "OLDPWD", 6) == 0)
			mini->sorted.content[i] = ft_strdup(find_env(mini, "PWD"));
		else
			mini->sorted.content[i] = ft_strdup("");
		free_char_array(env_aux);
		env_aux = NULL;
		i++;
	}
	mini->sorted.key[i] = NULL;
	mini->sorted.content[i] = NULL;
    if (!mini->tokens[1])
	{
		i = 0;
    	while (i < mini->sorted.len)
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

/* void    print_export(t_struct *mini)
{
    int i;

    if (!mini->tokens[1])
	{
		sort_2D_str(mini, mini->env.len);
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
} */

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

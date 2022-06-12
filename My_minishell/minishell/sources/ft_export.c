/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:03:22 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:03:23 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	take_off_plus(char *str)
{
	int	i;

	if (str[ft_strlen(str) - 1] == '+')
	{
		i = 0;
		while (str[i + 1])
			i++;
		str[i] = '\0';
	}
}

int	if_plus(char *key, char *value, t_struct *mini)
{
	int		i;
	int		flag;
	char	*aux;

	flag = plus_search(key);
	if (flag == 1)
	{
		i = 0;
		take_off_plus(key);
		while (mini->env.key[i])
		{
			if (ft_strncmp(mini->env.key[i], key, ft_strlen(mini->env.key[i])) == 0)
			{
				aux = ft_strdup(mini->env.content[i]);
				free(mini->env.content[i]);
				take_off_quotes(aux);
				mini->env.content[i] = ft_strjoin(aux, value);
				free(aux);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

void	ft_export(t_struct *mini)
{
	int		i;
	int		j;
	char	**env_aux;

	print_export(mini);
	i = 1;
	while (mini->tokens[i])
	{
		env_aux = ft_split(mini->tokens[i], '=');
		if (!env_aux)
		{
			printf("malloc error\n");
			exit(1);
		}
		if (!env_aux[1])
		{
			if (!check_quote_s1(env_aux[0]))
        		return ;
			take_off_quotes(env_aux[0]);
			if (env_aux[0][0] == '-')
			{
				printf("minishell: export: -s: invalid option\n");
				i++;
				continue ;
			}
			if (find_env(mini, env_aux[0]))
			{
				if (find_char(mini->tokens[i], '=') != (int)ft_strlen(mini->tokens[i]))
				{
					j = 0;
					while (mini->env.key[j])
					{
						if (ft_strncmp(mini->env.key[j], env_aux[0], ft_strlen(env_aux[0])) == 0)
						{
							free(mini->env.content[j]);
							mini->env.content[j] = ft_strdup("\"\"");
							break ;
						}
						j++;
					}
				}
				i++;
				continue ;
			}
			else if (find_char(mini->tokens[i], '=') == (int)ft_strlen(mini->tokens[i]) - 1)
				add_env(mini, env_aux[0], "\"\"");
			else
				add_env(mini, env_aux[0], NULL);
			i++;
			continue ;
		}
		exec_verify(mini, env_aux, i);
		i++;
	}
	g_ret_number = 0;
}

void	verify_if_env_exists(t_struct *mini, char **env_aux, int i)
{
    char    *key;
    char    *value;

    key = ft_strdup(env_aux[0]);
    value = ft_strdup(env_aux[1]);
    if (!check_quotes(key, value))
        return ;
	if ((find_char(key, '\'') != (int)ft_strlen(key)) || (find_char(key, '\"') != (int)ft_strlen(key)))
	{
		printf("minishell: quotes error\n");
		return ;
	}
    take_off_quotes(key);
    take_off_quotes(value);
	exec_export_add(mini, key, value, i);
}

void	add_env(t_struct *mini, char *new_key, char *new_content)
{
	int	i;

	mini->env.len++;
	alloc_env_aux(mini);
	i = 0;
	while (mini->env.key[i])
	{
		mini->env_aux.key[i] = ft_strdup(mini->env.key[i]);
		mini->env_aux.content[i] = ft_strdup(mini->env.content[i]);
		i++;
	}
	mini->env_aux.key[i] = ft_strdup(new_key);
	if (new_content)
		mini->env_aux.content[i] = ft_strdup(new_content);
	else
		mini->env_aux.content[i] = ft_strdup("\0");
	i++;
	mini->env_aux.key[i] = NULL;
	mini->env_aux.content[i] = NULL;
	free_char_array(mini->env.key);
	free_char_array(mini->env.content);
	mini->env.key = mini->env_aux.key;
	mini->env.content = mini->env_aux.content;
}

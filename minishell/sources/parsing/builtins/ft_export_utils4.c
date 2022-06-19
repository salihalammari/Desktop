/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:46:45 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:41:54 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	already_exist(t_struct *mini, char *key, char *value, int i)
{
	char	*aux;

	if (ft_strncmp(mini->env.key[i], key, \
				ft_strlen(mini->env.key[i])) == 0)
	{
		aux = ft_strdup(mini->env.content[i]);
		malloc_check_strdup(aux);
		free(mini->env.content[i]);
		take_off_quotes(aux);
		mini->env.content[i] = ft_strjoin(aux, value);
		free(aux);
		return (1);
	}
	return (0);
}

void	print_export(t_struct *mini)
{
	int	i;

	if (!mini->tokens[1])
	{
		copy_export(mini, 1);
		sort_2d_str(mini, mini->env.len);
		i = 0;
		while (mini->sorted.key[i])
		{
			if (!(mini->sorted.content[i][0] == '\"' && \
						mini->sorted.content[i][1] == '\"') && \
					mini->sorted.content[i][0] != '\0')
				printf("declare -x %s=\"%s\"\n", mini->sorted.key[i], \
						mini->sorted.content[i]);
			else if (mini->sorted.content[i][0] == '\0')
				printf("declare -x %s\n", mini->sorted.key[i]);
			else
				printf("declare -x %s=%s\n", mini->sorted.key[i], \
						mini->sorted.content[i]);
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

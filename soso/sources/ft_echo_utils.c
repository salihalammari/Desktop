/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:43:33 by slammari          #+#    #+#             */
/*   Updated: 2022/06/18 19:48:43 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_3(char *aux, char *str, char *split)
{
	aux = ft_strdup(str);
	malloc_check_strdup(aux);
	free(str);
	str = ft_strjoin(aux, " ");
	free(aux);
	aux = ft_strdup(str);
	malloc_check_strdup(aux);
	free(str);
	str = ft_strjoin(aux, split);
	free(aux);
}

void	join_args_after_redir(char **split, char *mini_tokens_i, int i)
{
	char	*aux;
	char	*str;

	aux = NULL;
	str = ft_strdup("");
	malloc_check_strdup(str);
	while (split[i])
	{
		join_3(aux, str, split[i]);
		i++;
	}
	free_char_array(&split);
	aux = ft_strdup(mini_tokens_i);
	malloc_check_strdup(aux);
	free(mini_tokens_i);
	mini_tokens_i = ft_strjoin(aux, str);
	free(aux);
	free(str);
}

int	check_redir_out(t_struct *mini)
{
	int	i;
	int	j;

	i = 0;
	while (mini->commands[i])
	{
		j = 0;
		while (mini->commands[i][j])
		{
			if (mini->commands[i][j] == '>' \
					|| mini->commands[i][j] == '<')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	*echo_redir_in(t_struct *mini, char *mini_tokens_i \
		, char ***split, int *i)
{
	char	*aux;

	aux = ft_strdup(mini_tokens_i);
	malloc_check_strdup(mini_tokens_i);
	free(mini_tokens_i);
	mini_tokens_i = ft_substr(aux, 5, find_char(aux, '>') - 5);
	malloc_check_strdup(mini_tokens_i);
	free(aux);
	free_char_array(split);
	*split = ft_split(mini->commands[2], ' ');
	malloc_check_split(*split);
	if (*split[0][0] == '>' && *split[0][1] == '\0')
		*i = 2;
	else if (*split[0][0] == '>' && *split[0][1] != '\0')
		*i = 1;
	else if (*split[0][0] != '>')
		return (mini_tokens_i);
	return (NULL);
}

void	echo_redir(t_struct *mini, char **mini_tokens_i)
{
	char	*copy;

	copy = ft_strdup(*mini_tokens_i);
	malloc_check_strdup(copy);
	free(*mini_tokens_i);
	*mini_tokens_i = echo_with_redir(mini, copy);
}

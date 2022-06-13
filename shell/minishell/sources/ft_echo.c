/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:02:07 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:02:09 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_struct *mini)
{
	int	j;
	int	n;

	n = init_echo(mini, 0);
	j = 0;
	if (mini->split.q == 0)
	{
		if (mini->tokens[1])
		{
			print_echo(mini, mini->token.to_print);
			if (!mini->has_flag)
				ft_putstr_fd("\n", mini->out_fd);
		}
		else
			ft_putstr_fd("\n", mini->out_fd);
	}
	else
		printf("minishell: quotes error\n");
}

int	init_echo(t_struct *mini, int n)
{
	if (mini->tokens[0][0] != '|')
		n = 1;
	else
		n = 2;
	return (n);
}

static char	*echo_with_redir(t_struct *mini, char *mini_tokens_i)
{
	char	*aux;
	char	*str;
	int		i;
	char	**split;

	i = 2;
	str = ft_strdup("");
	malloc_check_strdup(str);
	split = ft_split(mini->commands[1], ' ');
	malloc_check_split(split);
	if (split[0][1] != '\0')
		i = 1;
	while (split[i])
	{
		aux = ft_strdup(str);
		malloc_check_strdup(aux);
		free(str);
		str = ft_strjoin(aux, " ");
		free(aux);
		aux = ft_strdup(str);
		malloc_check_strdup(aux);
		free(str);
		str = ft_strjoin(aux, split[i]);
		free(aux);
		i++;
	}
	free_char_array(split);
	aux = ft_strdup(mini_tokens_i);
	malloc_check_strdup(aux);
	free(mini_tokens_i);
	mini_tokens_i = ft_strjoin(aux, str);
	free(aux);
	free(str);
	return (mini_tokens_i);
}

void	print_echo(t_struct *mini, char *mini_tokens_i)
{
	int	i;
	int	flag;
	char	*copy;

	i = 0;
	flag = 0;
	while (mini->line_read[i])
	{
		if (mini->line_read[i] == '>' && find_char(mini_tokens_i, '>') == (int)ft_strlen(mini_tokens_i))
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		copy = ft_strdup(mini_tokens_i);
		malloc_check_strdup(copy);
		free(mini_tokens_i);
		mini_tokens_i = echo_with_redir(mini, copy);
	}
	if (!ft_strncmp(mini_tokens_i, "$?", 2))
		ft_putnbr_fd(g_ret_number, mini->out_fd);
	else
	{
		ft_putstr_fd(mini_tokens_i, mini->out_fd);
		g_ret_number = 0;
	}
	free(mini_tokens_i);
	mini_tokens_i = NULL;
	mini->token.to_print = NULL;
}

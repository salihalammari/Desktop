/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:06:09 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:06:11 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_cmd(t_struct *mini, char *in, int i)
{
	int	j;

	init_split_struct(mini);
	in = clean_spaces(in);
	while (i < (int)ft_strlen(in))
	{
		if (mini->split.q == 0 && (in[i] == D_QUOTE || in[i] == QUOTE))
			mini->split.q = in[i];
		else
		{
			if (mini->split.q == in[i])
				mini->split.q = 0;
			else
				i = count_pipe(mini, in, i);
		}
		mini->split.len++;
		i++;
	}
	if (ft_strlen(in) > 0)
	{
		mini->commands[mini->split.n_comand]
			= ft_substr(in, mini->split.ini, i);
		if (!check_quote_s1(mini->commands[mini->split.n_comand]))
			return ;
		take_off_quotes(mini->commands[mini->split.n_comand]);
		mini->split.n_comand++;
	}
	free(in);
	mini->commands[mini->split.n_comand] = NULL;
}

void	init_split_struct(t_struct *mini)
{
	mini->split.n_comand = 0;
	mini->split.ini = 0;
	mini->split.len = 0;
	mini->split.qtt_pipe = 0;
	mini->split.q = 0;
	mini->last_redir = 0;
	mini->redir_flag = 0;
	mini->name_file = NULL;
}

char	*clean_spaces(char *in)
{
	char	*aux;

	aux = ft_strtrim(in, " ");
	in = aux;
	return (in);
}

void	rider_before_cmd(t_struct *mini, char *in, int i)
{
	char	**split;
	char	*copy;
	char	*aux;
	int		n;

	split = ft_split(in, ' ');
	if (!split)
	{
		printf("malloc error\n");
		exit(1);
	}
	if (!split[1])
		return ;
	else if (split[1] && (find_char(split[0], '>') != (int)ft_strlen(split[0]) || find_char(split[0], '<') != (int)ft_strlen(split[0])) && !split[2])
		return ;
	n = 2;
	if ((in[1] == '>' || in[1] == '<') && in[2] == ' ')
		n = 2;
	else if (in[1] != ' ')
		n = 1;
	mini->commands[mini->split.n_comand] = ft_strdup("");
	while (ft_strncmp(split[n], "|", 1) != 0 && split[n])
	{
		aux = ft_strdup(split[n]);
		copy = ft_strdup(mini->commands[mini->split.n_comand]);
		free(mini->commands[mini->split.n_comand]);
		mini->commands[mini->split.n_comand] = ft_strjoin(copy, " ");
		free(copy);
		copy = ft_strdup(mini->commands[mini->split.n_comand]);
		free(mini->commands[mini->split.n_comand]);
		mini->commands[mini->split.n_comand] = ft_strjoin(copy, aux);
		free(copy);
		free(aux);
		n++;
		if (!split[n])
			break ;
	}
	free_char_array(split);
	mini->split.ini = i;
	mini->split.len = 0;
	mini->split.n_comand++;
}

int	count_pipe(t_struct *mini, char *in, int i)
{
	if (in[i] == '|' || in[i] == '<' || in[i] == '>')
	{
		if (in[i] == '|' && mini->split.q == 0)
			mini->split.qtt_pipe++;
		if (mini->split.q == 0  && i > 1 && mini->split.len > 0)
		{
			mini->commands[mini->split.n_comand] = ft_substr(in,
					mini->split.ini, mini->split.len);
			mini->split.ini = i;
			mini->split.len = 0;
			mini->split.n_comand++;
			if (in[i] == '>')
				mini->last_redir = 1;
			else
				mini->last_redir = 0;
			if (in[i] == in[i + 1])
			{
				i++;
				mini->split.len = 1;
			}
		}
		if (mini->split.q == 0 && i == 0 && (in[0] == '<' || in[0] == '>' || (in[0] == '>' && in[1] == '>') || (in[0] == '<' && in[1] == '<')))
			rider_before_cmd(mini, in, i);
	}
	return (i);
}

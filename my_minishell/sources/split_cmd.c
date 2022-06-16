/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:06:09 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/16 20:09:02 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_cmd(char *in)
{
	int	i;
	i = 0;
	while (in[i + 1])
	{
		if ((in[i] == D_QUOTE || in[i] == QUOTE) && (in[i + 1] == D_QUOTE || in[i + 1] == QUOTE))
			return (1);
		i++;
	}
	return (0);
}

int    check_cmd(t_struct *mini)
{
    int    i;
    int    flag;

    i = 0;
    flag = 0;
    while (mini->line_read[i + 1])
    {
        if ((mini->line_read[i] == D_QUOTE || mini->line_read[i] == QUOTE) && mini->line_read[i + 1] == ' ')
            flag = 1;
        i++;
    }
    i = 0;
    while (mini->line_read[i + 1])
    {
        if (ft_isalnum(mini->line_read[i]) && mini->line_read[i + 1] == ' ')
            flag = 1;
        i++;
    }
    return (flag);
}

void	split_cmd(t_struct *mini, int i)
{
	char	*copy;
	init_split_struct(mini);
	if (!check_cmd(mini))
	{
		printf("minishelle: %s: command not found\n", mini->line_read);
		g_ret_number = 1;
		return ;
	}
	copy = ft_strdup(mini->line_read);
	free(mini->line_read);
	mini->line_read = NULL;
	mini->line_read = clean_spaces(copy);
	free(copy);
	copy = NULL;
	if (!check_pipe_between_quotes(mini->line_read))
		return ;
	while (i < (int)ft_strlen(mini->line_read))
	{
		if (mini->split.q == 0 && (mini->line_read[i] == D_QUOTE
			|| mini->line_read[i] == QUOTE))
			mini->split.q = mini->line_read[i];
		else
		{
			if (mini->split.q == mini->line_read[i])
				mini->split.q = 0;
			else
				i = count_pipe(mini, mini->line_read, i);
		}
		mini->split.len++;
		i++;
	}
	if (ft_strlen(mini->line_read) > 0)
	{
		mini->commands[mini->split.n_comand] = ft_substr(mini->line_read, mini->split.ini, i);
		if (!check_quote_s1(mini->commands[mini->split.n_comand]))
			return ;
		take_off_quotes(mini->commands[mini->split.n_comand]);
		mini->split.n_comand++;
	}
	free(mini->line_read);
	mini->line_read = NULL;
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
	mini->split.permi = 0;
	mini->line = NULL;
	mini->token.to_print = NULL;
}
char	*clean_spaces(char *in)
{
	char	*aux;
	aux = ft_strtrim(in, " ");
	in = ft_strdup(aux);
	free(aux);
	return (in);
}
void	rider_before_cmd(t_struct *mini, char *in, int i)
{
	char	**split;
	char	*copy;
	char	*aux;
	int		n;
	split = ft_split(in, ' ');
	malloc_check_split(split);
	if (!split[1])
	{
		free_char_array(&split);
		return ;
	}
	else if (split[1] && (split[0][ft_strlen(split[0]) - 1] == '>' || split[0][ft_strlen(split[0]) - 1] == '<') && !split[2])
	{
		free_char_array(&split);
		return ;
	}
	n = 2;
	if ((in[1] == '>' || in[1] == '<') && in[2] == ' ')
		n = 2;
	else if (in[1] != ' ')
		n = 1;
	mini->commands[mini->split.n_comand] = ft_strdup("");
	malloc_check_strdup(mini->commands[mini->split.n_comand]);
	while (ft_strncmp(split[n], "|", 1) != 0 && split[n])
	{
		aux = ft_strdup(split[n]);
		malloc_check_strdup(aux);
		copy = ft_strdup(mini->commands[mini->split.n_comand]);
		malloc_check_strdup(copy);
		free(mini->commands[mini->split.n_comand]);
		mini->commands[mini->split.n_comand] = ft_strjoin(copy, " ");
		free(copy);
		copy = ft_strdup(mini->commands[mini->split.n_comand]);
		malloc_check_strdup(copy);
		free(mini->commands[mini->split.n_comand]);
		mini->commands[mini->split.n_comand] = ft_strjoin(copy, aux);
		free(copy);
		free(aux);
		n++;
		if (!split[n])
			break ;
	}
	free_char_array(&split);
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

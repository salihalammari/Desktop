/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:06:09 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/23 16:34:37 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	split_cmd(t_struct *mini, int i)
{
	char	*copy;

	init_split_struct(mini);
	if (check_cmd(mini) && ft_strncmp(mini->line_read, "export ", 7) \
		&& ft_strncmp(mini->line_read, "echo ", 5))
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
	lock_unlock(mini, &i);
	if (!cmd_quotes(mini, &i))
		return ;
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
	mini->heredoc = 0;
	mini->remains = NULL;
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
	int		n;

	split = ft_split(in, ' ');
	malloc_check_split(split);
	if (!check_redir_before(split))
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
	redir_before_cmd_assist(mini, split, &n);
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
		if (mini->split.q == 0 && i > 1 && mini->split.len > 0)
			count_pipe_assist(mini, in, i);
		if (mini->split.q == 0 && i == 0 && (in[0] == '<' || in[0] == '>' || \
					(in[0] == '>' && in[1] == '>') \
					|| (in[0] == '<' && in[1] == '<')))
			rider_before_cmd(mini, in, i);
	}
	return (i);
}

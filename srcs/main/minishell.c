/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:21:53 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 22:27:57 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	initialization(t_mini *mini, char **env)
{
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	mini->exit = 0;
	mini->ret = 0;
	mini->no_exec = 0;
	mini->no_env = 0;
	reset_all_fds(mini);
	init_env(mini, env);
	init_copy_env(mini, env);
	increment_shlvl(mini->env);
	increment_shlvl(mini->copy_env);
}

void	exit_from_parent(t_mini *mini)
{
	if (mini->parent == 0)
	{
		freeing_token(mini->start);
		exit(mini->ret);
	}
}

void	exec_and_redir(t_mini *mini, t_token *token)
{
	t_token	*previous;
	t_token	*next;
	int		pipe;

	previous = previous_separ(token, NOSKIP);
	next = next_separator(token, NOSKIP);
	pipe = 0;
	if (ft_istype(previous, TRUNC))
		output(mini, token, TRUNC);
	else if (ft_istype(previous, APPEND))
		output(mini, token, APPEND);
	else if (ft_istype(previous, INPUT) || ft_istype(previous, HEREDOC))
		input(mini, token);
	else if (ft_istype(previous, PIPE))
		pipe = minipipe(mini);
	if (pipe == -1)
		return ;
	if (next && pipe != 1)
		exec_and_redir(mini, next->next);
	if ((ft_istype(previous, PIPE) || !previous)
		&& pipe != 1 && mini->no_exec == 0)
		execution(mini, token);
}

void	minishell(t_mini *mini)
{
	t_token	*token;
	int		status;

	token = last_token(mini->start, NOSKIP);
	if (has_atype_of(mini->start, "THAI"))
		token = mini->start->next;
	while (mini->exit == 0 && token)
	{
		mini->charge = 1;
		mini->parent = 1;
		mini->last = 1;
		exec_and_redir(mini, token);
		dup2_in_out(mini);
		close_multi_fds(mini);
		reset_all_fds(mini);
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (mini->last == 0)
			mini->ret = status;
		exit_from_parent(mini);
		mini->no_exec = 0;
		if (token)
			token = last_token(token, SKIP);
	}
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	initialization(&mini, env);
	while (mini.exit == 0)
	{
		mini.pipe = 0;
		mini.heredoc = 0;
		mini.type_quotes = 0;
		mini.redirout = 0;
		sig_init();
		parser(&mini);
		if (mini.start != NULL && check_syntax(&mini, mini.start))
			minishell(&mini);
		unlinking_heredoc_files(&mini);
		freeing_token(mini.start);
	}
	freeing_env(mini.env);
	freeing_env(mini.copy_env);
	return (mini.ret);
}

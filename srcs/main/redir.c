/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:21:48 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 23:26:38 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	expanding(t_mini *mini, t_token *token, char **file)
{
	if (mini->type_quotes == 0 || mini->type_quotes == 1)
	{
		*file = expander(token->str, mini);
		if (!*file)
			return (ERROR);
	}
	else
	{
		*file = ft_strdup(token->str);
		if (!*file)
			return (ERROR);
	}
	return (SUCCESS);
}

void	output(t_mini *mini, t_token *token, int type)
{
	char	*file;

	if (expanding(mini, token, &file))
		return ;
	close_fd(mini->fdout);
	if (type == TRUNC)
		mini->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		mini->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (!access(file, F_OK) && access(file, W_OK) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(file, STDERR);
		ft_putendl_fd(": permission denied", STDERR);
		mini->no_exec = 1;
		mini->ret = 1;
		return ;
	}
	mini->redirout = 1;
	free(file);
	mini->pipe = 0;
}

void	input(t_mini *mini, t_token *token)
{
	char	*file;

	if (expanding(mini, token, &file))
		return ;
	close_fd(mini->fdin);
	mini->fdin = open(file, O_RDONLY, S_IRWXU);
	if (mini->fdin == -1)
	{
		mini->no_exec = 1;
		if (mini->heredoc == 1)
			return ;
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(file, STDERR);
		if (access(file, F_OK) == -1)
			ft_putendl_fd(": No such file or directory", STDERR);
		else if (!access(file, F_OK) && access(file, R_OK) == -1)
			ft_putendl_fd(": permission denied", STDERR);
		mini->ret = 1;
		free(file);
		return ;
	}
	free(file);
	dup2(mini->fdin, STDIN);
}

static int	dup_and_init_in_process(t_mini *mini, pid_t pid, int *pipefd)
{
	if (pid == 0)
	{
		close_fd(pipefd[1]);
		dup2(mini->fdin, 0);
		mini->fdin = pipefd[0];
		mini->pipin = pipefd[0];
		mini->parent = 0;
		mini->pid = -1;
		mini->no_exec = 0;
		return (2);
	}
	else
	{
		close_fd(pipefd[0]);
		dup2(mini->fdout, 1);
		mini->fdout = pipefd[1];
		mini->pid = pid;
		mini->last = 0;
		return (1);
	}
}

int	minipipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	mini->pipe = 1;
	pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd("minishell: fork: Resource temporarily unavailable", 2);
		mini->no_exec = 1;
		return (-1);
	}
	run_signals(2);
	return (dup_and_init_in_process(mini, pid, pipefd));
}

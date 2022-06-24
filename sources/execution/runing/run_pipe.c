/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:11:40 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/24 14:35:39 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_commands(t_struct *mini)
{
	int		j;
	int		fd[2];

	j = 0;
	mini->c = 0;
	mini->last_redir = 0;
	while (j < mini->split.qtt_pipe)
	{
		if (pipe(fd) < 0)
		{
			printf("Pipe error\n");
			g_ret_number = 127;
		}
		mini->out_fd = fd[1];
		exec_assist(mini, 0);
		close(mini->out_fd);
		if (mini->in_fd != 0)
			close(mini->in_fd);
		mini->in_fd = fd[0];
		j++;
	}
	exec_assist(mini, 1);
}

void	cmds_execution(t_struct *mini, int flag)
{
	int	i;

	tokenizer(mini);
	if (mini->split.q == 0)
	{
		i = -1;
		while (mini->tokens[i++])
			take_off_quotes(mini->tokens[i]);
	}
	if (mini->tokens[0])
		is_builtin(mini->tokens[0], mini);
	if (mini->in_fd != -1)
		exec_process(mini, mini->in_fd, mini->out_fd, flag);
	free_char_array(&mini->tokens);
	free(mini->token.to_exec);
	mini->token.to_exec = NULL;
}

void	exec_assist(t_struct *mini, int flag)
{
	if (!action(mini))
		return ;
	if (mini->out_fd == -1)
	{
		printf("minishell: Permission denied\n");
		mini->out_fd = dup(1);
		free(mini->name_file);
		g_ret_number = 1;
		return ;
	}
	if (mini->commands[0][0] != '>')
		cmds_execution(mini, flag);
	free(mini->name_file);
}

int	call_redirection(t_struct *mini)
{
	while (mini->commands[mini->c] && mini->commands[mini->c][0] != '|')
	{
		if (!redirect_out(mini, mini->c))
			return (0);
		if (!redirect_in(mini, mini->c, NULL))
			return (0);
		mini->c++;
	}
	return (1);
}

int	action(t_struct *mini)
{
	free(mini->line);
	mini->line = NULL;
	mini->line = ft_strdup(mini->commands[mini->c]);
	malloc_check_strdup(mini->line);
	if (mini->split.n_comand > 1)
		mini->c++;
	mini->error_name_file = NULL;
	if (!call_redirection(mini))
		return (0);
	if (mini->error_name_file != NULL && mini->heredoc == 0)
	{
		g_ret_number = 1;
		if (access(mini->error_name_file, F_OK) == -1)
			printf("minishell: %s: %s", mini->error_name_file, ERROR_DIR);
		else if (!access(mini->error_name_file, F_OK) \
			&& access(mini->error_name_file, R_OK) == -1)
		{
			printf("minishell: %s: Permission denied\n", mini->error_name_file);
			free(mini->error_name_file);
			mini->error_name_file = NULL;
		}
		return (0);
	}
	return (1);
}

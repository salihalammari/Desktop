/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:23:14 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 12:35:22 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fd(int fd)
{
	if (fd > 0)
		close(fd);
}

void	dup2_in_out(t_mini *mini)
{
	dup2(mini->in, STDIN);
	dup2(mini->out, STDOUT);
}

void	close_multi_fds(t_mini *mini)
{
	close_fd(mini->fdin);
	close_fd(mini->fdout);
	close_fd(mini->pipin);
	close_fd(mini->pipout);
}

void	reset_all_fds(t_mini *mini)
{
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
	mini->pid = -1;
}

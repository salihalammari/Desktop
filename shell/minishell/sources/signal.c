/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:05:55 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:05:57 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_exit(t_struct *mini)
{
	int	i;
	char	*ex;
	char	*copy;
	char	*c;

	i = 0;
	if (mini->env_flag == 1)
		printf("\n");
	c = ft_itoa(mini->prompt_len);
	ex = ft_strjoin("\033[1A\033[", c);
	free(c);
	copy = ft_strdup(ex);
	malloc_check_strdup(copy);
	free(ex);
	ex = ft_strjoin(copy, "C exit\n");
	free(copy);
	write(1, ex, ft_strlen(ex));
	free(ex);
}

void	run_signals(t_struct *mini ,int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		write_exit(mini);
		exit(0);
	}
}

void	restore_prompt(int sig)
{
	g_ret_number = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_ret_number = 130;
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	back_slash(int sig)
{
	g_ret_number = 131;
	(void)sig;
}

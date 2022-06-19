/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:47:05 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 11:47:06 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_line(t_struct *mini)
{
	char	*prompt;

	prompt = create_prompt();
	run_signals(mini, 1);
	mini->line_read = readline(prompt);
	if (mini->line_read && *mini->line_read)
		add_history(mini->line_read);
	mini->prompt_len = ft_strlen(prompt) \
			- (ft_strlen(CYAN) + ft_strlen(WHITE) + 1);
	free(prompt);
}

void	prompt_desine(char **prompt, char **tab1)
{
	char	*buf;
	char	*cyan;
	char	*white;

	buf = get_cwd_buf();
	cyan = ft_strdup(CYAN);
	malloc_check_strdup(cyan);
	white = ft_strdup(WHITE);
	malloc_check_strdup(white);
	*prompt = ft_strjoin(cyan, buf);
	free(buf);
	*tab1 = ft_strjoin(*prompt, white);
	free(*prompt);
	free(white);
	free(cyan);
	*prompt = ft_strjoin(*tab1, " $ ");
	free(*tab1);
	*tab1 = ft_strdup(*prompt);
	free(*prompt);
}

char	*create_prompt(void)
{
	char	*prompt;
	char	*tab1;

	prompt = NULL;
	tab1 = NULL;
	prompt_desine(&prompt, &tab1);
	if (g_ret_number == 0)
		prompt = ft_strjoin("\033[0;32m➜ ", tab1);
	else
		prompt = ft_strjoin("\033[0;31m➜ ", tab1);
	free(tab1);
	return (prompt);
}

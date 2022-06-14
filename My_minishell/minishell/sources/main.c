/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:04:27 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:04:28 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize(t_struct *mini, char **env)
{
	char	*pwd;

	mini->last_redir = 0;
	g_ret_number = 0;
	mini->tokens = (char **) NULL;
	if (!*env)
	{
		mini->env_flag = 1;
		mini->env.env = malloc(sizeof(char *) * 4);
		mini->env.env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
		malloc_check_strdup(mini->env.key[0]);
		mini->env.env[1] = ft_strdup("SHLVL=1");
		malloc_check_strdup(mini->env.env[1]);
		pwd = get_cwd_buf();
		mini->env.env[2] = ft_strjoin("PWD=", pwd);
		free(pwd);
		mini->env.env[3] = NULL;
		create_env(mini, env);
		init_path(mini);
	}
	if (*env)
	{
		mini->env_flag = 0;
		create_env(mini, env);
		init_path(mini);
		mini->home = ft_strdup(find_env(mini, "HOME"));
		malloc_check_strdup(mini->home);
	}
}

void	get_line(t_struct *mini)
{
	char	*prompt;

	prompt = create_prompt();
	run_signals(mini, 1);
	mini->line_read = readline(prompt);
	if (mini->line_read && *mini->line_read)
		add_history(mini->line_read);
	mini->prompt_len = ft_strlen(prompt) - (ft_strlen(CYAN) + ft_strlen(WHITE) + 1);
	free(prompt);
}

char	*create_prompt(void)
{
	char	*buf;
	char	*prompt;
	char	*cyan;
	char	*white;
	char	*tab1;

	buf = get_cwd_buf();
	cyan = ft_strdup(CYAN);
	malloc_check_strdup(cyan);
	white = ft_strdup(WHITE);
	malloc_check_strdup(white);
	prompt = ft_strjoin(cyan, buf);
	free(buf);
	tab1 = ft_strjoin(prompt, white);
	free(prompt);
	free(white);
	free(cyan);
	prompt = ft_strjoin(tab1, " $ ");
	free(tab1);
	return (prompt);
}

int	main(int ac, char **av, char **env)
{
	t_struct	mini;
	int	out;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	initialize(&mini, env);
	mini.token.to_print = NULL;
	mini.line = NULL;
	while (1)
	{
		out = dup(1);
		mini.out_fd = STDOUT_FILENO;
		mini.in_fd = STDIN_FILENO;
		get_line(&mini);
		if (mini.line_read)
		{
			if (ft_strlen(mini.line_read) != 0)
			{
				split_cmd(&mini, 0);
				if (mini.split.n_comand > 0 && mini.commands[0][0] != '|')
					exec_commands(&mini, out);
				if (mini.commands[0] && mini.commands[0][0] == '|')
					printf(ERROR_PIPE);
				free_char_array2(mini.commands);
				free(mini.token.to_print);
			}
			free(mini.line_read);
		}
		else
			run_signals(&mini, 3);
	}
}

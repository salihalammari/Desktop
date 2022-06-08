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
	int		flag;

	mini->last_redir = 0;
	g_ret_number = 0;
	mini->tokens = (char **) NULL;
	if (!*env)
	{
		flag = 1;
		mini->env.env = malloc(sizeof(char *) * 4);
		mini->env.env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
		mini->env.env[1] = ft_strdup("SHLVL=1");
		pwd = get_cwd_buf();
		mini->env.env[2] = ft_strjoin("PWD=", pwd);
		free(pwd);
		mini->env.env[3] = NULL;
		create_env(mini, env, flag);
		init_path(mini);
	}
	if (*env)
	{
		flag = 0;
		create_env(mini, env, flag);
		init_path(mini);
		mini->home = ft_strdup(find_env(mini, "HOME"));
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
	white = ft_strdup(WHITE);
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
	int	rl_catch_signals;
	int	out;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	initialize(&mini, env);
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
				split_cmd(&mini, mini.line_read, 0);
				if (mini.split.n_comand > 0 && mini.commands[0][0] != '|')
					exec_commands(&mini, out);
				if (mini.commands[0] && mini.commands[0][0] == '|')
					printf(ERROR_PIPE);
				free_char_array2(mini.commands);
			}
			free(mini.line_read);
		}
		else
			run_signals(&mini, 3);
	}
}

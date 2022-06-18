/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:04:27 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/18 19:12:32 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_no_env(t_struct *mini, char **env)
{
	char	*pwd;

	mini->env_flag = 1;
	mini->env.env = malloc(sizeof(char *) * 4);
	mini->env.env[0] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
	malloc_check_strdup(mini->env.env[0]);
	mini->env.env[1] = ft_strdup("SHLVL=1");
	malloc_check_strdup(mini->env.env[1]);
	pwd = get_cwd_buf();
	mini->env.env[2] = ft_strjoin("PWD=", pwd);
	free(pwd);
	mini->env.env[3] = NULL;
	create_env(mini, env);
	init_path(mini);
}

void	initialize(t_struct *mini, char **env)
{
	rl_catch_signals = 0;
	mini->last_redir = 0;
	g_ret_number = 0;
	mini->tokens = (char **) NULL;
	if (!*env)
		if_no_env(mini, env);
	if (*env)
	{
		mini->env_flag = 0;
		create_env(mini, env);
		init_path(mini);
		mini->home = ft_strdup(find_env(mini, "HOME"));
		malloc_check_strdup(mini->home);
	}
	mini->token.to_print = NULL;
	mini->line = NULL;
	*mini->commands = NULL;
	mini->token.to_print = NULL;
	mini->error_name_file = NULL;
}

static void	fd_init(t_struct *mini)
{
	mini->split.sd_out = dup(1);
	mini->out_fd = STDOUT_FILENO;
	mini->in_fd = STDIN_FILENO;
	get_line(mini);
}

int	main(int ac, char **av, char **env)
{
	t_struct	mini;

	(void)ac;
	(void)av;
	initialize(&mini, env);
	while (1)
	{
		fd_init(&mini);
		if (mini.line_read)
		{
			if (ft_strlen(mini.line_read) != 0)
			{
				split_cmd(&mini, 0);
				if (mini.split.n_comand > 0 && mini.commands[0][0] != '|')
					exec_commands(&mini);
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

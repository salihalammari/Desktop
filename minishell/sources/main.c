#include "minishell.h"

void	initialize(t_struct *mini, char **env)
{
	mini->last_redir = 0;
	g_ret_number = 0;
	mini->tokens = (char **) NULL;
	create_env(mini, env);
	init_path(mini);
	mini->home = ft_strdup(find_env(mini, "HOME"));
}

void	get_line(t_struct *mini)
{
	char	*prompt;

	prompt = create_prompt();
	run_signals(1);
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
			run_signals(3);
	}
}

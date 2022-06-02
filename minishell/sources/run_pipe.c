#include "minishell.h"

void	exec_commands(t_struct *mini, int out)
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
		exec_assist(mini, 0, out);
		close(mini->out_fd);
		if (mini->in_fd != 0)
			close(mini->in_fd);
		mini->in_fd = fd[0];
		j++;
	}
	exec_assist(mini, 1, out);
}

void	exec_assist(t_struct *mini, int flag, int out)
{
	int	i;

	action(mini);
	if (mini->out_fd == -1)
	{
		printf("minishell: Permission denied\n");
		mini->out_fd = dup(1);
		free(mini->name_file);
		return ;
	}
	if (mini->commands[0][0] != '>')
	{
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
			exec_process(mini, mini->in_fd, mini->out_fd, flag, out);
		free_char_array(mini->tokens);
		free(mini->token.to_exec);
	}
	if (mini->name_file)
		free(mini->name_file);
}

void	action(t_struct *mini)
{
	mini->line = ft_strdup(mini->commands[mini->c]);
	if (mini->split.n_comand > 1 )
		mini->c++;
	mini->error_name_file = NULL;
	while (mini->commands[mini->c] && mini->commands[mini->c][0] != '|')
	{
		redirect_out(mini, mini->c);
		redirect_in(mini, mini->c, NULL);
		mini->c++;
	}
	if (mini->error_name_file != NULL)
	{
		g_ret_number = 1;
		printf("minishell: %s: %s", mini->error_name_file, ERROR_DIR);
		free(mini->error_name_file);
	}
}

void	exec_process(t_struct *mini, int in, int out, int flag, int sor)
{
	pid_t	pid;

	if (mini->is_builtin && mini->tokens[0])
		run_builtin(mini);
	else
	{
		pid = fork();
		run_signals(2);
		if (pid < 0)
		{
			printf("Fork error\n");
			g_ret_number = 127;
		}
		else if (pid == 0)
		{
			file_descriptor_handler(in, out);
			g_ret_number = 127;
			ft_execve_pipe(mini, 0, "", sor);
			exit(g_ret_number);
		}
		else if (pid != 0 && flag == 1)
			waitpid(pid, &g_ret_number, WUNTRACED);
		if (WIFEXITED(g_ret_number))
			g_ret_number = WEXITSTATUS(g_ret_number);
	}
}

int	str_ncmp(char *str1, char *str2, int n)
{
	while (--n > 0 && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str2 - *str1);
}

int	str_ichr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*path_join(char *path, char *bin)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(sizeof(char) * (str_ichr(path, 0) + str_ichr(bin, 0) + 2));
	if (!joined)
	{
		free(joined);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (path[j])
		joined[i++] = path[j++];
	joined[i++] = '/';
	j = 0;
	while (bin[j])
		joined[i++] = bin[j++];
	joined[i] = 0;
	return (joined);
}

char	*str_ndup(char *str, unsigned int n)
{
	char			*duped;
	unsigned int	i;

	i = 0;
	duped = malloc(sizeof(char) * (n + 1));
	if (!duped)
	{
		free(duped);
		return (NULL);
	}
	while (i < n)
		duped[i++] = *str++;
	duped[n] = 0;
	return (duped);
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && str_ncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && str_ichr(path, ':') > -1)
	{
		dir = str_ndup(path, str_ichr(path, ':'));
		bin = path_join(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_ichr(path, ':') + 1;
	}
	return (cmd);
}

void	ft_execve_pipe(t_struct *mini, int i, char *command, int out)
{
	char	*path;

	if (mini->tokens[0])
	{
		path = get_path(mini->tokens[0], mini->env.env);
		g_ret_number = execve(path, &mini->tokens[0],
				mini->env.env);
		while (mini->path && mini->path[i] != NULL)
		{	
			command = ft_strdup(mini->path[i]);
			if (mini->tokens[0][0] == '|' && mini->tokens[1])
			{
				if (!mini->tokens[0][1])
					spaces_in_pipe(mini, 2, command);
				else
				{
					mini->tokens[0] = &mini->tokens[0][1];
					spaces_in_pipe(mini, 1, command);
				}
			}
			else
				spaces_in_pipe(mini, 1, command);
			i++;
		}
		execve_error(mini, out);
	}
}

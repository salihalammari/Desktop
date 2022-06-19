/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:47:14 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:44:15 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	forking(t_struct *mini, int in, int out, int flag)
{
	pid_t	pid;

	pid = fork();
	run_signals(mini, 2);
	if (pid < 0)
	{
		printf("Fork error\n");
		g_ret_number = 127;
	}
	else if (pid == 0)
	{
		file_descriptor_handler(in, out);
		g_ret_number = 127;
		ft_execve_pipe(mini, 0, "");
		exit(g_ret_number);
	}
	else if (pid != 0 && flag == 1)
		waitpid(pid, &g_ret_number, WUNTRACED);
	if (WIFEXITED(g_ret_number))
		g_ret_number = WEXITSTATUS(g_ret_number);
}

void	exec_process(t_struct *mini, int in, int out, int flag)
{
	if (mini->is_builtin && mini->tokens[0])
		run_builtin(mini);
	else
	{
		forking(mini, in, out, flag);
		(void)flag;
	}
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

char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && str_ichr(path, ':') > -1)
	{
		dir = ft_substr(path, 0, str_ichr(path, ':'));
		malloc_check_strdup(dir);
		bin = path_join(dir, cmd);
		malloc_check_strdup(bin);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_ichr(path, ':') + 1;
	}
	return (cmd);
}

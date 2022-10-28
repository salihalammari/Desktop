/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:30:20 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 22:27:45 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	print_error(char *path)
{
	int	fd;
	int	ret;
	DIR	*folder;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(path, STDERR);
	if (ft_strchr(path, '/') == NULL)
		ft_putendl_fd(": command not found", STDERR);
	else if (fd == -1 && folder != NULL)
		ft_putendl_fd(": is a directory", STDERR);
	else if (fd == -1 && folder == NULL)
		ft_putendl_fd(": No such file or directory", STDERR);
	else if (fd != -1 && folder == NULL)
		ft_putendl_fd(": Permission denied", STDERR);
	if (ft_strchr(path, '/') == NULL || (folder == NULL && fd == -1))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	close_fd(fd);
	return (ret);
}

static	int	exec_cmd(char *path, char **args, t_env *env, t_mini *mini)
{
	int		ret;
	char	**env_array;
	char	*ptr;

	ret = SUCCESS;
	if (g_sig.pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ptr = env_to_string(env);
		env_array = ft_split(ptr, '\n');
		ft_memdel(ptr);
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = print_error(path);
		freeing_tab(env_array);
		freeing_token(mini->start);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	return (ret);
}

int	fork_proces(char *path, char **args, t_env *env, t_mini *mini)
{
	int		ret;

	ret = SUCCESS;
	g_sig.pid = fork();
	if (g_sig.pid < 0)
		return (1);
	run_signals(2);
	signal(SIGINT, SIG_IGN);
	ret = exec_cmd(path, args, env, mini);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (WEXITSTATUS(g_sig.exit_status));
	return (WEXITSTATUS(ret));
}

static char	*path_join(const char *s1, const char *s2)
{
	char	*path;
	char	*tmp;

	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, s2);
	if (!path)
		return (NULL);
	ft_memdel(tmp);
	return (path);
}

char	*check_directory(char *bin, char *command)
{
	char			*path;
	DIR				*folder;
	struct dirent	*item;

	folder = opendir(bin);
	path = NULL;
	if (!folder)
		return (NULL);
	item = readdir(folder);
	while (item)
	{
		if (ft_strcmp(item->d_name, command) == 0)
			path = path_join(bin, item->d_name);
		item = readdir(folder);
	}
	closedir(folder);
	return (path);
}

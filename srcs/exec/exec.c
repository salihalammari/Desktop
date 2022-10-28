/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:30:26 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 22:27:48 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**cmd_tab(t_token *start)
{
	int		i;
	char	**tab;
	t_token	*token;

	if (!start)
		return (NULL);
	token = start->next;
	while (token && token->type < TRUNC)
		token = token->next;
	tab = malloc(BUFF_SIZE);
	if (!tab)
		return (NULL);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i++] = token->str;
		token = token->next;
	}
	tab[i] = NULL;
	return (tab);
}

static int	if_env_variable(t_mini *mini, char **cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (mini->type_quotes == 0 || mini->type_quotes == 1)
			cmd[i] = expander(cmd[i], mini);
		else
		{
			cmd[i] = ft_strdup(cmd[i]);
			if (!cmd[i])
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	executor(char **args, t_env *env, t_mini *mini)
{
	char	**bin;
	char	*path;
	int		i;
	int		ret;

	i = 0;
	ret = UNKNOWN_COMMAND;
	while (env && env->value && ft_strncmp(env->value, "PATH=", 5))
		env = env->next;
	if (env == NULL || env->next == NULL)
		return (fork_proces(args[0], args, env, mini));
	bin = ft_split(env->value, ':');
	if (!args[0] && !bin[0])
		return (ERROR);
	i = 1;
	path = check_directory(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_directory(bin[i++], args[0]);
	if (path != NULL)
		ret = fork_proces(path, args, env, mini);
	else
		ret = fork_proces(args[0], args, env, mini);
	freeing_tab(bin);
	ft_memdel(path);
	return (ret);
}

void	execution_center(t_mini *mini, t_token *token)
{
	char	**cmd;

	if (mini->charge == 0)
		return ;
	cmd = cmd_tab(token);
	if (if_env_variable(mini, cmd))
		return ;
	if (cmd && ft_strcmp(cmd[0], "exit") == 0 && has_pipe(token) == 0)
		ft_exit(mini, cmd);
	else if (cmd && is_builtin_cmd(cmd[0]))
		mini->ret = builtin_executor(cmd, mini);
	else if (cmd)
		mini->ret = executor(cmd, mini->env, mini);
	freeing_tab(cmd);
	close_fd(mini->pipin);
	close_fd(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
	mini->charge = 0;
}

void	execution(t_mini *mini, t_token *token)
{
	if (mini->pipe == 0 || (mini->pipe == 1 && mini->redirout == 0))
		dup2(mini->fdout, 1);
	dup2(mini->fdin, 0);
	execution_center(mini, token);
}

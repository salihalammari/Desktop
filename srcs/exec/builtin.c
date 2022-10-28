/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:30:23 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 22:27:47 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin_cmd(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (1);
	if (ft_strcmp(command, "echo") == 0 || ft_strcmp(command, "ECHO") == 0)
		return (1);
	if (ft_strcmp(command, "env") == 0 || ft_strcmp(command, "ENV") == 0)
		return (1);
	if (ft_strcmp(command, "export") == 0)
		return (1);
	if (ft_strcmp(command, "pwd") == 0 || ft_strcmp(command, "PWD") == 0)
		return (1);
	if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

int	builtin_executor(char **args, t_mini *mini)
{
	int		result;

	result = 0;
	if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args, mini);
	if (ft_strcmp(args[0], "echo") == 0 || ft_strcmp(args[0], "ECHO") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args[0], "env") == 0 || ft_strcmp(args[0], "ENV") == 0)
		ft_env(mini->env);
	if (ft_strcmp(args[0], "export") == 0)
	{
		if (args[1])
			empty_env(mini, args);
		ft_export(args, mini->env, mini->copy_env);
	}
	if (ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "PWD") == 0)
		result = ft_pwd(mini);
	if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, mini);
	return (result);
}

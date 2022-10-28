/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:29:38 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 19:15:08 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	print_error(int error, const char *arg)
{
	int	i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == -3 || error == 0)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while ((arg[i] != '=' || error == -3) && arg[i])
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	error_case(char *args, int *i, int *error_ret)
{
	*error_ret = is_valid_env_str(args);
	if (args[0] == '=')
		*error_ret = -3;
	if (*error_ret <= 0)
	{
		if (print_error(*error_ret, args) == ERROR)
		{
			(*i)++;
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	if_no_value(char *args, t_env *env, t_env *secret)
{
	int	new_env;

	if (ft_search(args, '=') == 1)
	{
		new_env = already_exist_in_env(secret, args);
		if (new_env == 0)
			add_to_env(args, secret);
		new_env = already_exist_in_env(env, args);
		if (new_env == 0)
			add_to_env(args, env);
	}
	else
	{
		new_env = already_exist_in_env(secret, args);
		if (new_env == 0)
			add_to_env(args, secret);
	}
	return (new_env);
}

void	exec_export(char **args, t_env *env, t_env *secret)
{
	int	i;
	int	error_ret;
	int	new_env;

	i = 1;
	new_env = 0;
	while (args[i])
	{
		if (ft_search(args[i], '+'))
			concat(&args[i], env);
		if (error_case(args[i], &i, &error_ret))
			continue ;
		if (error_ret == 2)
			new_env = if_no_value(args[i], env, secret);
		else
			new_env = already_exist_in_env(env, args[i]);
		if (new_env == 0)
			if (error_ret == 1)
				add_to_env(args[i], env);
		new_env = already_exist_in_env(secret, args[i]);
		if (new_env == 0)
			add_to_env(args[i], secret);
		i++;
	}
}

int	ft_export(char **args, t_env *env, t_env *secret)
{
	if (!args[1])
	{
		print_env_sorted(secret);
		return (SUCCESS);
	}
	else
		exec_export(args, env, secret);
	return (SUCCESS);
}

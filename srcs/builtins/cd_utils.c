/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:35:05 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 22:27:30 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cd_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static void	copy_value(t_env *env, size_t len, char *oldpwd)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (env->value[i++])
	{
		if (i > (int)len)
			oldpwd[j++] = env->value[i];
	}
	oldpwd[j] = '\0';
}

char	*get_path_from_env(t_env *env, const char *var, size_t len, int flag)
{
	int		s_alloc;
	char	*oldpwd;

	if (!env)
		return (NULL);
	while (env->next != NULL && env)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			oldpwd = malloc(sizeof(char) * s_alloc + 1);
			if (!oldpwd)
				return (NULL);
			copy_value(env, len, oldpwd);
			if (flag)
				ft_putendl_fd(oldpwd, STDOUT);
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

int	update_oldpwd(t_mini *mini)
{
	char	*oldpwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	if (already_exist_in_env(mini->env, oldpwd) == 0 && \
		already_exist_in_env(mini->env, "PWD"))
		add_to_env(oldpwd, mini->env);
	else if (already_exist_in_env(mini->env, "PWD") == 0 && \
		already_exist_in_env(mini->env, oldpwd) == 0)
		add_to_env("OLDPWD=", mini->env);
	if (already_exist_in_env(mini->copy_env, oldpwd) == 0 && \
		already_exist_in_env(mini->copy_env, "PWD"))
		add_to_env(oldpwd, mini->copy_env);
	else if (already_exist_in_env(mini->copy_env, "PWD") == 0 && \
		already_exist_in_env(mini->copy_env, oldpwd) == 0)
		add_to_env("OLDPWD=", mini->copy_env);
	ft_memdel(oldpwd);
	return (SUCCESS);
}

void	updat_pwd(t_mini *mini)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return ;
	already_exist_in_env(mini->env, pwd);
	already_exist_in_env(mini->copy_env, pwd);
	ft_memdel(pwd);
}

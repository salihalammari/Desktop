/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:27:30 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 22:27:32 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	change_directory(int option, t_env *env, t_mini *mini)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		env_path = get_path_from_env(env, "HOME", 4, 0);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", STDERR);
		if (!env_path)
			return (ERROR);
	}
	else if (option == 1)
	{
		env_path = get_path_from_env(env, "OLDPWD", 6, 1);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
		if (!env_path)
			return (ERROR);
	}
	update_oldpwd(mini);
	ret = chdir(env_path);
	updat_pwd(mini);
	ft_memdel(env_path);
	return (ret);
}

void	ft_print_msg(void)
{
	if (!getcwd(NULL, 0))
		printf("cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory\n");
}

int	ft_cd(char **args, t_mini *mini)
{
	int	cd_ret;
	int	flag;

	if (!args[1] || (!ft_strncmp(args[1], "~", 1) && ft_strlen(args[1]) == 1))
		return (change_directory(0, mini->env, mini));
	flag = 0;
	if (ft_strcmp(args[1], "-") == 0)
	{
		cd_ret = change_directory(1, mini->env, mini);
		flag = 1;
	}
	if (ft_strcmp(args[1], ".") == 0)
		ft_print_msg();
	else
	{
		if (!flag)
			update_oldpwd(mini);
		cd_ret = chdir(args[1]);
		updat_pwd(mini);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0 && ft_strcmp(args[1], "-"))
			print_cd_error(args);
	}
	return (cd_ret);
}

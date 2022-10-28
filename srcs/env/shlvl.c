/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:30:04 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/18 13:31:02 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	invalid_shlvl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	shlvl_to_int(const char *str)
{
	int	sign;
	int	num;
	int	i;

	i = 0;
	sign = 1;
	num = 0;
	ft_skip_spacenl(str, &i);
	if (invalid_shlvl(str))
		return (0);
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num * sign);
}

void	increment_shlvl(t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*shlvl;
	char	*shlvl_value;
	int		shell_level;

	shlvl_value = get_env_value("SHLVL", env);
	if (ft_strcmp(shlvl_value, "") == 0)
		return ;
	shell_level = shlvl_to_int(shlvl_value) + 1;
	ft_memdel(shlvl_value);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp("SHLVL", env_name) == 0)
		{
			ft_memdel(env->value);
			shlvl = ft_itoa(shell_level);
			env->value = ft_strjoin("SHLVL=", shlvl);
			if (!env->value)
				return ;
			ft_memdel(shlvl);
			return ;
		}
		env = env->next;
	}
}

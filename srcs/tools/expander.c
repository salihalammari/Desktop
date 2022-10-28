/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:23:01 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/19 19:33:24 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	rtn_size(int ret)
{
	char	*tmp;
	int		rtn_len;

	tmp = ft_itoa(ret);
	rtn_len = ft_strlen(tmp);
	ft_memdel(tmp);
	return (rtn_len);
}

int	get_expanded_value_len(const char *arg, int pos, t_env *env, int ret)
{
	char	*var_value;
	char	var_name[BUFF_SIZE];
	int		i;

	i = 0;
	if (arg[pos] == '?')
		return (rtn_size(ret));
	if (ft_isdigit(arg[pos]))
		return (0);
	while (arg[pos] && is_valid_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	i = ft_strlen(var_value);
	ft_memdel(var_value);
	return (i);
}

int	cmds_len_for_alloc(const char *arg, t_env *env, int ret)
{
	int	size;
	int	i;

	size = 0;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == EXPANDER)
		{
			i++;
			if ((arg[i] == '\0' || ft_isalnum(arg[i]) == 0) && arg[i] != '?')
				size++;
			else
				size += get_expanded_value_len(arg, i, env, ret);
			if (ft_isdigit(arg[i]) == 0)
			{
				while (arg[i + 1] && is_valid_env_char(arg[i]))
					i++;
			}
			else
				size--;
		}
		size++;
	}
	return (size);
}

char	*get_env_var_value(const char *arg, int pos, t_env *env, int ret)
{
	char	*var_value;
	char	var_name[BUFF_SIZE];
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);
	}
	if (ft_isdigit(arg[pos]))
		return (NULL);
	while (arg[pos] && is_valid_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	return (var_value);
}

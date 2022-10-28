/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:22:09 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 22:28:03 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	varlcopy(char *new_arg, const char *env_value, int pos)
{
	int	i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

static	void	var_inserting(t_expander *ex, char *arg, t_env *env, int ret)
{
	char	*env_value;

	env_value = get_env_var_value(arg, ex->j, env, ret);
	if (env_value)
		ex->i += varlcopy(ex->new_arg, env_value, ex->i);
	ft_memdel(env_value);
	if (arg[ex->j] == '?')
		ex->j++;
	if (ft_isdigit(arg[ex->j]) == 0 && arg[ex->j - 1] != '?')
	{
		while (is_valid_env_char(arg[ex->j]) == 1)
			ex->j++;
	}
	else
	{
		if (arg[ex->j - 1] != '?')
			ex->j++;
	}
}

static int	init_ex(t_expander *ex)
{
	if (!ex->new_arg)
		return (ERROR);
	ex->i = 0;
	ex->j = 0;
	return (SUCCESS);
}

char	*expander(char *arg, t_mini *mini)
{
	t_expander	ex;
	int			new_arg_len;

	if (!arg)
		return (NULL);
	new_arg_len = cmds_len_for_alloc(arg, mini->env, mini->ret);
	ex.new_arg = malloc(BUFF_SIZE);
	if (init_ex(&ex))
		return (NULL);
	while (ex.i < new_arg_len && arg[ex.j])
	{
		while (arg[ex.j] == EXPANDER)
		{
			ex.j++;
			if ((arg[ex.j] == '\0' || ft_isalnum(arg[ex.j]) == 0) \
			&& arg[ex.j] != '?')
				ex.new_arg[ex.i++] = '$';
			else if (ft_counter(arg, '$') % 2 != 0)
				var_inserting(&ex, arg, mini->env, mini->ret);
		}
		ex.new_arg[ex.i++] = arg[ex.j++];
	}
	ex.new_arg[ex.i] = '\0';
	return (ex.new_arg);
}

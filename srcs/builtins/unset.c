/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 08:22:53 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 22:21:18 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error(char **a)
{
	int	i;

	i = 1;
	while (a[i])
	{
		if (ft_isdigit(a[i][0]))
		{
			ft_putstr_fd("unset: not a valid identifier: ", STDERR);
			ft_putendl_fd(a[i], STDERR);
		}
		else if (!ft_charscmp(a[i], "+-*/=()~`!@#$^"))
		{
			ft_putstr_fd("unset: not a valid identifier: ", STDERR);
			ft_putendl_fd(a[i], STDERR);
		}
		i++;
	}
}

size_t	env_name_size(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

void	unset_middle(t_mini *mini, char *a, int flag)
{
	t_env	*current;
	t_env	*temp;

	if (!mini->copy_env || !mini->env)
		return ;
	if (flag == 0)
		current = mini->copy_env;
	else
		current = mini->env;
	while (current->next != NULL)
	{
		if (!ft_strncmp(a, current->next->value, ft_strlen(a)) && \
			ft_strlen(a) == env_name_size(current->next->value))
		{
			temp = current->next;
			current->next = current->next->next;
			ft_memdel(temp->value);
			ft_memdel(temp);
			break ;
		}
		else
			current = current->next;
	}
}

int	secret_unset(char **a, t_mini *mini)
{
	t_env	*temp;
	int		i;

	if ((!mini->copy_env || !mini->env) && !mini->no_env)
		return (-1);
	ft_error(a);
	i = 1;
	while (a[i])
	{
		if (!mini->copy_env)
			break ;
		if (!ft_strncmp(a[i], mini->copy_env->value, ft_strlen(a[i])) && \
				ft_strlen(a[i]) == env_name_size(mini->copy_env->value))
		{
			temp = mini->copy_env;
			mini->copy_env = mini->copy_env->next;
			ft_memdel(temp->value);
			ft_memdel(temp);
		}
		else
			unset_middle(mini, a[i], 0);
		i++;
	}
	return (0);
}

int	ft_unset(char **a, t_mini *mini)
{
	t_env	*temp;
	int		i;

	if (secret_unset(a, mini) == -1)
		return (0);
	i = 1;
	while (a[i])
	{
		if (!mini->env)
			break ;
		if (!ft_strncmp(a[i], mini->env->value, ft_strlen(a[i])) && \
				ft_strlen(a[i]) == env_name_size(mini->env->value))
		{
			temp = mini->env;
			mini->env = mini->env->next;
			ft_memdel(temp->value);
			ft_memdel(temp);
			i = 1;
			continue ;
		}
		else
			unset_middle(mini, a[i], 1);
		i++;
	}
	return (0);
}

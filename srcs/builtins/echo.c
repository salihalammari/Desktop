/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:29:27 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 22:27:34 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	how_many_args(char **args)
{
	int	size;

	if (!args || !*args)
		return (0);
	size = 0;
	while (args[size])
		size++;
	return (size);
}

static int	write_echo_args(char **args)
{
	int	i;
	int	n_option;

	i = 1;
	n_option = 0;
	while (args[i] && (ft_strcmp(args[i], "-n") == 0 \
		|| ft_strcmpall(args[i], 1, 'n') == 0))
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	return (n_option);
}

int	ft_echo(char **args)
{
	int	n_option;

	n_option = 0;
	if (!args || !*args)
		return (1);
	if (how_many_args(args) > 1)
		n_option = write_echo_args(args);
	if (n_option == 0)
		write(1, "\n", 1);
	return (SUCCESS);
}

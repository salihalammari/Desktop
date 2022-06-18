/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_off_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:42:36 by slammari          #+#    #+#             */
/*   Updated: 2022/06/18 15:42:37 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_case(char *list)
{
	int	i;
	int	j;

	i = 0;
	if (list[0] != '\'' && list[0] != '\"')
	{
		while (list[i])
		{
			if (list[i] == '\'' || list[i] == '\"')
			{
				j = i;
				while (list[j + 1])
				{
					list[j] = list[j + 1];
					j++;
				}
				list[j] = '\0';
			}
			i++;
		}
	}
}

static void	second_case(char *list)
{
	int		i;
	int		j;
	char	a;

	i = 0;
	if (list[0] == '\'')
	{
		while (list[i])
		{
			if (list[i] == '\'')
			{
				j = i;
				while (list[j + 1])
				{
					a = list[j];
					list[j] = list[j + 1];
					list[j + 1] = a;
					j++;
				}
				list[j] = '\0';
			}
			i++;
		}
	}
}

static void	third_case(char *list)
{
	int		i;
	int		j;
	char	a;

	if (list[0] == '\"')
	{
		i = 0;
		while (list[i])
		{
			if (list[i] == '\"')
			{
				j = i;
				while (list[j + 1])
				{
					a = list[j];
					list[j] = list[j + 1];
					list[j + 1] = a;
					j++;
				}
				list[j] = '\0';
			}
			i++;
		}
	}
}

void	take_off_quotes(char *list)
{
	int	i;

	if (!list)
		return ;
	first_case(list);
	second_case(list);
	third_case(list);
	i = 0;
	while (list[i])
	{
		if ((list[i] == '\'' || list[i] == '\"') && list[i + 1] == '\0')
		{
			list[i] = '\0';
			break ;
		}
		i++;
	}
}

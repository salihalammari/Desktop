/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:43:04 by slammari          #+#    #+#             */
/*   Updated: 2022/06/18 15:43:05 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_check_split(char **split)
{
	if (!split)
	{
		printf("minishell: malloc error\n");
		free(split);
		exit(1);
	}
}

void	malloc_check_strdup(char *str)
{
	if (!str)
	{
		printf("minishell: malloc error\n");
		free(str);
		exit(1);
	}
}

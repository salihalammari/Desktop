/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:42:23 by slammari          #+#    #+#             */
/*   Updated: 2022/06/18 15:42:24 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_no_cmd(t_struct *mini, char **split, int j)
{
	if (((!split[1] && split[0][0] == '<' && split[0][1] == '<') \
				|| (split[0][2] == '\0' && split[0][1] == '<' \
					&& split[1] && !split[2]) || (!mini->commands[j + 1] \
						&& !mini->error_name_file)) && j < 1)
	{
		free_char_array(&split);
		return (0);
	}
	return (1);
}

void	fill_extend(char **extend, char *value)
{
	*extend = ft_strdup(value);
	malloc_check_strdup(*extend);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:43:44 by slammari          #+#    #+#             */
/*   Updated: 2022/06/18 15:43:45 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_expander(char **copy, char **split, int *i)
{
	*copy = ft_strdup(split[*i]);
	malloc_check_strdup(*copy);
	free(split[*i]);
	split[*i] = ft_strjoin("$", *copy);
	free(*copy);
	*copy = ft_strdup(split[*i]);
	malloc_check_strdup(*copy);
}

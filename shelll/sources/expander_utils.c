/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:43:32 by slammari          #+#    #+#             */
/*   Updated: 2022/06/17 22:45:01 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_expander(char **copy, char **split, int *i)
{
    *copy = ft_strdup(split[*i]);
    malloc_check_strdup(*copy);
    free(split[*i]);
    split[*i] = ft_strjoin("$", *copy);
    free(*copy);
    *copy = ft_strdup(split[*i]);
    malloc_check_strdup(*copy);
}

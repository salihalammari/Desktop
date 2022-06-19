/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:46:03 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:42:12 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	equal_in_echo(t_struct *mini, char **split, int *i)
{
	char	*copy;

	if (find_char(split[*i], '=') != (int)ft_strlen(split[*i]))
	{
		copy = ft_strdup(split[*i]);
		free(split[*i]);
		split[*i] = ft_substr(copy, 0, find_char(copy, '='));
		mini->chyata = ft_strdup(&copy[ft_strlen(split[*i])]);
		take_off_quotes(mini->chyata);
		free(copy);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:37:51 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 16:39:20 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	stop_reading(t_mini *mini, t_token *tmp, char *file_name)
{
	mini->heredoc = 1;
	free (tmp->str);
	free (tmp->next->str);
	tmp->str = ft_strdup("<");
	if (!tmp->str)
		return (ERROR);
	tmp->next->str = ft_strdup(file_name);
	if (!tmp->next->str)
		return (ERROR);
	return (SUCCESS);
}

void	unlinking_heredoc_files(t_mini *mini)
{
	t_list	*copy;

	if (mini->heredoc)
	{
		while (mini->file)
		{
			copy = mini->file;
			unlink(mini->file->content);
			mini->file = mini->file->next;
			free(copy->content);
			free(copy);
		}
	}
}

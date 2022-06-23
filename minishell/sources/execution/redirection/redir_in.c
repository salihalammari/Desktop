/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <sghajdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:04:56 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/23 19:20:15 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_in_expander(t_struct *mini, char ***file)
{
	char	*copy;

	copy = ft_strdup(*file[0]);
	malloc_check_strdup(copy);
	free(*file[0]);
	*file[0] = expander(mini, copy);
	free(copy);
}

int	simple_redir_in(t_struct *mini, char ***file, int j)
{
	*file = ft_split(&mini->commands[j][1], ' ');
	malloc_check_split(*file);
	if (!*file[0])
	{
		printf(ERROR_REDI);
		free_char_array(file);
		g_ret_number = 258;
		return (0);
	}
	if (*file[0][0] == D_QUOTE || *file[0][0] == QUOTE)
		mini->redir_flag = 1;
	take_off_quotes(*file[0]);
	if (*file[0][0] == '$' && mini->redir_flag == 0)
		redir_in_expander(mini, file);
	if ((access(*file[0], F_OK) == -1 || access(*file[0], R_OK) == -1) \
			&& mini->error_name_file == NULL)
	{
		mini->error_name_file = ft_strdup(*file[0]);
		malloc_check_strdup(mini->error_name_file);
	}
	else
		mini->in_fd = open(*file[0], O_RDONLY, 0644);
	return (1);
}

int	exec_rediraction(t_struct *mini, char ***file, int j)
{
	if (mini->commands[j][1] == '<')
	{
		*file = double_redir(mini, *file, j);
		mini->heredoc = 1;
		if (!*file)
			return (0);
	}
	else if (mini->commands[j][0] == '<' && mini->heredoc == 0)
	{
		if (!simple_redir_in(mini, file, j))
			return (0);
	}
	return (1);
}
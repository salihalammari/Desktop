/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:09:05 by sghajdao          #+#    #+#             */
/*   Updated: 2022/10/21 22:27:53 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		g_sig.sigint = 1;
		g_sig.exit_status = 1;
		write(2, "\n", 1);
	}
}

static void	add_t_at_end(char **file)
{
	char	*copy;

	while (!access(*file, F_OK))
	{
		copy = ft_strdup(*file);
		if (!copy)
			return ;
		free (*file);
		*file = ft_strjoin(copy, "t");
		if (!*file)
			return ;
		free(copy);
	}
}

int	if_empty_line(t_mini *mini, char *line)
{
	if (!line)
	{
		mini->ret = 1;
		mini->no_exec = 1;
		return (1);
	}
	return (0);
}

static	void	read_until_delimiter(t_mini *mini, t_token *tmp, \
	char *file_name, int fd)
{
	char	*line;
	char	*copy;

	while (1)
	{
		line = readline("> ");
		if (if_empty_line(mini, line))
			break ;
		if (!ft_strcmp(line, tmp->next->str))
		{
			free(line);
			if (stop_reading(mini, tmp, file_name))
				return ;
			else
				break ;
		}
		copy = ft_strdup(line);
		if (!copy)
			return ;
		free(line);
		line = expander(copy, mini);
		free(copy);
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	ft_heredoc(t_mini *mini, t_token **lst)
{
	char	*file_name;
	t_token	*tmp;
	int		fd;

	tmp = *lst;
	while (tmp)
	{
		if (tmp && tmp->type == 5)
		{
			if (!check_syntax(mini, tmp))
				return ;
			file_name = ft_strdup("/tmp/.txt");
			if (!file_name)
				return ;
			add_t_at_end(&file_name);
			fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			ft_lstadd_back(&mini->file, ft_lstnew(file_name));
			mini->heredoc = 1;
			signal(SIGINT, handler);
			read_until_delimiter(mini, tmp, file_name, fd);
			free(file_name);
			close(fd);
		}
		tmp = tmp->next;
	}
}

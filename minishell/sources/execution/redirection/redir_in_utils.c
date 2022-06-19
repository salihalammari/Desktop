/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:34:36 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:44:00 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	there_is_pipe(t_struct *mini, char **aux, char ***file)
{
	if (mini->split.n_comand == 1 || (*aux[0] == '|'
			&& ft_strlen(*aux) == 1))
	{
		free(mini->line);
		mini->line = NULL;
		mini->line = new_comman(1, *file);
		free_char_array(file);
	}
}

int	redirect_in(t_struct *mini, int j, char *aux)
{
	char	**file;
	char	**split;

	if (mini->commands[j][0] == '<')
	{
		file = NULL;
		if (!exec_rediraction(mini, &file, j))
		{
			free_char_array(&file);
			return (0);
		}
		aux = ft_strtrim(mini->line, " ");
		there_is_pipe(mini, &aux, &file);
		free(aux);
		mini->last_redir = 0;
		free_char_array(&file);
		split = ft_split(mini->commands[j], ' ');
		malloc_check_split(split);
		if (!if_no_cmd(mini, split, j))
			return (0);
		free_char_array(&split);
	}
	return (1);
}

char	**double_redir(t_struct *mini, char **file, int j)
{
	int	old_stdin;

	if (mini->commands[j + 1])
		file = ft_split(&mini->commands[j + 1][1], ' ');
	else
		file = ft_split(&mini->commands[j][2], ' ');
	malloc_check_split(file);
	if (!file[0])
	{
		free_char_array(&file);
		printf(ERROR_REDI);
		g_ret_number = 258;
		return (NULL);
	}
	if (file[0][0] == D_QUOTE || file[0][0] == QUOTE)
		mini->redir_flag = 1;
	take_off_quotes(file[0]);
	old_stdin = dup(STDIN_FILENO);
	read_until (mini, file[0]);
	mini->in_fd = dup(0);
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	mini->is_append++;
	return (file);
}

void	read_until(t_struct *mini, char *end)
{
	char	*line;
	int		fd[2];

	line = ft_strdup("");
	malloc_check_strdup(line);
	pipe(fd);
	while (1)
	{
		free(line);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, end, ft_strlen(end)) == 0 \
				&& line[ft_strlen(end)] == '\0')
			break ;
		if (line[0] == '$' && mini->redir_flag == 0)
			redir_expander(mini, &line);
		ft_putendl_fd(line, fd[1]);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	free(line);
}

char	*new_comman(int i, char **str)
{
	char	*aux;
	char	*copy;

	aux = ft_strdup("");
	malloc_check_strdup(aux);
	while (str[i] != NULL)
	{
		if (ft_strlen(aux) > 0)
		{
			copy = ft_strdup(aux);
			malloc_check_strdup(copy);
			free(aux);
			aux = ft_strjoin(copy, " ");
			free(copy);
		}
		copy = ft_strdup(aux);
		malloc_check_strdup(copy);
		free(aux);
		aux = ft_strjoin(copy, str[i]);
		free(copy);
		i++;
	}
	return (aux);
}

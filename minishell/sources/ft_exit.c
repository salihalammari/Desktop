
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:02:45 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:02:47 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	all_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_struct *mini)
{
	int	ex;

	printf("exit\n");
	if (mini->tokens[1] && !mini->tokens[2] && all_is_digit(mini->tokens[1]) == 1)
	{
		free_char_array2(mini->commands);
		if (*mini->env.env)
		{
			free_char_array2(mini->env.content);
			free_char_array2(mini->env.key);
		}
		if (mini->path)
			free_char_array(mini->path);
		free(mini->home);
		close(mini->in_fd);
		close(mini->out_fd);
		ex = ft_atoi(mini->tokens[1]);
		free_char_array(mini->tokens);
		free(mini->line_read);
		free_char_array(mini->sorted.env);
		free_char_array(mini->sorted.key);
		free_char_array(mini->sorted.content);
		exit(ex);
	}
	else if (mini->tokens[1] && mini->tokens[2])
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	else if (mini->tokens[1] && !mini->tokens[2] && all_is_digit(mini->tokens[1]) == 0)
	{
		printf("bash: exit: %s: numeric argument required\n", mini->tokens[1]);
		return ;
	}
	free_char_array2(mini->commands);
	if (*mini->env.env)
	{
		free_char_array2(mini->env.content);
		free_char_array2(mini->env.key);
	}
	if (mini->env_flag == 0)
		free_char_array(mini->path);
	if (there_is_home(mini) == true)
		free(mini->home);
	free(mini->line_read);
	close(mini->in_fd);
	close(mini->out_fd);
	free_char_array(mini->tokens);
	free_char_array(mini->sorted.env);
	free_char_array(mini->sorted.key);
	free_char_array(mini->sorted.content);
	exit(0);
}

void	free_line(char *line_read)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
}

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_char_array2(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
}

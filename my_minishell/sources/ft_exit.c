
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
	printf("exit\n");
	if (mini->tokens[1] && !mini->tokens[2] && all_is_digit(mini->tokens[1]) == 1)
		exit_with_arg(mini);
	else if (mini->tokens[1] && mini->tokens[2] && all_is_digit(mini->tokens[1]))
	{
		final_free(mini);
		printf("minishell: exit: too many arguments\n");
		g_ret_number = 1;
		return ;
	}
	else if (mini->tokens[1] && !all_is_digit(mini->tokens[1]))
	{
		final_free(mini);
		printf("bash: exit: %s: numeric argument required\n", mini->tokens[1]);
		exit(255);
	}
	final_free(mini);
	if (g_ret_number == 258)
		exit(2);
	exit(g_ret_number);
}

void	free_line(char *line_read)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
}

void	free_char_array(char ***array)
{
	int	i;

	if (!array || !(*array))
		return ;
	i = 0;
	while ((*array)[i] != NULL)
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}

void	free_char_array2(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
}

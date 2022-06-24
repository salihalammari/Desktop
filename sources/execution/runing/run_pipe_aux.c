/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:05:26 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/23 20:48:04 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	file_descriptor_handler(int in, int out)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		dup2(out, 1);
		close(out);
	}
	return (0);
}

static void	take_off_pipe(t_struct *mini, int i)
{
	char	*copy;

	if (mini->tokens[i - 1][0] == '|' && mini->tokens[i - 1][1])
	{
		copy = ft_strdup(mini->tokens[i - 1]);
		malloc_check_strdup(copy);
		free(mini->tokens[i - 1]);
		mini->tokens[i - 1] = ft_strdup(&copy[1]);
		malloc_check_strdup(mini->tokens[i - 1]);
		free(copy);
	}
}

void	spaces_in_pipe(t_struct *mini, int i, char *command)
{
	char	*aux;
	char	*copy;

	if (ft_strlen(mini->token.to_print) && mini->tokens[i]
		&& (mini->tokens[i][0] == QUOTE || mini->tokens[i][0] == D_QUOTE)
		&& ft_strncmp(mini->tokens[i - 1], "sed", 3))
	{
		aux = ft_strtrim(mini->token.to_print, D_QUOTE_S);
		free_char_array2(&mini->tokens[i + 1]);
	}
	else
		aux = ft_strtrim(mini->tokens[i], D_QUOTE_S);
	free(mini->tokens[i]);
	mini->tokens[i] = aux;
	copy = ft_strdup(command);
	malloc_check_strdup(copy);
	free(command);
	command = ft_strjoin(copy, mini->tokens[i - 1]);
	free(copy);
	take_off_pipe(mini, i);
	g_ret_number = execve(command, &mini->tokens[i - 1], mini->env.env);
	free(command);
}

static void	put_error(char *cmd, int out)
{
	char	*mes;
	char	*copy;

	mes = ft_strjoin("minishell: ", cmd);
	copy = ft_strdup(mes);
	malloc_check_strdup(copy);
	free(mes);
	mes = ft_strjoin(copy, ": command not found");
	free(copy);
	ft_putendl_fd(mes, out);
	free(mes);
}

void	execve_error(t_struct *mini)
{
	g_ret_number = 127;
	if (mini->tokens[0][0] != '|')
		put_error(mini->tokens[0], mini->split.sd_out);
	else if (mini->tokens[1])
		put_error(mini->tokens[1], mini->split.sd_out);
	close(mini->split.sd_out);
}

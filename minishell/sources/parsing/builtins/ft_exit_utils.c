/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:46:28 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:41:24 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_with_arg(t_struct *mini)
{
	int	ex;

	free_char_array2(mini->commands);
	if (*mini->env.env)
	{
		free_char_array2(mini->env.content);
		free_char_array2(mini->env.key);
	}
	if (mini->path)
		free_char_array(&mini->path);
	free(mini->home);
	close(mini->in_fd);
	close(mini->out_fd);
	ex = ft_atoi(mini->tokens[1]);
	if (ex < 0)
		ex += 256;
	free_char_array(&mini->tokens);
	free(mini->line_read);
	free_char_array(&mini->sorted.env);
	free_char_array(&mini->sorted.key);
	free_char_array(&mini->sorted.content);
	exit(ex);
}

void	final_free(t_struct *mini)
{
	free_char_array2(mini->commands);
	if (*mini->env.env)
	{
		free_char_array2(mini->env.content);
		free_char_array2(mini->env.key);
	}
	if (mini->env_flag == 0)
		free_char_array(&mini->path);
	if (there_is_home(mini) == true)
		free(mini->home);
	free(mini->line_read);
	close(mini->in_fd);
	close(mini->out_fd);
	free_char_array(&mini->tokens);
	free_char_array(&mini->sorted.env);
	free_char_array(&mini->sorted.key);
	free_char_array(&mini->sorted.content);
	free(mini->line);
	free(mini->token.to_print);
}

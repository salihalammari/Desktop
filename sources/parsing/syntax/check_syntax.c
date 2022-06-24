/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:45:32 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:43:11 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_char(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

static void	error_message(char **cmd, char ***split, int flag)
{
	printf("minishell: %s: command not found\n", *cmd);
	g_ret_number = 1;
	free(*cmd);
	if (flag == 1)
		free_char_array(split);
}

int	if_find_pipe(char *in, char **cmd)
{
	if ((find_char(in, '|') != (int)ft_strlen(in)) && \
			(count_char(&in[find_char(in, '|')], '\"') % 2 != 0))
	{
		printf("RGSDRGDTHYFJ\n");
		error_message(cmd, NULL, 0);
		return (0);
	}
	return (1);
}

int	check_pipe_between_quotes(char *in)
{
	char	*cmd;
	char	**split;

	if (in[0] == D_QUOTE || in[0] == QUOTE)
	{
		cmd = ft_strdup(in);
		take_off_quotes(cmd);
		if ((find_char(in, '|') != (int)ft_strlen(in)) && \
				(count_char(&in[find_char(in, '|')], '\"') % 2 != 0))
		{
			error_message(&cmd, &split, 0);
			return (0);
		}
		split = ft_split(cmd, ' ');
		malloc_check_split(split);
		if (split[0] && split[1] && (int)ft_strlen(split[1]) > 1 \
				&& (count_char(in, QUOTE) % 2 || count_char(in, D_QUOTE) % 2))
		{
			error_message(&cmd, &split, 1);
			return (0);
		}
		free_char_array(&split);
		free(cmd);
	}
	return (1);
}

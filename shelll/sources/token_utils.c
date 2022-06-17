/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:06:40 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/17 19:19:51 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_home_sign(t_struct *mini, t_token *tk)
{
	char	*extend;
	char	*end;

	tk->new = ft_substr(mini->line, tk->init, tk->len - 1);
	end = ft_strdup(tk->end);
	malloc_check_strdup(end);
	free(tk->end);
	tk->end = ft_strjoin(end, tk->new);
	free(tk->new);
	free(end);
	extend = ft_strdup(mini->home);
	malloc_check_strdup(extend);
	end = ft_strdup(tk->end);
	malloc_check_strdup(end);
	free(tk->end);
	tk->end = ft_strjoin(end, extend);
	free(end);
	free(extend);
	tk->i++;
	tk->len = 1;
	tk->init = tk->i;
}

void	get_key(t_token *tk, t_struct *mini, char **n_env)
{
	char	*copy;
	int		i;

	if (find_char(*n_env, '$') != (int)ft_strlen(*n_env))
	{
		copy = ft_strdup(*n_env);
		malloc_check_strdup(copy);
		free(*n_env);
		*n_env = ft_substr(copy, tk->init, find_char(*n_env, '$'));
		free(copy);
	}
	if (!find_env(mini, *n_env) && *n_env[0] != '?')
	{
		copy = ft_strdup(*n_env);
		i = 0;
		while (copy[i] != '\0')
		{
			copy[i] = ' ';
			i++;
		}
		free(*n_env);
		*n_env = ft_strdup(copy);
		free(copy);
	}
}

void	get_dollar_sign(t_struct *mini, t_token *tk)
{
	char	*extend;
	char	*n_env;
	char	*end;

	get_extend(mini, tk, &n_env, &end);
	if (mini->line[tk->i + 1] != '?' && find_env(mini, n_env))
	{
		extend = ft_strdup(find_env(mini, n_env));
		malloc_check_strdup(extend);
	}
	else if (mini->line[tk->i] == '$' && (mini->line[tk->i + 1] == '\0' || mini->line[tk->i + 1] == ' '))
	{
		extend = ft_strdup("$");
		malloc_check_strdup(extend);
	}
	else if (mini->line[tk->i + 1] != '?' && !find_env(mini, n_env))
	{
		extend = ft_strdup(n_env);
		malloc_check_strdup(extend);
	}
	else if (mini->line[tk->i + 1] == '?')
		extend = ft_itoa(g_ret_number);
	else
		extend = NULL;
	extend_finish(tk, &n_env, &extend, &end);
}

t_token	*init_tk(void)
{
	t_token	*tk;

	tk = (t_token *)malloc(sizeof(t_token));
	tk->end = NULL;
	tk->new = NULL;
	tk->to_exec = NULL;
	tk->to_print = NULL;
	tk->quote = '\0';
	tk->i = 0;
	tk->init = 0;
	tk->len = 1;
	tk->posic = 0;
	return (tk);
}

void	free_tk(t_token *tk)
{
	if (tk->end != NULL)
	{
		free(tk->end);
		tk->end = NULL;
	}
	if (tk->new != NULL)
	{
		free(tk->new);
		tk->new = NULL;
	}
	if (tk->to_exec != NULL)
	{
		free(tk->to_exec);
		tk->to_exec = NULL;
	}
	if (tk->to_print != NULL)
	{
		free(tk->to_print);
		tk->to_print = NULL;
	}
	free(tk);
}


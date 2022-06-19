/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:47:45 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:43:26 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	extend_assist(t_token *tk, char **end, char **extend)
{
	*end = ft_strdup(tk->end);
	malloc_check_strdup(*end);
	free(tk->end);
	tk->end = ft_strjoin(*end, *extend);
	free(*end);
}

void	get_extend(t_struct *mini, t_token *tk, char **n_env, char **end)
{
	tk->new = ft_substr(mini->line, tk->init, tk->len - 1);
	*end = ft_strdup(tk->end);
	malloc_check_strdup(*end);
	free(tk->end);
	tk->end = ft_strjoin(*end, tk->new);
	free (tk->new);
	free(*end);
	tk->posic = tokenizer_find_char(&mini->line[tk->i + 1], ' ');
	*n_env = ft_substr(mini->line, tk->i + 1, tk->posic);
	if (mini->line[tk->i] == '$')
		get_key(tk, mini, n_env);
}

void	extend_finish(t_token *tk, char **n_env, char **extend, char **end)
{
	if (extend)
	{
		*end = ft_strdup(tk->end);
		malloc_check_strdup(*end);
		free(tk->end);
		tk->end = ft_strjoin(*end, *extend);
		free(*end);
	}
	free(*extend);
	tk->i += ft_strlen(*n_env) + 1;
	free (*n_env);
	tk->len = 1;
	tk->init = tk->i;
}

void	finish_tokenizer(t_struct *mini, t_token *tk)
{
	char	*end;

	tk->new = ft_substr(mini->line, tk->init, tk->len);
	end = ft_strdup(tk->end);
	malloc_check_strdup(end);
	free(tk->end);
	tk->end = ft_strjoin(end, tk->new);
	free(end);
	tk->posic = tokenizer_find_char(tk->end, ' ');
	free(mini->token.to_print);
	mini->token.to_print = NULL;
	mini->token.to_print = ft_strtrim(&(tk->end)[tk->posic], " ");
	mini->token.to_exec = ft_substr(tk->end, tk->i + 1, tk->posic);
	tokenizer_clean_quotes(mini, mini->token.to_print, 0, 0);
	mini->tokens = ft_split(tk->end, ' ');
	malloc_check_split(mini->tokens);
	free_tk(tk);
	free (mini->line);
	mini->line = NULL;
}

void	token_assist(t_struct *mini, char *in, int i, int c)
{
	char	*aux;

	aux = ft_strtrim(in, " ");
	mini->has_flag = false;
	clean_option(mini, in, i);
	while (in[i] == ' ')
		i++;
	while (in[i])
	{
		c = fixing_for_norminette(mini, in[i], aux, c);
		i++;
	}
	aux[c] = '\0';
	free(mini->token.to_print);
	mini->token.to_print = NULL;
	mini->token.to_print = ft_strdup(aux);
	malloc_check_strdup(mini->token.to_print);
	free(aux);
}

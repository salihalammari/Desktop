/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:06:40 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:06:42 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_home_sign(t_struct *mini, t_token *tk)
{
	char	*extend;
	char	*end;

	tk->new = ft_substr(mini->line, tk->init, tk->len - 1);
	end = ft_strdup(tk->end);
	free(tk->end);
	tk->end = ft_strjoin(end, tk->new);
	free(tk->new);
	free(end);
	extend = ft_strdup(mini->home);
	end = ft_strdup(tk->end);
	free(tk->end);
	tk->end = ft_strjoin(end, extend);
	free(end);
	free(extend);
	tk->i++;
	tk->len = 1;
	tk->init = tk->i;
}

void	get_dollar_sign(t_struct *mini, t_token *tk)
{
	char	*extend;
	char	*n_env;
	char	*end;
	char	*copy;
	int		i;

	tk->new = ft_substr(mini->line, tk->init, tk->len - 1);
	end = ft_strdup(tk->end);
	free(tk->end);
	tk->end = ft_strjoin(end, tk->new);
	free (tk->new);
	free(end);
	tk->posic = tokenizer_find_char(&mini->line[tk->i + 1], ' ');
	n_env = ft_substr(mini->line, tk->i + 1, tk->posic);
	
	if (mini->line[tk->i] == '$') /*************echo $AEFAEFAEF******************************/
	{
		if (find_char(n_env, '$') != (int)ft_strlen(n_env))
		{
			copy = ft_strdup(n_env);
			free(n_env);
			n_env = ft_substr(copy, tk->init, find_char(n_env, '$'));
			free(copy);
		}
		if (!find_env(mini, n_env))
		{
			i = 0;
			while (n_env[i])
			{
				n_env[i] = ' ';
				i++;
			}
		}
	}


	if (mini->line[tk->i + 1] != '?' && find_env(mini, n_env))
		extend = ft_strdup(find_env(mini, n_env));
	else if (mini->line[tk->i] == '$' && (mini->line[tk->i + 1] == '\0' || mini->line[tk->i + 1] == ' '))
		extend = ft_strdup("$");
	else if (mini->line[tk->i + 1] != '?' && !find_env(mini, n_env))
		extend = ft_strdup(n_env);
	else if (mini->line[tk->i + 1] == '?')
		extend = ft_itoa(g_ret_number);
	else
		extend = NULL;
	if (extend)
	{
		end = ft_strdup(tk->end);
		free(tk->end);
		tk->end = ft_strjoin(end, extend);
		free(end);
	}
	free(extend);
	tk->i += ft_strlen(n_env) + 1;
	free (n_env);
	tk->len = 1;
	tk->init = tk->i;
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

void	finish_tokenizer(t_struct *mini, t_token *tk)
{
	char	*end;

	tk->new = ft_substr(mini->line, tk->init, tk->len);
	end = ft_strdup(tk->end);
	free(tk->end);
	tk->end = ft_strjoin(end, tk->new);
	free(end);
	tk->posic = tokenizer_find_char(tk->end, ' ');
	mini->token.to_print = ft_strtrim(&(tk->end)[tk->posic], " ");
	mini->token.to_exec = ft_substr(tk->end, tk->i + 1, tk->posic);
	tokenizer_clean_quotes(mini, mini->token.to_print, 0, 0);
	mini->tokens = ft_split(tk->end, ' ');
	if (!mini->tokens)
	{
		printf("malloc error\n");
		exit(1);
	}
	free_tk(tk);
	free (mini->line);
}

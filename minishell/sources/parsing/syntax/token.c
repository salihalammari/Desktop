/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:06:56 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:43:34 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	tokenizer_find_char(char *string, char needle)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == needle || (string[i] == D_QUOTE \
					&& string[i - 1] == ' ') || (string[i] == QUOTE \
						&& string[i - 1] == ' '))
			return (i);
		if (string[i] == '?')
			return (i + 1);
		i++;
	}
	return (i);
}

int	fixing_for_norminette(t_struct *mini, char c, char *aux, int nbr)
{
	if (mini->token.quote == 0 && (c == QUOTE || c == D_QUOTE))
		mini->token.quote = c;
	else
	{
		if (mini->token.quote == c)
			mini->token.quote = 0;
		else
		{
			aux[nbr] = c;
			nbr++;
		}
	}
	return (nbr);
}

void	clean_option(t_struct *mini, char *in, int i)
{
	char	*copy;

	copy = NULL;
	if (in[i] == '-' && in[i + 1] == 'n' && in[i + 2] == ' ')
	{
		while (in[i] == '-' && in[i + 1] == 'n' && in[i + 2] == ' ')
		{
			mini->has_flag = true;
			i += 3;
		}
		in = ft_memmove(in, in + i, ft_strlen(in));
		free(copy);
	}
	else if (in[i] == '-' && in[i + 1] == 'n' && in[i + 2] == 'n')
	{
		++i;
		while (in[i] == 'n')
			i++;
		if (in[i] == ' ')
		{
			in = ft_memmove(in, in + i, ft_strlen(in));
			mini->has_flag = true;
		}
	}
}

void	tokenizer_clean_quotes(t_struct *mini, char *in, int i, int c)
{
	mini->token.quote = 0;
	if (in[0])
		token_assist(mini, in, i, c);
	else if (!in[0])
	{
		free(mini->token.to_print);
		mini->token.to_print = NULL;
	}
}

void	tokenizer(t_struct *mini)
{
	t_token	*tk;

	tk = init_tk();
	mini->token.quote = 0;
	tk->end = ft_strdup("");
	malloc_check_strdup(tk->end);
	if (mini->line)
	{
		echo_expander(mini);
		while ((int)ft_strlen(mini->line) > tk->i)
		{
			if (mini->token.quote == 0 && (mini->line[tk->i] == QUOTE))
				mini->token.quote = mini->line[tk->i];
			else
				call_dollar_home(mini, tk);
			tk->len++;
			tk->i++;
		}
		finish_tokenizer(mini, tk);
	}
}

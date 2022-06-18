/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 15:42:28 by slammari          #+#    #+#             */
/*   Updated: 2022/06/18 17:50:45 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_dollar_home(t_struct *mini, t_token *tk)
{
	if (mini->token.quote == mini->line[tk->i])
		mini->token.quote = 0;
	if (mini->line[tk->i] == '~' && mini->token.quote == 0)
		get_home_sign(mini, tk);
	else if (mini->line[tk->i] == '$' && mini->token.quote == 0)
		get_dollar_sign(mini, tk);
}

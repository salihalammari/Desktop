#include "minishell.h"

void	split_cmd(t_struct *mini, char *in, int i)
{
	int	j;

	init_split_struct(mini);
	in = clean_spaces(in);
	while (i < (int)ft_strlen(in))
	{
		if (mini->split.q == 0 && (in[i] == D_QUOTE || in[i] == QUOTE))
			mini->split.q = in[i];
		else
		{
			if (mini->split.q == in[i])
				mini->split.q = 0;
			else
				i = count_pipe(mini, in, i);
		}
		mini->split.len++;
		i++;
	}
	if (mini->split.q == 0)
	{
		j = 0;
		while (mini->commands[j])
		{
			take_off_quotes(mini->commands[j]);
			j++;
		}
	}
	if (ft_strlen(in) > 0)
	{
		mini->commands[mini->split.n_comand]
			= ft_substr(in, mini->split.ini, i);
		mini->split.n_comand++;
	}
	free(in);
	mini->commands[mini->split.n_comand] = NULL;
}

void	init_split_struct(t_struct *mini)
{
	mini->split.n_comand = 0;
	mini->split.ini = 0;
	mini->split.len = 0;
	mini->split.qtt_pipe = 0;
	mini->split.q = 0;
	mini->last_redir = 0;
}

char	*clean_spaces(char *in)
{
	char	*aux;

	aux = ft_strtrim(in, " ");
	in = aux;
	return (in);
}

int	count_pipe(t_struct *mini, char *in, int i)
{
	char	**copy;

	if (in[i] == '|' || in[i] == '<' || in[i] == '>')
	{
		if (in[i] == '|' && mini->split.q == 0)
			mini->split.qtt_pipe++;
		if (mini->split.q == 0  && i > 1 && mini->split.len > 0)
		{
			mini->commands[mini->split.n_comand] = ft_substr(in,
					mini->split.ini, mini->split.len);
			mini->split.ini = i;
			mini->split.len = 0;
			mini->split.n_comand++;
			if (in[i] == '>')
				mini->last_redir = 1;
			else
				mini->last_redir = 0;
			if (in[i] == in[i + 1])
			{
				i++;
				mini->split.len = 1;
			}
		}
		if (mini->split.q == 0 && i == 0 && (in[0] == '<' || in[0] == '>'))
		{
			copy = ft_split(in, ' ');
			mini->commands[mini->split.n_comand] = ft_strdup(copy[2]);
			free_char_array(copy);
			mini->split.ini = i;
			mini->split.len = 0;
			mini->split.n_comand++;
		}
	}
	return (i);
}

#include "minishell.h"

/* void	init_split_struct(t_struct *mini)
{
	mini->split.n_comand = 0;
	mini->split.ini = 0;
	mini->split.len = 0;
	mini->split.qtt_pipe = 0;
	mini->split.q = 0;
	mini->last_redir = 0;
	mini->redir_flag = 0;
	mini->name_file = NULL;
	mini->split.permi = 0;
	mini->line = NULL;
	mini->token.to_print = NULL;
	mini->tokens = NULL;
}

char	*clean_spaces(char *in)
{
	char	*aux;

	aux = ft_strtrim(in, " ");
	in = ft_strdup(aux);
	free(aux);
	return (in);
}

void	define_start_cmd(t_struct *mini, char ***split, char *in, int n)
{
	*split = ft_split(in, ' ');
	malloc_check_split(*split);
	if (!*split[1])
	{
		free_char_array(split);
		return ;
	}
	else if (*split[1] && (*split[0][ft_strlen(*split[0]) - 1] == '>' || *split[0][ft_strlen(*split[0]) - 1] == '<') && !*split[2])
	{
		free_char_array(split);
		return ;
	}
	n = 2;
	if ((in[1] == '>' || in[1] == '<') && in[2] == ' ')
		n = 2;
	else if (in[1] != ' ')
		n = 1;
	mini->commands[mini->split.n_comand] = ft_strdup("");
	malloc_check_strdup(mini->commands[mini->split.n_comand]);
}

void	rider_before_cmd(t_struct *mini, char *in, int i)
{
	int		j;
	char	**split;

	j = 0;
	while (in[j] == '<' || in[j] == '>')
		j++;
	while (in[j] == ' ')
		j++;
	while (ft_isalnum(in[j]))
		j++;
	i = j;
	if (find_char(&in[j], '|') != (int)ft_strlen(&in[j]))
	{
		split = ft_split(&in[j], '|');
		malloc_check_split(split);
		while (split[mini->split.n_comand])
		{
			mini->commands[mini->split.n_comand] = ft_strdup(split[mini->split.n_comand]);
			mini->split.n_comand++;
		}
		free_char_array(&split);
	}
	else
		mini->commands[mini->split.n_comand] = ft_strdup(in);
	//mini->split.ini = i;
	//mini->split.len = 0;
	//mini->split.n_comand++;
}

int	count_pipe(t_struct *mini, char *in, int i)
{
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
	}
	return (i);
}
 */
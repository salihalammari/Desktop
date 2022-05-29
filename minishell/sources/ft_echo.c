#include "minishell.h"

void	ft_echo(t_struct *mini)
{
	int		j;
	int		n;

	n = init_echo(mini, 0);
	j = 0;
	if (mini->split.q == 0)
	{
		if (mini->tokens[1])
		{
			print_echo(mini, mini->token.to_print);
			if (!mini->has_flag)
				ft_putstr_fd("\n", mini->out_fd);
		}
		else
			ft_putstr_fd("\n", mini->out_fd);
	}
	else
		printf("minishell: quotes error\n");
}

int	init_echo(t_struct *mini, int n)
{
	if (mini->tokens[0][0] != '|')
		n = 1;
	else
		n = 2;
	return (n);
}

static char	*echo_with_redir(t_struct *mini, char *mini_tokens_i)
{
	int		i;
	char	*aux;
	char	*copy;

	i = 0;
	while (mini->line_read[i])
	{
		if (mini->line_read[i] == '>')
		{
			if (mini->line_read[++i] == ' ')
			{
				while (mini->line_read[++i] != ' ')
				++i;
				aux = ft_strdup(&mini->line_read[i]);
				copy = ft_strdup(mini_tokens_i);
				free(mini_tokens_i);
				mini_tokens_i = ft_strjoin(copy, aux);
				free(aux);
				free(copy);
				return (mini_tokens_i);
			}
		}
		i++;
	}
	return (mini_tokens_i);
}

/* static char	*echo_with_redir(t_struct *mini, char *mini_tokens_i)
{
	char	*aux;
	char	*str;
	int		i;
	char	**split;

	i = 2;
	str = ft_strdup("");
	split = ft_split(mini->commands[1], ' ');
	if (split[0][1] != '\0')
		i = 1;
	while (split[i])
	{
		aux = ft_strdup(str);
		free(str);
		str = ft_strjoin(aux, " ");
		free(aux);
		aux = ft_strdup(str);
		free(str);
		str = ft_strjoin(aux, split[i]);
		free(aux);
		i++;
	}
	free_char_array(split);
	aux = ft_strdup(mini_tokens_i);
	//free(mini_tokens_i);
	mini_tokens_i = ft_strjoin(aux, str);
	free(aux);
	//free(str);
	return (mini_tokens_i);
} */

void	print_echo(t_struct *mini, char *mini_tokens_i)
{
	int	i;
	int	flag;
	char	*copy;

	i = 0;
	flag = 0;
	while (mini->line_read[i])
	{
		if (mini->line_read[i] == '>' && find_char(mini_tokens_i, '>') == (int)ft_strlen(mini_tokens_i))
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		copy = ft_strdup(mini_tokens_i);
		free(mini_tokens_i);
		mini_tokens_i = echo_with_redir(mini, copy);
	}
	if (!ft_strncmp(mini_tokens_i, "$?", 2))
		ft_putnbr_fd(g_ret_number, mini->out_fd);
	else
	{
		ft_putstr_fd(mini_tokens_i, mini->out_fd);
		g_ret_number = 0;
	}
	free(mini_tokens_i);
}

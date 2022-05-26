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

void	print_echo(t_struct *mini, char *mini_tokens_i)
{
	int	i;
	int	flag;
	char	*str;
	char	*aux;

	i = 0;
	while (mini->line_read[i])
	{
		if (mini->line_read[i] == '>')
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		i = 2;
		str = ft_strdup("");
		while (ft_split(mini->commands[1], ' ')[i])
		{
			aux = ft_strdup(str);
			free(str);
			str = ft_strjoin(aux, " ");
			free(aux);
			aux = ft_strdup(str);
			free(str);
			str = ft_strjoin(aux, ft_split(mini->commands[1], ' ')[i]);
			free(aux);
			i++;
		}
		mini_tokens_i = ft_strjoin(mini_tokens_i, str);
		free(str);
	}
	if (!ft_strncmp(mini_tokens_i, "$?", 2))
		ft_putnbr_fd(g_ret_number, mini->out_fd);
	else
	{
		ft_putstr_fd(mini_tokens_i, mini->out_fd);
		g_ret_number = 0;
	}
}

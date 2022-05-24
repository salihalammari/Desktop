#include "minishell.h"

void	redirect_out(t_struct *mini, int j)
{
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	j = mini->c;
	if (mini->commands[j] && mini->commands[j][0] == '>')
	{
		if (mini->commands[j] && mini->commands[j][1] == '>')
		{
			file = ft_strtrim(&mini->commands[j][2], " ");
			mini->out_fd = open(file, flags | O_APPEND, 0777);
			free (file);
		}
		else
			simple_redir_out(mini, j, flags);
		mini->last_redir = 1;
		if (mini->split.n_comand == 1)
			free(mini->line);
	}
}

void	simple_redir_out(t_struct *mini, int j, int flags)
{
	char	*assist;
	char	*file;

	assist = ft_strtrim(&mini->commands[j][1], " ");
	file = ft_substr(assist, 0, find_char(assist, ' '));
	mini->out_fd = open(file, flags | O_TRUNC, 0777);
	free (assist);
	free (file);
}

int	find_char(char *string, char needle)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == needle)
			return (i);
		i++;
	}
	return (i);
}

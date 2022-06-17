#include "minishell.h"

void	control_pipe(t_struct *mini, char *command, int i)
{
	command = ft_strdup(mini->path[i]);
	malloc_check_strdup(command);
	if (mini->tokens[0][0] == '|' && mini->tokens[1])
	{
		if (!mini->tokens[0][1])
			spaces_in_pipe(mini, 2, command);
		else
		{
			mini->tokens[0] = &mini->tokens[0][1];
			spaces_in_pipe(mini, 1, command);
		}
	}
	else
		spaces_in_pipe(mini, 1, command);
}

void	ft_execve_pipe(t_struct *mini, int i, char *command)
{
	char	*path;

	if (mini->tokens[0])
	{
		path = get_path(mini->tokens[0], mini->env.env);
		g_ret_number = execve(path, &mini->tokens[0],
				mini->env.env);
		while (mini->path && mini->path[i] != NULL)
		{
			control_pipe(mini, command, i);
			i++;
		}
		execve_error(mini);
	}
}

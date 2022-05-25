#include "minishell.h"

void	ft_exit(t_struct *mini)
{
	free_char_array2(mini->commands);
	free_char_array2(mini->env.content);
	free_char_array2(mini->env.key);
	free_char_array2(mini->tokens);
	if (mini->path)
		free_char_array(mini->path);
	free (mini->home);
	close(mini->in_fd);
	close(mini->out_fd);
	printf("exit\n");
	exit(10);
}

void	free_line(char *line_read)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
}

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_char_array2(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
}

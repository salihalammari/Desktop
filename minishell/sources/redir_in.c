
#include "minishell.h"

void	redirect_in(t_struct *mini, int j, char *aux)
{
	char	**file;
	
	if (mini->commands[j][0] == '<')
	{
		file = NULL;
		if (mini->commands[j][1] == '<')
			file = double_redir(mini, file, j);
		else
		{
			file = ft_split(&mini->commands[j][1], ' ');
			if (!file)
				return ;
			mini->in_fd = open(file[0], O_RDONLY, 0777);
			if (mini->in_fd == -1 && mini->error_name_file == NULL)
				mini->error_name_file = ft_strdup(file[0]);
		}
		aux = ft_strtrim(mini->line, " ");
		if (mini->split.n_comand == 1 || (aux[0] == '|'
				&& ft_strlen(aux) == 1))
		{
			free(mini->line);
			mini->line = new_comman(1, file);
		}
		free(aux);
		mini->last_redir = 0;
		free_char_array(file);
	}
}

char	**double_redir(t_struct *mini, char **file, int j)
{
	int old_stdin;

	file = ft_split(&mini->commands[j][2], ' ');
	if (!file)
	 return (0);
	 old_stdin = dup(STDIN_FILENO);
	read_until (file[0]);
	mini->in_fd = dup(0);
	dup2(old_stdin, STDIN_FILENO);
	close(old_stdin);
	mini->is_append++;
	return (file);
}

void	read_until(char *end)
{
	char	*line;
	int		fd[2];

	line = ft_strdup("");
	pipe(fd);
	while (ft_strncmp(line, end, ft_strlen(end))
		|| ft_strlen(line) != ft_strlen(end))
	{
		free(line);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) != ft_strlen(end))
			ft_putendl_fd(line, fd[1]);
	}
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	free(line);
}

char	*new_comman(int i, char **str)
{
	char	*aux;

	aux = ft_strdup("");
	while (str[i] != NULL)
	{
		if (ft_strlen(aux) > 0)
			aux = ft_strjoin(aux, " ");
		aux = ft_strjoin(aux, str[i]);
		i++;
	}
	return (aux);
}
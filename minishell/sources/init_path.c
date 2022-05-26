#include "minishell.h"

int	init_path(t_struct *mini)
{
	char	*path_aux;
	int		i;
	char	**path;

	path_aux = ft_strdup(find_env(mini, "PATH"));
	if (!path_aux)
		return (0);
	path = ft_split(path_aux, ':');
	if (!path)
		return (0);
	i = 0;
	while(path[i])
		i++;
	mini->path = (char **)malloc(sizeof(char *) * i);
	if (!mini->path)
		return (free(path), 0);
	i = 0;
	while (path[i] != NULL)
	{
		mini->path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	free_char_array(path);
	free(path_aux);
	return (1);
}

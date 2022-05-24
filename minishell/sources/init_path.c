#include "minishell.h"

int	init_path(t_struct *mini)
{
	char	*path_aux;
	int		i;

	path_aux = ft_strdup(find_env(mini, "PATH"));
	if (!path_aux)
		return (0);
	mini->path = ft_split(path_aux, ':');
	if (!mini->path)
		return (0);
	i = 0;
	while (mini->path && mini->path[i])
	{
		mini->path[i] = ft_strjoin(mini->path[i], "/");
		i++;
	}
	free(path_aux);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:04:09 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:04:11 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_path(t_struct *mini, char **path)
{
	int	i;

	i = 0;
	while (path && path[i])
	{
		mini->path[i] = ft_strjoin(path[i], "/");
		free(path[i]);
		i++;
	}
}

int	init_path(t_struct *mini)
{
	char	*path_aux;
	int		i;
	char	**path;

	path_aux = ft_strdup(find_env(mini, "PATH"));
	malloc_check_strdup(path_aux);
	if (!path_aux)
		return (0);
	path = ft_split(path_aux, ':');
	malloc_check_split(path);
	i = 0;
	while (path[i])
		i++;
	mini->path = malloc(sizeof(char *) * (i + 1));
	malloc_check_split(mini->path);
	create_path(mini, path);
	mini->path[i] = NULL;
	free(path);
	free(path_aux);
	return (1);
}

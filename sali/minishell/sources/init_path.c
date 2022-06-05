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
	{
		printf("malloc error\n");
		exit(1);
	}
	i = 0;
	while (path[i])
		i++;
	mini->path = malloc(sizeof(char *) * (i + 1));
	if (!mini->path)
	{
		printf("malloc error\n");
		exit(1);
	}
	i = 0;
	while (path && path[i])
	{
		mini->path[i] = ft_strjoin(path[i], "/");
		free(path[i]);
		i++;
	}
	mini->path[i] = NULL;
	free(path);
	free(path_aux);
	return (1);
}

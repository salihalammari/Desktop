/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slammari <slammari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:03:35 by sghajdao          #+#    #+#             */
/*   Updated: 2022/06/19 17:42:02 by slammari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(void)
{
	char	path[2000];

	getcwd(path, 2000);
	g_ret_number = 0;
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
}

char	*get_cwd_buf(void)
{
	char	*buf;

	buf = malloc(sizeof(char) * 2000);
	getcwd(buf, 2000);
	return (buf);
}

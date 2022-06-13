/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghajdao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:01:15 by sghajdao          #+#    #+#             */
/*   Updated: 2022/05/29 21:01:17 by sghajdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quote_s1(char *str)
{
    int i;
    int d1;
    int o1;

    i = 0;
    d1 = 0;
    o1 = 0;
    while (str[i])
    {
        if (str[i] == '\"')
            d1++;
        if (str[i] == '\'')
            o1++;
        i++;
    }
    if (((d1 && o1) || (d1 % 2 != 0) || (o1 % 2 != 0)) && find_char(str, '=') == (int)ft_strlen(str))
    {
        printf("minishell: %s not a valid identifier\n", str);
        return (0);
    }
    else
        return (1);
}

static void    count_quotes(char *str1, int d, int o)
{
    int i;

    i = 0;
    while (str1[i])
    {
        if (str1[i] == '\"')
            d++;
        if (str1[i] == '\'')
            o++;
        i++;
    }
}

int check_quotes(char *str1, char *str2)
{
    int d1;
    int o1;
    int d2;
    int o2;

    d1 = 0;
    o1 = 0;
    count_quotes(str1, d1, o1);
    d2 = 0;
    o2 = 0;
    count_quotes(str2, d2, o2);
    if ((str1[0] == '\'' || str1[0] == '\"') || ((d1 % 2 == 0 && d1 > 2) \
        && (d2 % 2 == 0 && d2 > 2)) || (d2 % 2 != 0 && d1 % 2 != 0) \
        || (o1 % 2 == 0 && o2 % 2 != 0 && o1 != 0) \
        || (o1 % 2 != 0 && o2 % 2 == 0 && o2 != 0) || (d1 && o1))
    {
        printf("%s=%s: not a valid identifier\n", str1, str2);
        return (0);
    }
    else
        return (1);
}

static int count_char(char *str, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == c)
            j++;
        i++;
    }
    return (j);
}

int	check_pipe_between_quotes(char *in)
{
	char	*cmd;
    char    **split;

	if (in[0] == D_QUOTE || in[0] == QUOTE)
	{
        cmd = ft_strdup(in);
		take_off_quotes(cmd);
		if ((find_char(in, '|') != (int)ft_strlen(in)) && (count_char(&in[find_char(in, '|')], '\"') % 2 != 0))
		{
			printf("minishell: %s: command not found\n", cmd);
			free(cmd);
			return (0);
		}
        split = ft_split(cmd, ' ');
        malloc_check_split(split);
        if (split[0] && split[1] && (int)ft_strlen(split[1]) > 1)
        {
			printf("minishell: %s: command not found\n", cmd);
			free(cmd);
            free_char_array(split);
			return (0);
        }
        free_char_array(split);
        free(cmd);
	}
	return (1);
}

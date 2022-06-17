#include "minishell.h"

static int	count_char(char *str, char c)
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

static void	error_message(char **cmd)
{
	printf("minishell: %s: command not found\n", *cmd);
	g_ret_number = 1;
	free(*cmd);
}

int	check_pipe_between_quotes(char *in)
{
	char	*cmd;
	char	**split;

	if (in[0] == D_QUOTE || in[0] == QUOTE)
	{
		cmd = ft_strdup(in);
		take_off_quotes(cmd);
		if ((find_char(in, '|') != (int)ft_strlen(in)) && (count_char(&in[find_char(in, '|')], '\"') % 2 != 0))
		{
			error_message(&cmd);
			return (0);
		}
		split = ft_split(cmd, ' ');
		malloc_check_split(split);
		if (split[0] && split[1] && (int)ft_strlen(split[1]) > 1)
		{
			error_message(&cmd);
			free_char_array(&split);
			return (0);
		}
		free_char_array(&split);
		free(cmd);
	}
	return (1);
}

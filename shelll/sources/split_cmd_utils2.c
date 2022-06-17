#include "minishell.h"

int	check_empty_cmd(char *in)
{
	int	i;
	i = 0;
	while (in[i + 1])
	{
		if ((in[i] == D_QUOTE || in[i] == QUOTE) \
			&& (in[i + 1] == D_QUOTE || in[i + 1] == QUOTE))
			return (1);
		i++;
	}
	return (0);
}

int check_cmd(t_struct *mini)
{
    int    i;
    int    flag;

    i = 0;
    flag = 0;
    while (mini->line_read[i + 1])
    {
        if ((mini->line_read[i] == D_QUOTE || mini->line_read[i] == QUOTE) && mini->line_read[i + 1] == ' ')
            flag = 1;
        i++;
    }
    i = 0;
    while (mini->line_read[i + 1])
    {
        if ((mini->line_read[i] == D_QUOTE || mini->line_read[i] == QUOTE) && ft_isalnum(mini->line_read[i]) && mini->line_read[i + 1] == ' ')
            flag = 1;
        i++;
    }
    return (flag);
}

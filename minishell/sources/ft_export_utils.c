#include "minishell.h"

int	ft_strind(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void    print_export(t_struct *mini)
{
    int i;

    i = 0;
    while (i < mini->env.len)
    {
		if (ft_strlen(mini->env.content[i]) > 2)
        	printf("declare -x %s=\"%s\"\n", mini->env.key[i], mini->env.content[i]);
		else
			printf("declare -x %s=%s\n", mini->env.key[i], mini->env.content[i]);
        i++;
    }
}
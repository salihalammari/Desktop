#include "minishell.h"

void    sort_assist(t_struct *mini, int i, int j)
{
    char    *tmp_k;
	char	*tmp_c;

    tmp_k = ft_strdup(mini->sorted.key[i]);
    malloc_check_strdup(tmp_k);
    tmp_c = ft_strdup(mini->sorted.content[i]);
    malloc_check_strdup(tmp_c);
    free(mini->sorted.key[i]);
    free(mini->sorted.content[i]);
    mini->sorted.key[i] = ft_strdup(mini->sorted.key[j]);
    malloc_check_strdup(mini->sorted.key[i]);
    mini->sorted.content[i] = ft_strdup(mini->sorted.content[j]);
    malloc_check_strdup(mini->sorted.content[i]);
    free(mini->sorted.key[j]);
    free(mini->sorted.content[j]);
    mini->sorted.key[j] = ft_strdup(tmp_k);
    malloc_check_strdup(mini->sorted.key[j]);
    mini->sorted.content[j] = ft_strdup(tmp_c);
    malloc_check_strdup(mini->sorted.content[j]);
    free(tmp_k);
    free(tmp_c);
}

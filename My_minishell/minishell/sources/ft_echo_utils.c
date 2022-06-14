#include "minishell.h"

void    join_3(char *aux, char *str, char *split)
{
    aux = ft_strdup(str);
    malloc_check_strdup(aux);
    free(str);
    str = ft_strjoin(aux, " ");
    free(aux);
    aux = ft_strdup(str);
    malloc_check_strdup(aux);
    free(str);
    str = ft_strjoin(aux, split);
    free(aux);
}

void    join_args_after_redir(char **split, char *mini_tokens_i, int i)
{
    char    *aux = NULL;
    char    *str;

    str = ft_strdup("");
	malloc_check_strdup(str);
    while (split[i])
	{
        join_3(aux, str, split[i]);
		i++;
	}
    free_char_array(&split);
	aux = ft_strdup(mini_tokens_i);
	malloc_check_strdup(aux);
	free(mini_tokens_i);
	mini_tokens_i = ft_strjoin(aux, str);
	free(aux);
	free(str);
}

int check_redir_out(t_struct *mini)
{
    int i;

    i = 0;
    while (mini->line_read[i])
	{
		if (mini->line_read[i] == '>' /* && find_char(mini_tokens_i, '>') == (int)ft_strlen(mini_tokens_i) */)
			return (1);
		i++;
	}
    return (0);
}

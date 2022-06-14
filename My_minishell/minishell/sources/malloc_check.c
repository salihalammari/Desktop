#include "minishell.h"

void    malloc_check_split(char **split)
{
    if (!split)
    {
        printf("minishell: malloc error\n");
        free(split);
        exit(1);
    }
}

void    malloc_check_strdup(char *str)
{
    if (!str)
    {
        printf("minishell: malloc error\n");
        free(str);
        exit(1);
    }
}

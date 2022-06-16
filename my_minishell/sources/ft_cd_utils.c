#include "minishell.h"

int cd_home__(t_struct *mini, bool home)
{
	char	*token_aux;
	char	*path;

    if (ft_strncmp(mini->tokens[1], "--", 2) == 0 && mini->tokens[1][2] == '\0')
    {
    	if (home == false)
    	{
			g_ret_number = 1;
    		printf(ERROR_HOME);
    		return (1);
    	}
    	path = ft_strdup(mini->home);
    	malloc_check_strdup(path);
    	token_aux = ft_strdup(path);
    	malloc_check_strdup(token_aux);
    	free(path);
    	change_oldpwd(mini);
    	g_ret_number = chdir(token_aux);
    	change_pwd(mini);
    	free(token_aux);
    	return (0);
    }
    return (1);
}

static int  find_oldpwd(t_struct *mini, char *token_aux)
{
    char    *path;
    int     i;

    if (!find_env(mini, "OLDPWD") || find_env(mini, "OLDPWD")[1] == '\"')
    {
    	printf("minishell: cd: OLDPWD not set\n");
    	g_ret_number = 1;
    	return (1);
    }
    path = ft_strdup(find_env(mini, "OLDPWD"));
    malloc_check_strdup(path);
    token_aux = ft_strdup(path);
    malloc_check_strdup(token_aux);
    free(path);
    i = 0;
    while (mini->env.key[i])
    {
    	if (ft_strncmp(mini->env.key[i], "OLDPWD", 6) == 0)
    		break ;
    	i++;
    }
    change_oldpwd(mini);
    g_ret_number = chdir(token_aux);
    free(token_aux);
    return (0);
}

int cd_to_oldpwd(t_struct *mini)
{
	char	*token_aux;

    if (ft_strncmp(mini->tokens[1], "-", 1) == 0 && mini->tokens[1][1] == '\0')
    {
        token_aux = NULL;
        if (find_oldpwd(mini, token_aux))
            return (1);
    	change_pwd(mini);
    	printf("%s\n", find_env(mini, "PWD"));
    	return (0);
    }
    return (1);
}

int get_cd_path(t_struct *mini, bool home)
{
    char    *token_aux;

    if (mini->tokens[1])
	{
		token_aux = ft_strdup(mini->token.to_print);
		malloc_check_strdup(token_aux);
	}
	else
	{
		if (home == true)
		{
			token_aux = ft_strdup(mini->home);
			malloc_check_strdup(token_aux);
		}
		else
		{
			g_ret_number = 1;
			printf(ERROR_HOME);
			return (1);
		}
	}
    change_oldpwd(mini);
	g_ret_number = chdir(token_aux);
    free(token_aux);
    return (0);
}

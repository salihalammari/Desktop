#include "minishell.h"

static void	change_pwd(t_struct *mini)
{
	int	i;

	i = 0;
	while (mini->env.key[i])
	{
		if (ft_strncmp(mini->env.key[i], "PWD", 3) == 0)
		{
			mini->env.content[i] = get_cwd_buf();
			return ;
		}
		i++;
	}
}

static void	change_oldpwd(t_struct *mini)
{
	int	i;

	i = 0;
	while (mini->env.key[i])
	{
		if (ft_strncmp(mini->env.key[i], "OLDPWD", 6) == 0)
		{
			mini->env.content[i] = get_cwd_buf();
			return ;
		}
		i++;
	}
}

int	ft_cd(t_struct *mini)
{
	char	*token_aux;
	bool	home;

	home = there_is_home(mini);
	if (mini->tokens[1])
		token_aux = ft_strdup(mini->token.to_print);
	else
	{
		if (home == true)
			token_aux = ft_strdup(mini->home);
		else
		{
			g_ret_number = 1;
			printf(ERROR_HOME);
			return (1);
		}
	}
	change_oldpwd(mini);
	g_ret_number = chdir(token_aux);
	if (g_ret_number == -1)
		printf("minishell: cd: %s: %s", mini->tokens[1], ERROR_DIR);
	change_pwd(mini);
	free(token_aux);
	return (0);
}

bool	there_is_home(t_struct *mini)
{
	if (find_env(mini, "HOME"))
		return (true);
	else
		return (false);
}

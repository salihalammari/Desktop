#include "minishell.h"

void    env_aux_allocation(t_struct *mini, char ***env_aux, int i)
{
    *env_aux = ft_split(mini->tokens[i], '=');
    malloc_check_split(*env_aux);
}

void    control_export(t_struct *mini, char **env_aux, int i)
{
    while (mini->tokens[i])
	{
        env_aux_allocation(mini, &env_aux, i);
		if (!env_aux[1])
		{
			if (!check_quote_s1(env_aux[0]))
		  		return ;
			take_off_quotes(env_aux[0]);
			if (env_aux[0][0] == '-')
			{
				printf("minishell: export: -s: invalid option\n");
				i++;
				continue ;
			}
			if (find_env(mini, env_aux[0]))
			{
				if (!equal_not_found(mini, env_aux, i))
					break ;
				continue ;
			}
			just_key_equal(mini, env_aux, i);
			i++;
			continue ;
		}
		exec_verify(mini, env_aux, i);
		i++;
	}
}

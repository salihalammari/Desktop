#include "minishell.h"

static void	take_off_plus(char *str)
{
	int	i;

	if (str[ft_strlen(str) - 1] == '+')
	{
		i = 0;
		while (str[i + 1])
			i++;
		str[i] = '\0';
	}
}

int	if_plus(char *key, char *value, t_struct *mini)
{
	int		i;
	int		flag;
	char	*aux;

	flag = plus_search(key);
	if (flag == 1)
	{
		i = 0;
		take_off_plus(key);
		while (mini->env.key[i])
		{
			if (ft_strncmp(mini->env.key[i], key, ft_strlen(mini->env.key[i])) == 0)
			{
				aux = ft_strdup(mini->env.content[i]);
				free(mini->env.content[i]);
				mini->env.content[i] = ft_strjoin(aux, value);
				free(aux);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

void	ft_export(t_struct *mini)
{
	int		i;
	char	**env_aux;

	print_export(mini);
	i = 1;
	while (mini->tokens[i])
	{
		env_aux = ft_split(mini->tokens[i], '=');
		if (!env_aux)
		 return ;
		if (!env_aux[1])
		{
			if (!check_quote_s1(env_aux[0]))
        		return ;
			env_aux[0] = take_off_quotes(env_aux[0]);
			if (find_env(mini, env_aux[0]))
			{
				i++;
				continue ;
			}
			else
				add_env(mini, env_aux[0], "\'\'");
			i++;
			continue ;
		}
		exec_verify(mini, env_aux, i);
		i++;
	}
	g_ret_number = 0;
}

void	verify_if_env_exists(t_struct *mini, char **env_aux, int i)
{
    char    *key;
    char    *value;

    key = ft_strdup(env_aux[0]);
    value = ft_strdup(env_aux[1]);
    if (!check_quotes(key, value))
        return ;
	if ((find_char(key, '\'') != (int)ft_strlen(key)) || (find_char(key, '\"') != (int)ft_strlen(key)))
	{
		printf("minishell: quotes error\n");
		return ;
	}
    key = take_off_quotes(key);
    value = take_off_quotes(value);
	exec_export_add(mini, key, value, i);
}

void	add_env(t_struct *mini, char *new_key, char *new_content)
{
	int	i;

	mini->env.len++;
	alloc_env_aux(mini);
	i = 0;
	while (i < mini->env.len - 1)
	{
		mini->env_aux.key[i] = ft_strdup(mini->env.key[i]);
		mini->env_aux.content[i] = ft_strdup(mini->env.content[i]);
		i++;
	}
	mini->env_aux.key[i] = ft_strdup(new_key);
	mini->env_aux.content[i] = ft_strdup(new_content);
	i++;
	mini->env_aux.key[i] = NULL;
	mini->env_aux.content[i] = NULL;
	free_char_array(mini->env.key);
	free_char_array(mini->env.content);
	mini->env.key = mini->env_aux.key;
	mini->env.content = mini->env_aux.content;
}

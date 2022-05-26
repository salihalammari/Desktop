#include "minishell.h"

int	is_key_valid(char *key)
{
	int	i;

	i = 1;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

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
	int	i;
	int	flag;

	i = 0;
	while (key[i])
	{
		if (key[i] == '+')
			flag = 1;
		i++;
	}
	if (flag == 1)
	{
		i = 0;
		take_off_plus(key);
		while (mini->env.key[i])
		{
			if (ft_strncmp(mini->env.key[i], key, ft_strlen(mini->env.key[i])) == 0)
			{
				mini->env.content[i] = ft_strjoin(mini->env.content[i], value);
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

	if (!mini->tokens[1])
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
		if (env_aux[1])
			verify_if_env_exists(mini, env_aux, i);
		else if (mini->tokens[i][ft_strlen(mini->tokens[1]) - 1] == '=')
		{
			env_aux[1] = ft_strdup("");
			verify_if_env_exists(mini, env_aux, i);
		}
		free(env_aux[0]);
		free(env_aux[1]);
		free(env_aux);
		env_aux = NULL;
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
	if (if_plus(key, value, mini))
		return ;
	if (find_env(mini, key))
	{
		free(mini->env.content[mini->env.index]);
		mini->env.content[mini->env.index] = ft_strdup(value);
	}
	else
		add_env(mini, key, value);
	if (!ft_strncmp(mini->tokens[i], "PATH", 4))
	{
		if (mini->path)
			free_char_array(mini->path);
		init_path(mini);
	}
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

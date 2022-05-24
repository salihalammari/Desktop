#include "minishell.h"

void	ft_pwd(t_struct *mini)
{
	char	*buf;

	buf = get_cwd_buf();
	ft_putendl_fd(buf, mini->out_fd);
	if (buf == NULL)
		g_ret_number = 1;
	else
		g_ret_number = 0;
	free(buf);
}

char	*get_cwd_buf(void)
{
	size_t	size;
	char	*buf;

	size = 2000;
	buf = NULL;
	buf = getcwd(buf, size);
	return (buf);
}

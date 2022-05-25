#include "minishell.h"

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		write(1,"\033[1A\033[44Cexit\n",14);
		exit(10);
	}
}

void	restore_prompt(int sig)
{
	g_ret_number = 130;
	write(1, "\n", 1);
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_ret_number = 130;
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	back_slash(int sig)
{
	g_ret_number = 131;
	(void)sig;
}

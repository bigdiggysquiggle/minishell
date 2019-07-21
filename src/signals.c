#include "ft_minishell.h"

void	sig_process(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, sig_process);
	}
}

void	sig_main(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		ft_putstr(PROMPT);
		signal(SIGINT, sig_main);
	}
}

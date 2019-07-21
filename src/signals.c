/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dromansk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 15:23:44 by dromansk          #+#    #+#             */
/*   Updated: 2019/07/21 15:45:37 by dromansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

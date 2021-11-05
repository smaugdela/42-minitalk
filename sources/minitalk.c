/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:52:00 by smagdela          #+#    #+#             */
/*   Updated: 2021/10/20 17:20:53 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

__int8_t	global;

void	my_sig(int param)
{

	if (param == SIGUSR1)
	{
		global = 0;
	}
	if (param == SIGUSR2)
	{
		global = 1;
	}
}

int     main()
{
	int					pid;
	struct sigaction	act;
	int					i;
	__uint8_t			c;
//	Uncomment if signals need to be blocked during handling
//	sigset_t			blocked;
//	sigemptyset(&blocked);
//	sigaddset(&blocked, SIGUSR2);

	act.sa_handler = my_sig;
	pid = getpid();
	ft_printf("Server pid is: %d\n", pid);
	if (sigaction(SIGUSR1, &act, NULL) == -1 || sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		return(42);
	}
	while (1)
	{
		i = 0;
		c = 0;
		while(i < 8)
		{
			pause();
			c = c | global;
			c = c << 1;
			++i;
		}
		write(1, &c, 1);
	}
}

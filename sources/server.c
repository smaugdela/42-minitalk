/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:52:00 by smagdela          #+#    #+#             */
/*   Updated: 2021/10/20 17:20:53 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_hermes	global;

static void	my_sig(int param, siginfo_t *info, void *context)
{
	(void)context;
	if (param == SIGUSR1)
		global.signal = 0;
	else if (param == SIGUSR2)
		global.signal = 1;
	else if (param == SIGINT || param == SIGQUIT)
	{
		// free correctement?
		exit(0);
	}
	global.client_pid = info->si_pid;
}

int     main()
{
	struct sigaction	act;
	int					i;
	int					str_len;
//	Uncomment if signals need to be blocked during handling
//	sigset_t			blocked;
//	sigemptyset(&blocked);
//	sigaddset(&blocked, SIGUSR2);

	act.sa_sigaction = my_sig;
	act.sa_flags = SA_SIGINFO;
	ft_printf("Server pid is: %d\n", getpid());
	if (sigaction(SIGUSR1, &act, NULL) == -1 || sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		return(42);
	}
	str_len = 0;
	i = sizeof(str_len) * 8;
	while(i--)
	{
		pause();
		if (global.signal == 1)
			str_len = str_len | (1 << ((sizeof(str_len) * 8) - i - 1));
	}
	ft_printf("strlen = %d\n", str_len);	//should malloc the string here.
	sleep(5);
	if (global.signal == 1)
	{
		ft_printf("Messij received from client.\nResponding OK signal to client shortly, at pid %d\n", global.client_pid);
		sleep(3);
		kill(global.client_pid, SIGUSR2);
	}
	else
	{
		ft_printf("No signal received.\n");
	}
	return (0);
/*
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
*/
}

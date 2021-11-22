/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:46:14 by smagdela          #+#    #+#             */
/*   Updated: 2021/11/22 19:27:06 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_bool error_check(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd("Error: usage: ./client <PID> <string to transmit>\n", 2);
		return (FALSE);
	}
	if (ft_strlen(argv[1]) > ft_nblen(MAX_PID) || ft_atoi(argv[1]) < 0
		|| ft_atoi(argv[1]) > MAX_PID)
	{
		ft_putstr_fd("Error: PID not valid.\n", 2);
		return (FALSE);
	}
	if (kill(ft_atoi(argv[1]), 0) == -1)
	{
		ft_putstr_fd("Error: PID not valid, no process found for that ID.\n", 2);
		return (FALSE);
	}
	ft_printf("frquency = %d\n", TRANSMISSION_FREQ);
	if (TRANSMISSION_FREQ < 100 || TRANSMISSION_FREQ > 1000000)
	{
		ft_putstr_fd("Error: transmission freq should be between 1 kHz and 1MHz.\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

static void client_signal_handler(int param)
{
	if (param == SIGUSR2)
	{
		ft_printf("Messij received from server! Now closing.\n");
	}
}

int	main(int argc, char **argv)
{
	int					str_len;
	int					pid;
	int					i;
	struct sigaction	act;

	if (error_check(argc, argv) == FALSE)
		return (42);
	act.sa_handler = client_signal_handler;
	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		return(42);
	}
	pid = ft_atoi(argv[1]);
	str_len = ft_strlen(argv[2]);
	ft_printf("strlen = %d\n", str_len);
	i = sizeof(str_len) * 8;
	while(i--)
	{
		if (str_len & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		str_len = str_len >> 1;
		usleep(1000000 / TRANSMISSION_FREQ);
	}
	ft_printf("Finnished sending strlen, sending OK signal to server shortly.\n");
	sleep(3);
	kill(pid, SIGUSR2);
	ft_printf("Waiting for response...\n");
	pause();
	return (0);
}
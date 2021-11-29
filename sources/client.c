/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:46:14 by smagdela          #+#    #+#             */
/*   Updated: 2021/11/29 16:54:44 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_bool	error_check(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd("Error: usage: ./client <PID> <string to transmit>\n", 2);
		return (FALSE);
	}
	if (ft_strlen(argv[1]) > ft_nblen(MAX_PID) || ft_atoi(argv[1]) <= 0
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
	if (TRANSMISSION_FREQ < MIN_FREQ || TRANSMISSION_FREQ > MAX_FREQ)
	{
		ft_putstr_fd("Error: transmission freq ", 2);
		ft_putstr_fd("should be between 1kHz and 150kHz (kbits/sec).\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

static void	client_signal_handler(int param)
{
	if (param == SIGUSR2)
	{
	}
}

static void	send_strlen(pid_t pid, size_t str_len)
{
	int	i;

	i = sizeof(str_len) * 8;
	while (i--)
	{
		if (str_len & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		str_len = str_len >> 1;
		if (i)
			usleep(1000000 / TRANSMISSION_FREQ);
	}
}

static void	send_str(pid_t pid, char *str, size_t str_len)
{
	int		i;
	char	c;
	size_t	index;

	index = 0;
	while (index < str_len)
	{
		c = str[index];
		i = sizeof(c) * 8;
		while (i--)
		{
			if (c & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			c = c >> 1;
			usleep(1000000 / TRANSMISSION_FREQ);
		}
		++index;
	}
}

int	main(int argc, char **argv)
{
	size_t				str_len;
	int					pid;
	struct sigaction	act;

	if (error_check(argc, argv) == FALSE)
		return (42);
	act.sa_handler = client_signal_handler;
	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		return (42);
	}
	if (TRANSMISSION_FREQ < 8000)
	{
		ft_putstr_fd("\nWarning: transmission frequency very low (maybe ", 1);
		ft_putstr_fd("because of linux?), please do not care about the sp", 1);
		ft_putstr_fd("eed if you're correcting under these conditions.\n", 1);
	}
	pid = ft_atoi(argv[1]);
	str_len = ft_strlen(argv[2]);
	send_strlen(pid, str_len);
	pause();
	send_str(pid, argv[2], str_len);
	return (0);
}

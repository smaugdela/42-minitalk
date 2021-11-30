/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:46:14 by smagdela          #+#    #+#             */
/*   Updated: 2021/11/30 15:59:48 by smagdela         ###   ########.fr       */
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
	return (TRUE);
}

static void	client_signal_handler(int param)
{
	if (param == SIGUSR2)
	{
	}
}

static void	send_strlen(pid_t pid, size_t str_len, struct sigaction act)
{
	int	i;

	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		exit(42);
	}
	i = sizeof(str_len) * 8;
	while (i--)
	{
		if (str_len & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		if (i)
			pause();
		str_len = str_len >> 1;
	}
}

static void	send_str(pid_t pid, char *str, size_t str_len, struct sigaction act)
{
	int		i;
	char	c;
	size_t	index;

	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		exit(42);
	}
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
			pause();
			c = c >> 1;
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
	pid = ft_atoi(argv[1]);
	str_len = ft_strlen(argv[2]);
	ft_printf("str_len = %d\n", str_len);
	send_strlen(pid, str_len, act);
	ft_printf("str_len sent! Now waiting for server to respond...\n");
	pause();
	send_str(pid, argv[2], str_len, act);
	return (0);
}

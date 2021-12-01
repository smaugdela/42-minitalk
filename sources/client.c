/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:46:14 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/01 18:06:40 by smagdela         ###   ########.fr       */
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

static void	client_signal_handler(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGUSR2)
	{
		return ;
	}
	(void)context;
	(void)info;
}

static void	send_strlen(pid_t pid, size_t s_len, struct sigaction act)
{
	int	i;

	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		exit (42);
	}
	i = sizeof(s_len) * 8;
	while (i--)
	{
		usleep(DELAY);
		if (s_len & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		pause();
		s_len = s_len >> 1;
	}
	return ;
}

static void	send_str(pid_t pid, char *str, size_t s_len, struct sigaction act)
{
	int		i;
	char	c;
	int		index;

	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		exit (42);
	}
	index = -1;
	while (++index < s_len)
	{
		c = str[index];
		i = sizeof(c) * 8;
		while (i--)
		{
			usleep(DELAY);
			if (c & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			pause();
			c = c >> 1;
		}
	}
}

int	main(int argc, char **argv)
{
	size_t				str_len;
	int					pid;
	struct sigaction	act;
	sigset_t			blocked;

	sigemptyset(&blocked);
	sigaddset(&blocked, SIGUSR2);
	act.sa_mask = blocked;
	if (error_check(argc, argv) == FALSE)
		return (42);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = client_signal_handler;
	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		return (42);
	}
	pid = ft_atoi(argv[1]);
	str_len = ft_strlen(argv[2]);
	send_strlen(pid, str_len, act);
	send_str(pid, argv[2], str_len, act);
	return (0);
}

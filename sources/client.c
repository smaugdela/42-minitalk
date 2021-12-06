/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:46:14 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/06 16:36:04 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

static void	send_str(pid_t pid, char *str, int s_len, struct sigaction act)
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
	if (str_len)
	{
		send_strlen(pid, str_len, act);
		send_str(pid, argv[2], str_len, act);
	}
	return (0);
}

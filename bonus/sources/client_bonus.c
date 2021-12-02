/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:59:51 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/02 16:39:28 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
		usleep(DELAY);
		if (str_len & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		pause();
		str_len = str_len >> 1;
	}
}

static void	send_str(pid_t pid, char32_t *str, int str_len)
{
	int		i;
	char32_t	c;
	int	index;

	index = -1;
	while (++index < str_len)
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

	if (error_check(argc, argv) == FALSE)
		return (42);
	act.sa_handler = client_signal_handler;
	if (sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		return (42);
	}
	pid = ft_atoi(argv[1]);
	str_len = ft_strlen_unic((char32_t *)argv[2]);
	send_strlen(pid, str_len);
	send_str(pid, (char32_t *)argv[2], str_len);
	return (0);
}

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

#define _POSIX_C_SOURCE 1

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>	//ATTENTION
#include <unistd.h>

__int8_t	global;

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
	{
		while (*s)
		{
			write(fd, s, sizeof(*s));
			++s;
		}
	}
}

void ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(c));
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

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
	printf("Server pid is: %d\n", pid);
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

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

static int	roger_strlen(int sig, size_t *s_len)
{
	static int	i = sizeof(*s_len) * 8;

	while(i--)
	{
		if (sig == SIGUSR2)
			*s_len = *s_len | (1 << ((sizeof(*s_len) * 8) - i - 1));
	}
	return (i);
}

static void	roger_str(int sig, char *str)
{
	static int		i = 8;
	static int8_t	c = 0;

	if (i--)
	{

	}
	else
	{
		str[?] = (char)c;
		i = 8;
		c = 0;
	}
}

static void	my_sig(int sig, siginfo_t *info, void *context)
{
	static size_t	s_len = 0;
	static t_bool	metadata = 1;
	char			*str;

	(void)context;
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (metadata && roger_strlen(sig, &s_len) == 0)
		{
			ft_printf("strlen = %d\n", s_len);	//should malloc the string here.
			str = malloc((s_len + 1) * sizeof(char));
			if (str == NULL)
				exit(42);
			str[s_len] = '\0';
			metadata = 0;
			kill(info->si_pid, SIGUSR2);
		}
		else if (!metadata && s_len--)
			roger_str(sig, str);
		else
		{
			ft_putstr_fd(str, 1);
			free(str);
			metadata = 1;
		}

	}
	else if ((sig == SIGINT || sig == SIGQUIT) && !metadata)
		free(str);
}

int     main()
{
	struct sigaction	act;
	int					i;
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
	i = sizeof(size_t) * 8;
	while(1)
		pause();
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

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

	if (i--)
	{
		if (sig == SIGUSR2)
			*s_len = *s_len | (1 << ((sizeof(*s_len) * 8) - i - 1));
	}
	return (i);
}

static size_t	roger_str(int sig, char *str)
{
	static int8_t	c = 0;
	static int		i = sizeof(c) * 8;
	static size_t	index_c = 0;

	if (i--)
		c = c | (1 << ((sizeof(c) * 8) - i - 1));
	else if (sig == 0 && str == NULL)
	{
		i = 8;
		c = 0;
		index_c = 0;
	}
	else
	{
		str[index_c] = (char)c;
		i = 8;
		c = 0;
		++index_c;
	}
	return (index_c);
}

static void	my_sig(int sig, siginfo_t *info, void *context)
{
	static size_t	s_len = 0;
	static t_bool	metadata = 1;
	char			*str;

	(void)context;
	str = NULL;
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (metadata && roger_strlen(sig, &s_len) == 0)
		{
			ft_printf("strlen = %d\n", s_len);
			str = malloc((s_len + 1) * sizeof(char));
			if (str == NULL)
				exit(42);
			str[s_len] = '\0';
			metadata = 0;
			kill(info->si_pid, SIGUSR2);
		}
		if (!metadata && roger_str(sig, str) == s_len)
		{
			ft_putstr_fd(str, 1);
			free(str);
			metadata = 1;
			roger_str(0, NULL);
		}
	}
/*
	else if ((sig == SIGINT || sig == SIGQUIT) && !metadata)
		free(str);
*/
}

int     main()
{
	struct sigaction	act;
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
	while(1)
		pause();
	return (0);
}

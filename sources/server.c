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

static int	roger_strlen(int sig, size_t *s_len, pid_t pid)
{
	static int	i = sizeof(*s_len) * 8;

	if (sig == 0 && s_len == NULL && pid == -1)
		i = sizeof(*s_len) * 8;
	else if (i--)
	{
		if (sig == SIGUSR2)
			*s_len = *s_len | (1 << ((sizeof(*s_len) * 8) - i - 1));
	}
	kill(pid, SIGUSR2);
	return (i);
}

static size_t	roger_str(int sig, char *str, pid_t pid)
{
	static char		c = 0;
	static int		i = sizeof(c) * 8;
	static size_t	index_c = 0;

	if (sig == 0 && str == NULL && pid == -1)
	{
		i = sizeof(c) * 8;
		c = 0;
		index_c = 0;
		return (0);
	}
	--i;
	if (sig == SIGUSR2)
		c = c | (1 << ((sizeof(c) * 8) - i - 1));
	if (!i)
	{
		str[index_c] = c;
		i = 8;
		c = 0;
		++index_c;
	}
	if (i)
		return (index_c);
	else
		return (index_c + 1);
}

static void	reset(size_t *s_len, t_bool *metadata, char *str)
{
	ft_putstr_fd(str, 1);
	*s_len = 0;
	free(str);
	str = NULL;
	*metadata = TRUE;
	roger_strlen(0, NULL, -1);
	roger_str(0, NULL, -1);
}

static void	my_sig(int sig, siginfo_t *info, void *context)
{
	static size_t	s_len = 0;
	static t_bool	metadata = TRUE;
	static char		*str = NULL;

	(void)context;
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (metadata && roger_strlen(sig, &s_len, info->si_pid) == 0)
		{
			str = malloc((s_len + 1) * sizeof(char));
			if (str == NULL)
				exit(42);
			str[s_len] = '\0';
			metadata = FALSE;
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		else if (!metadata && roger_str(sig, str, info->si_pid) == s_len)
			reset(&s_len, &metadata, str);
		kill(info->si_pid, SIGUSR2);
	}
}

/*
	Uncomment if signals need to be blocked during handling
	sigset_t			blocked;
	sigemptyset(&blocked);
	sigaddset(&blocked, SIGUSR2);
*/
int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = my_sig;
	act.sa_flags = SA_SIGINFO;
	ft_printf("Server pid is: %d\n", getpid());
	if (sigaction(SIGUSR1, &act, NULL) == -1
		|| sigaction(SIGUSR2, &act, NULL) == -1)
	{
		ft_putstr_fd("Error.\n", 2);
		return (42);
	}
	while (1)
		pause();
	return (0);
}

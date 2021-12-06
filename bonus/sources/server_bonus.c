/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:59:48 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/06 11:31:47 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	roger_strlen(int sig, t_client_info *c)
{
	c->i = c->max_str;
	if (sig == 0 && c == NULL)
		c->i = c->max_str;
	else if ((c->i)--)
	{
		if (sig == SIGUSR2)
			c->s_len = c->s_len | (1 << ((c->max_str) - c->i - 1));
	}
	return (c->i);
}

static size_t	roger_str(int sig, t_client_info *c)
{
	c->i = c->max_c;
	if (sig == 0 && c == NULL)
	{
		c->i = c->max_c;
		c->c = 0;
		c->index_c = 0;
		return (0);
	}
	--(c->i);
	if (sig == SIGUSR2)
		c->c = c->c | (1 << ((c->max_c) - c->i - 1));
	if (!(c->i))
	{
		c->str[c->index_c] = c->c;
		c->i = c->max_c;
		c->c = 0;
		++c->index_c;
	}
	if (c->i)
		return (c->index_c);
	else
		return (c->index_c + 1);
}

static void	reset(t_client_info *client, t_client_info *clients)
{
	ft_putstr_unic_fd(client->str, 1);
	free(client->str);
	del_client(client, clients);
	roger_strlen(0, NULL);
	roger_str(0, NULL);
}

static void	my_sig(int sig, siginfo_t *info, void *context)
{
	static t_client_info	*clients = NULL;
	t_client_info			*client;

	client = search_pid(clients, info->si_pid);
	if (client == NULL)
		client = add_client(clients, info->si_pid);
	(void)context;
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (client->metadata && roger_strlen(sig, client) == 0)
		{
			client->str = malloc((client->s_len + 1) * sizeof(char));
			if (client->str == NULL)
				exit(42);
			client->str[client->s_len] = '\0';
			client->metadata = FALSE;
		}
		else if (!client->metadata
			&& roger_str(sig, client) == client->s_len)
			reset(client, clients);
		usleep(DELAY);
		kill(info->si_pid, SIGUSR2);
		return ;
	}
}

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

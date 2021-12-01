/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:59:48 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/01 18:10:29 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static int	roger_strlen(int sig, t_client_info *c)
{
	c->i = sizeof(c->s_len) * 8;
	if (sig == 0 && c->s_len == NULL)
		c->i = sizeof(c->s_len) * 8;
	else if (c->i--)
	{
		if (sig == SIGUSR2)
			c->s_len = c->s_len | (1 << ((sizeof(c->s_len) * 8) - c->i - 1));
	}
	return (c->i);
}

static size_t	roger_str(int sig, t_client_info *client)
{
	client->i = sizeof(client->c) * 8;
	if (sig == 0 && client == NULL)
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

static void	reset(t_client_info *client, t_client_info *clients)
{
	ft_putstr_fd(client->str, 1);
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
		if (client->metadata && roger_strlen(sig, &client->s_len) == 0)
		{
			client->str = malloc((client->s_len + 1) * sizeof(char));
			if (client->str == NULL)
				exit(42);
			client->str[client->s_len] = '\0';
			client->metadata = FALSE;
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		else if (!client->metadata
			&& roger_str(sig, client->str) == client->s_len)
			reset(client, clients);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:33:44 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/01 18:08:13 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_client_info	*search_pid(t_client_info *clients, pid_t pid)
{
	t_client_info	*client;

	if (clients == NULL)
		return (NULL);
	client = clients;
	while (client != NULL && client->pid != pid)
		client = client->next;
	return (client);
}

t_client_info	*add_client(t_client_info *clients, pid_t pid)
{
	t_client_info	*client;
	t_client_info	*tmp;

	client = malloc(sizeof(t_client_info) * 1);
	if (client == NULL)
		return (NULL);
	client->i = 0;
	client->c = 0;
	client->metadata = TRUE;
	client->next = NULL;
	client->pid = pid;
	client->s_len = 0;
	client->index_c = 0;
	if (clients == NULL)
		clients = client;
	else
	{
		tmp = clients;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = client;
	}
	return (client);
}

t_bool	del_client(t_client_info *client, t_client_info *clients)
{
	t_client_info	*tmp;

	if (client == clients)
		free(client);
	else
	{
		tmp = clients;
		while (tmp->next != client)
			tmp = tmp->next;
		tmp->next = client->next;
		free(client);
	}
	return (TRUE);
}

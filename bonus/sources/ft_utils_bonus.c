/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:33:44 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/06 12:04:49 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
/*
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
	client->max_c = sizeof(client->c) * 8;
	client->metadata = TRUE;
	client->next = NULL;
	client->pid = pid;
	client->s_len = 0;
	client->max_str = sizeof(client->s_len) * 8;
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

	if(client == NULL || clients == NULL)
		return (FALSE);
	if (client == clients)
	{
		tmp = client->next;
		free(client);
		clients = tmp;
	}
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

void	ft_putstr_unic_fd(char32_t *str, int fd)
{
	char32_t	c;

	while (*str)
	{
		c = (char32_t)str;
		write(fd, &c, 1);
		++str;
	}
}

size_t	ft_strlen_unic(char32_t *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		++str;
		++i;
	}
	return (i);
}
*/
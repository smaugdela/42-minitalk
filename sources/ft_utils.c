/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:52:24 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/06 11:54:42 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static size_t	ft_nblen(int64_t nb)
{
	size_t		len;
	uint64_t	tmp_nb;

	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
	{
		++len;
		tmp_nb = -nb;
	}
	else
		tmp_nb = nb;
	while (tmp_nb)
	{
		++len;
		tmp_nb = tmp_nb / 10;
	}
	return (len);
}

t_bool	error_check(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr_fd("Error: usage: ./client <PID> <string to transmit>\n", 2);
		return (FALSE);
	}
	if (ft_strlen(argv[1]) > ft_nblen(MAX_PID) || ft_atoi(argv[1]) <= 0
		|| ft_atoi(argv[1]) > MAX_PID)
	{
		ft_putstr_fd("Error: PID not valid.\n", 2);
		return (FALSE);
	}
	if (kill(ft_atoi(argv[1]), 0) == -1)
	{
		ft_putstr_fd("Error: PID not valid, no process found for that ID.\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

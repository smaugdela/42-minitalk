/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:23:51 by smagdela          #+#    #+#             */
/*   Updated: 2021/11/05 15:25:46 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putlnbr_fd(int64_t n, int fd)
{
	char	c;

	if (n == -9223372036854775807)
		write (fd, "−9223372036854775807", 11);
	else
	{
		if (n < 0)
		{
			write (fd, "-", 1);
			n = -n;
		}
		if (n <= 9 && n >= 0)
		{
			c = '0' + n;
			write (fd, &c, 1);
		}
		else
		{
			ft_putlnbr_fd(n / 10, fd);
			ft_putlnbr_fd(n % 10, fd);
		}
	}
}

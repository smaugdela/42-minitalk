/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:22:13 by smagdela          #+#    #+#             */
/*   Updated: 2021/09/01 13:09:29 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*-*/

#include "ft_printf.h"

static size_t	ft_hex_len(uint64_t nb)
{
	size_t	len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb)
	{
		++len;
		nb = nb / 16;
	}
	return (len);
}

static void	ft_put_ptr(uint64_t n)
{
	char	*base;

	base = "0123456789abcdef";
	if (n < 16)
		write(1, &base[n], 1);
	else
	{
		ft_put_ptr(n / 16);
		ft_put_ptr(n % 16);
	}
}

static void	ft_printer(uint64_t ptr)
{
	write(1, "0x", 2);
	ft_put_ptr(ptr);
}

int	ft_print_p(t_specifier spec, void *arg)
{
	uint64_t	ptr;
	size_t		len;

	if (arg == NULL)
		return (ft_print_s(spec, OSNUL));
	ptr = (uint64_t)arg;
	len = ft_hex_len(ptr) + 2;
	if (spec.minus_flag)
	{
		ft_printer(ptr);
		len += ft_print_width(spec.width, 0, len);
	}
	else
	{
		len += ft_print_width(spec.width, 0, len);
		ft_printer(ptr);
	}
	return (len);
}

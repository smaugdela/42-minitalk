/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:21:12 by smagdela          #+#    #+#             */
/*   Updated: 2021/11/05 15:25:19 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*-0.*/

#include "ft_printf.h"

static unsigned int	ft_uint_len(unsigned int nb)
{
	unsigned int	len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb)
	{
		++len;
		nb = nb / 10;
	}
	return (len);
}

int	ft_print_u(t_specifier spec, unsigned int arg)
{
	int	arg_len;
	int	len;

	if (arg == 0 && spec.precision == 0)
		return (ft_print_s(spec, ""));
	arg_len = ft_max(ft_uint_len(arg), spec.precision);
	len = arg_len;
	if (spec.minus_flag)
	{
		ft_print_width(spec.precision, 1, ft_uint_len(arg));
		ft_putlnbr_fd(arg, 1);
		len += ft_print_width(spec.width, spec.zero_flag, arg_len);
	}
	else
	{
		len += ft_print_width(spec.width, spec.zero_flag, arg_len);
		ft_print_width(spec.precision, 1, ft_uint_len(arg));
		ft_putlnbr_fd(arg, 1);
	}
	return (len);
}

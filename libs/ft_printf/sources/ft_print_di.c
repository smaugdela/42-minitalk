/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_di.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:32:45 by smagdela          #+#    #+#             */
/*   Updated: 2021/11/05 15:25:19 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*-0+ .*/

#include "ft_printf.h"

static int	ft_nblen(int64_t nb)
{
	int			len;
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

static uint64_t	ft_absol(int64_t nb)
{
	if (nb >= 0)
		return ((uint64_t)nb);
	return ((uint64_t)(-1 * nb));
}

static uint64_t	ft_sign_handler(int64_t arg, t_specifier spec)
{
	if (arg < 0)
	{
		write(1, "-", 1);
		return (ft_absol(arg));
	}
	else
	{
		if (spec.plus_flag)
			write(1, "+", 1);
		else if (spec.space_flag)
			write(1, " ", 1);
		return (arg);
	}
}

static void	ft_printer(t_specifier spec, int64_t arg, int arg_len)
{
	if (spec.zero_flag && arg < 0)
		arg = ft_sign_handler(arg, spec);
	if (spec.minus_flag)
	{
		arg = ft_sign_handler(arg, spec);
		ft_print_width(spec.precision, 1, ft_nblen(ft_absol(arg)));
		ft_putlnbr_fd(arg, 1);
		ft_print_width(spec.width, 0, arg_len);
	}
	else
	{
		ft_print_width(spec.width, spec.zero_flag, arg_len);
		arg = ft_sign_handler(arg, spec);
		ft_print_width(spec.precision, 1, ft_nblen(ft_absol(arg)));
		ft_putlnbr_fd(arg, 1);
	}
}

int	ft_print_di(t_specifier spec, int arg)
{
	int	arg_len;
	int	len;

	if (arg == 0 && spec.precision == 0)
		return (ft_print_s(spec, ""));
	arg_len = ft_max(ft_nblen(ft_absol(arg)), spec.precision);
	if (arg >= 0)
		arg_len += spec.plus_flag + spec.space_flag;
	else
		++arg_len;
	len = arg_len;
	ft_printer(spec, arg, arg_len);
	return (len + ft_max(spec.width - arg_len, 0));
}

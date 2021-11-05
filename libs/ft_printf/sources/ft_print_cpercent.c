/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_cpercent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:20:23 by smagdela          #+#    #+#             */
/*   Updated: 2021/08/26 10:59:44 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* - et -0 pour le %*/

#include "ft_printf.h"

int	ft_print_cpercent(t_specifier spec, char arg)
{
	int	len;

	if (spec.minus_flag)
	{
		write(1, &arg, 1);
		len = ft_print_width(spec.width, 0, 1);
	}
	else if (spec.zero_flag && arg == '%')
	{
		len = ft_print_width(spec.width, 1, 1);
		write(1, &arg, 1);
	}
	else
	{
		len = ft_print_width(spec.width, 0, 1);
		write(1, &arg, 1);
	}
	return (++len);
}

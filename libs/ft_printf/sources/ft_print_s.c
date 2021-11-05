/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:20:45 by smagdela          #+#    #+#             */
/*   Updated: 2021/09/01 14:35:43 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*-.*/

#include "ft_printf.h"

int	ft_print_s(t_specifier spec, char *arg)
{
	int	len;

	if (arg == NULL)
		arg = "(null)";
	if (spec.precision != -1)
		arg = ft_substr(arg, 0, spec.precision);
	else
		arg = ft_strdup(arg);
	len = ft_strlen(arg);
	if (spec.minus_flag)
	{
		ft_putstr_fd(arg, 1);
		len += ft_print_width(spec.width, 0, ft_strlen(arg));
	}
	else
	{
		len += ft_print_width(spec.width, 0, ft_strlen(arg));
		ft_putstr_fd(arg, 1);
	}
	free (arg);
	return (len);
}

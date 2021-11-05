/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:43:53 by smagdela          #+#    #+#             */
/*   Updated: 2021/09/06 12:25:41 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_dispatcher(const char *str, va_list arguments)
{
	char		*specifier;
	t_specifier	spec;

	specifier = ft_substr(str, 0, ft_strlen_charset(str, "cspdiuxX%\0") + 1);
	spec = ft_scan_structspec(specifier);
	free(specifier);
	if (spec.converter == 'c')
		return (ft_print_cpercent(spec, (char)va_arg(arguments, int)));
	else if (spec.converter == '%')
		return (ft_print_cpercent(spec, '%'));
	else if (spec.converter == 's')
		return (ft_print_s(spec, va_arg(arguments, char *)));
	else if (ft_is_in_charset(spec.converter, "di"))
		return (ft_print_di(spec, va_arg(arguments, int)));
	else if (spec.converter == 'u')
		return (ft_print_u(spec, va_arg(arguments, unsigned int)));
	else if (ft_is_in_charset(spec.converter, "xX"))
		return (ft_print_x(spec, va_arg(arguments, unsigned int)));
	else if (spec.converter == 'p')
		return (ft_print_p(spec, va_arg(arguments, void *)));
	else
		return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list		arguments;
	int			len;

	va_start(arguments, str);
	len = 0;
	while (*str)
	{
		if (*str == 37)
		{
			len += ft_dispatcher(++str, arguments);
			str += ft_strlen_charset(str, "cspdiuxX%\0");
			if (*str == '\0')
				return (len);
		}
		else
		{
			write(1, str, 1);
			++len;
		}
		++str;
	}
	va_end(arguments);
	return (len);
}

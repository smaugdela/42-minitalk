/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_structspec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 11:42:10 by smagdela          #+#    #+#             */
/*   Updated: 2021/09/01 10:27:14 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_specifier	ft_init_structspec(char *specifier)
{
	t_specifier	spec;

	spec.minus_flag = 0;
	spec.plus_flag = 0;
	spec.zero_flag = 0;
	spec.space_flag = 0;
	if (ft_strchr(specifier, '#') != NULL)
		spec.sharp_flag = 1;
	else
		spec.sharp_flag = 0;
	spec.precision = -1;
	spec.width = -1;
	spec.converter = specifier[ft_strlen_charset(specifier, "cspdiuxX%\0")];
	return (spec);
}

t_specifier	ft_scan_structspec(char *spec)
{
	t_specifier	output;
	char		*width_ptr;

	output = ft_init_structspec(spec);
	width_ptr = spec;
	while (ft_is_in_charset(*width_ptr, "-+ 0#"))
		++width_ptr;
	if (ft_strchr(spec, '-') != NULL)
		output.minus_flag = 1;
	else if (ft_strchr(spec, '0') != NULL && ft_strchr(spec, '0') < width_ptr)
		output.zero_flag = 1;
	if (ft_strchr(spec, '+') != NULL)
		output.plus_flag = 1;
	else if (ft_strchr(spec, ' ') != NULL)
		output.space_flag = 1;
	if (ft_atoi(width_ptr) > 0)
		output.width = ft_atoi(width_ptr);
	if (ft_strchr(spec, '.') != NULL)
	{
		output.precision = ft_atoi(ft_strchr(spec, '.') + 1);
		if (output.converter != 's')
			output.zero_flag = 0;
	}
	return (output);
}

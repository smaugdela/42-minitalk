/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 08:07:56 by smagdela          #+#    #+#             */
/*   Updated: 2021/09/01 13:18:34 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_is_in_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		++charset;
	}
	return (0);
}

int	ft_strlen_charset(const char *str, char *charset)
{
	int	len;

	len = 0;
	while (ft_is_in_charset(str[len], charset) == 0 && str[len])
		++len;
	return (len);
}

int	ft_print_width(int width, t_bool zero_flag, int arg_len)
{
	int		len;
	int		tmp_len;
	char	c;

	len = width - arg_len;
	tmp_len = len;
	if (zero_flag == 0)
		c = ' ';
	else
		c = '0';
	while (len-- > 0)
		write(1, &c, 1);
	return (ft_max(tmp_len, 0));
}

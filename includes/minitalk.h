/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:55:02 by smagdela          #+#    #+#             */
/*   Updated: 2021/11/25 14:47:54 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 1
# define _XOPEN_SOURCE 500

# include "ft_printf.h"
# include "libft.h"
# include <signal.h>

# define MAX_PID 4194304  /*apparently 99999 for MacOS, or 32768 for 32 bits linux, or 4194304 for 64 bits.*/
# define FALSE 0
# define TRUE 1

# ifndef TRANSMISSION_FREQ
#  define TRANSMISSION_FREQ 500
# endif

size_t	ft_nblen(int64_t nb);

#endif

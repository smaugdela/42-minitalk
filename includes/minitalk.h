/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:55:02 by smagdela          #+#    #+#             */
/*   Updated: 2021/11/25 17:57:37 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 1
# define _XOPEN_SOURCE 500

# include "ft_printf.h"
# include "libft.h"
# include <signal.h>

# define MAX_PID 4194304 
/*apparently 99999 for MacOS, 
or 32768 for 32 bits linux, 
or 4194304 for 64 bits linux.*/

# define FALSE 0
# define TRUE 1

# ifndef TRANSMISSION_FREQ
#  if defined __linux__
#   define TRANSMISSION_FREQ 10000	// 1000 < frequency < ?
#  elif defined __APPLE__
#   define TRANSMISSION_FREQ 150000	// 1000 < frequency < 150000
#  endif
# endif
/*Transmission frequency (in bits/s) is the maximum transfer rate value.
Lower it if information loss occurs,
increase it if it takes too much time to transfer.*/

size_t	ft_nblen(int64_t nb);

#endif

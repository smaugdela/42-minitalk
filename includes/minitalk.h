/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:55:02 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/01 16:24:19 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 1
# define _XOPEN_SOURCE 500

# include "ft_printf.h"
# include "libft.h"
# include <signal.h>

# define FALSE 0
# define TRUE 1

# define MAX_PID 4194304 
/*apparently 99999 for MacOS, 
or 32768 for 32 bits linux, 
or 4194304 for 64 bits linux.*/

# define DELAY 60 // in microseconds (should be < 70 us).

size_t	ft_nblen(int64_t nb);

#endif

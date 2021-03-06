/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:55:02 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/06 11:54:25 by smagdela         ###   ########.fr       */
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

# define DELAY 15
/*
In microseconds.
(should be < 70 µs, around 60 µs for linux at 42).
*/

t_bool	error_check(int argc, char **argv);

#endif

/*
sА Б В Г Ґ Д Ђ
Ѓ Е Ѐ Ё Є Ж З
З́ Ѕ И Ѝ Й І Ї
Ј К Л Љ М Н Њ
О Ō П Р С С́ Т
Ћ Ќ У Ӯ Ў Ф Х
Ц Ч Џ Ш Щ Ъ Ы
Ь Э Ю Я
*/

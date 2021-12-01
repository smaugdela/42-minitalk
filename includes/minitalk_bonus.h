/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:50:55 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/01 18:05:27 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "minitalk.h"

typedef struct s_client_info
{
	pid_t					pid;
	t_bool					metadata;
	int						i;
	size_t					s_len;
	char32_t				c;
	size_t					index_c;
	char32_t				*str;
	struct s_client_info	*next;
}	t_client_info;

t_client_info	*search_pid(t_client_info *clients, pid_t pid);

#endif

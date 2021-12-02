/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smagdela <smagdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:50:55 by smagdela          #+#    #+#             */
/*   Updated: 2021/12/02 16:24:18 by smagdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include "minitalk.h"
# include <uchar.h>

typedef struct s_client_info
{
	pid_t					pid;
	t_bool					metadata;
	int						i;
	size_t					s_len;
	int						max_str;
	char32_t				c;
	int						max_c;
	size_t					index_c;
	char32_t				*str;
	struct s_client_info	*next;
}	t_client_info;

t_client_info	*search_pid(t_client_info *clients, pid_t pid);
t_client_info	*add_client(t_client_info *clients, pid_t pid);
t_bool			del_client(t_client_info *client, t_client_info *clients);
size_t			ft_strlen_unic(char32_t *str);
void			ft_putstr_unic_fd(char32_t *str, int fd);

#endif

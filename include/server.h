/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:26:42 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/10 04:33:18 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

/* messages */
# define MSG_USAGE_SERVER     "\033[32mUsage: ./server\033[0m"
# define MSG_SERVER_CLEANUP   "\033[35m\n[SERVER] Cleanup: dead client\n\033[0m"

/* server state */
typedef struct s_server_state
{
	pid_t			active_sender_pid;
	pid_t			waiting_pid;
	int				bit_index;
	unsigned char	building_byte;
	size_t			buffer_len;
	char			buffer[BUFFER_SIZE];
}	t_server_state;

/* server */
void	handle_client_signal(int signo, siginfo_t *info, void *context);

#endif

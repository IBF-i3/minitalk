/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:26:42 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/10 04:12:04 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"

/* client timing */
# define CLIENT_POLL_US          1000
# define CLIENT_SOFT_TIMEOUT_MS  300
# define CLIENT_BUSY_BACKOFF_US  200

/* messages */
# define MSG_USAGE_CLIENT     "\033[32mUsage: ./client <pid> <message>\033[0m"
# define MSG_INVALID_PID      "\033[31mInvalid PID\033[0m"
# define MSG_SERVER_UNREACH   "\033[31mServer not reachable\033[0m"
# define MSG_SERVER_BUSY      "\033[36mSorry, server busy: waiting...\n\033[0m"

/* client wait */
typedef enum e_client_wait
{
	CLIENT_WAIT_SERVER_GONE = -1,
	CLIENT_WAIT_ACK = 0,
	CLIENT_WAIT_BUSY = 1,
	CLIENT_WAIT_NO_REPLY_YET = 2
}	t_client_wait;

/* client */
int		parse_args(int argc, char **argv,
			pid_t *out_server_pid, const char **out_message);
int		install_client_handlers(void);
int		wait_ack_or_busy(pid_t server_pid);
int		send_message(pid_t server_pid, const char *message);

#endif

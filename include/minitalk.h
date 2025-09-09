/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:26:42 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/09 16:17:47 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"

/* client -> server: data bits */
# define SIGNAL_DATA_BIT0 SIGUSR1
# define SIGNAL_DATA_BIT1 SIGUSR2

/* server -> client: control */
# define SIGNAL_CONTROL_ACK  SIGUSR1
# define SIGNAL_CONTROL_BUSY SIGUSR2

/* buffer */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8192
# endif

/* messages */
# define MSG_USAGE_SERVER     "Usage: ./server"
# define MSG_USAGE_CLIENT     "Usage: ./client <pid> <message>"
# define MSG_INVALID_PID      "Invalid PID"
# define MSG_SIGACTION_ERR    "Error: sigaction()"
# define MSG_SERVER_UNREACH   "Server not reachable."
# define MSG_SERVER_BUSY      "Sorry server busy, try again later."
# define MSG_SERVER_CLEANUP   "\n[Server] Cleaning up dead client.\n"

/* server state */
typedef struct s_server_state
{
	pid_t			active_sender_pid;
	int				bit_index;
	unsigned char	building_byte;
	size_t			buffer_len;
	char			buffer[BUFFER_SIZE];
}	t_server_state;

/* server */
void	handle_client_signal(int signo, siginfo_t *info, void *context);

/* client */
int		parse_args(int argc, char **argv,
			pid_t *out_server_pid, const char **out_message);
int		install_client_handlers(void);
int		wait_ack_or_busy(void);
int		send_message(pid_t server_pid, const char *message);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:28 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/10 04:10:01 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static volatile sig_atomic_t	g_client_sync = 0;

static void	control_handler(int signo)
{
	if (signo == SIGNAL_CONTROL_ACK)
		g_client_sync = 1;
	else
		g_client_sync = -1;
}

int	install_client_handlers(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGNAL_CONTROL_ACK);
	sigaddset(&sa.sa_mask, SIGNAL_CONTROL_BUSY);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = control_handler;
	if (sigaction(SIGNAL_CONTROL_ACK, &sa, NULL) == -1
		|| sigaction(SIGNAL_CONTROL_BUSY, &sa, NULL) == -1)
		return (-1);
	g_client_sync = 0;
	return (0);
}

int	wait_ack_or_busy(pid_t server_pid)
{
	int			waited_ms;

	waited_ms = 0;
	while (g_client_sync == 0)
	{
		if (kill(server_pid, 0) == -1)
			return (CLIENT_WAIT_SERVER_GONE);
		usleep(CLIENT_POLL_US);
		waited_ms++;
		if (waited_ms >= CLIENT_SOFT_TIMEOUT_MS)
			return (CLIENT_WAIT_NO_REPLY_YET);
	}
	if (g_client_sync < 0)
	{
		g_client_sync = 0;
		return (CLIENT_WAIT_BUSY);
	}
	g_client_sync = 0;
	return (CLIENT_WAIT_ACK);
}

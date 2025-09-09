/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:28 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/09 03:16:37 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* -1=BUSY, 0=wait, +1=ACK */
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

int	wait_ack_or_busy(void)
{
	int	timeout_counter = 0;
	const int	MAX_TIMEOUT = 5000;
	
	while (g_client_sync == 0)
	{
		usleep(1000);
		timeout_counter++;
		if (timeout_counter > MAX_TIMEOUT)
		{
			return (-1);
		}
	}
	if (g_client_sync < 0)
		return (-1);
	g_client_sync = 0;
	return (0);
}

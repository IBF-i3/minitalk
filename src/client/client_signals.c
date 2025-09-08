/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:28 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/08 03:27:16 by ibenaven         ###   ########.fr       */
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
	sa.sa_flags = 0;
	sa.sa_handler = control_handler;
	if (sigaction(SIGNAL_CONTROL_ACK, &sa, NULL) == -1
		|| sigaction(SIGNAL_CONTROL_BUSY, &sa, NULL) == -1)
		return (-1);
	g_client_sync = 0;
	return (0);
}

int	wait_ack_or_busy(void)
{
	while (g_client_sync == 0)
		pause();
	if (g_client_sync < 0)
		return (-1);
	g_client_sync = 0;
	return (0);
}

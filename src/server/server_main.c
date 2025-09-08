/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:59 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/08 01:00:48 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_server_pid(void)
{
	ft_printf("Server is ready. PID: %d\n", getpid());
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd(MSG_USAGE_SERVER, STDERR_FILENO);
		return (1);
	}
	print_server_pid();
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGNAL_DATA_BIT0);
	sigaddset(&sa.sa_mask, SIGNAL_DATA_BIT1);
	sa.sa_sigaction = handle_client_signal;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGNAL_DATA_BIT0, &sa, NULL) == -1
		|| sigaction(SIGNAL_DATA_BIT1, &sa, NULL) == -1)
	{
		ft_putstr_fd(MSG_SIGACTION_ERR, STDERR_FILENO);
		return (1);
	}
	while (1)
		pause();
}

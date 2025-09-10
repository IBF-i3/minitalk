/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:28 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/10 04:06:13 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	main(int argc, char *argv[])
{
	pid_t		server_pid;
	const char	*message;

	if (parse_args(argc, argv, &server_pid, &message) == -1)
		return (1);
	if (install_client_handlers() == -1)
	{
		ft_putendl_fd(MSG_SIGACTION_ERR, STDERR_FILENO);
		return (1);
	}
	if (send_message(server_pid, message) == -1)
	{
		ft_putendl_fd(MSG_SERVER_BUSY, STDERR_FILENO);
		return (2);
	}
	return (0);
}

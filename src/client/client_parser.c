/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:28 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/07 23:39:12 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	pid_validation(const char *str)
{
	int		i;
	pid_t	pid;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	pid = (pid_t)ft_atoi(str);
	if (pid <= 1)
		return (0);
	return (1);
}

void	parse_error(int status)
{
	if (status == 1)
		ft_putstr_fd(MSG_USAGE_CLIENT, STDERR_FILENO);
	else if (status == 2)
		ft_putstr_fd(MSG_INVALID_PID, STDERR_FILENO);
	else if (status == 3)
		ft_putstr_fd(MSG_SERVER_UNREACH, STDERR_FILENO);
}

int	parse_args(int argc, char *argv[],
		pid_t *out_server_pid, const char **out_message)
{
	int		status;
	pid_t	pid;

	status = 0;
	if (argc != 3)
		status = 1;
	else if (!pid_validation(argv[1]))
		status = 2;
	else
	{
		pid = (pid_t)ft_atoi(argv[1]);
		if (kill(pid, 0) == -1)
			status = 3;
	}
	if (status != 0)
	{
		parse_error(status);
		return (-1);
	}
	*out_server_pid = (pid_t)ft_atoi(argv[1]);
	*out_message = argv[2];
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:28 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/09 22:20:22 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	notify_busy_once(int *busy_flag)
{
	if (*busy_flag == 0)
	{
		write(STDERR_FILENO, MSG_SERVER_BUSY, sizeof(MSG_SERVER_BUSY) - 1);
		*busy_flag = 1;
	}
}

static int	send_one_bit(pid_t server_pid, int bit_value)
{
	int	signum;

	if (bit_value == 0)
		signum = SIGNAL_DATA_BIT0;
	else
		signum = SIGNAL_DATA_BIT1;
	if (kill(server_pid, signum) == -1)
		return (-1);
	return (0);
}

/* 0=ACK, 1=BUSY/soft, -1=dead */
static int	send_byte_bits(pid_t server_pid, unsigned char byte, int *busy_flag)
{
	int	bit_index;
	int	bit_value;
	int	w;

	bit_index = 0;
	while (bit_index < 8)
	{
		bit_value = (byte >> bit_index) & 1;
		if (send_one_bit(server_pid, bit_value) == -1)
			return (-1);
		while (1)
		{
			w = wait_ack_or_busy(server_pid);
			if (w == 0)
				break ;
			if (w < 0)
				return (-1);
			notify_busy_once(busy_flag);
			usleep(200);
			if (send_one_bit(server_pid, bit_value) == -1)
				return (-1);
		}
		bit_index++;
	}
	return (0);
}

int	send_message(pid_t server_pid, const char *message)
{
	int	busy_flag;

	busy_flag = 0;
	while (*message)
	{
		if (send_byte_bits(server_pid, (unsigned char)*message,
				&busy_flag) == -1)
			return (-1);
		message++;
	}
	if (send_byte_bits(server_pid, '\0', &busy_flag) == -1)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:28 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/10 04:09:01 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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

/* wait until ACK; on BUSY/soft-timeout -> backoff and resend the SAME bit */
static int	resend_until_ack(pid_t server_pid, int bit_value, int *busy_flag)
{
	int	status;

	while (1)
	{
		status = wait_ack_or_busy(server_pid);
		if (status == CLIENT_WAIT_ACK)
			return (0);
		if (status == CLIENT_WAIT_SERVER_GONE)
			return (-1);
		if (status == CLIENT_WAIT_BUSY)
			notify_busy_once(busy_flag);
		usleep(CLIENT_BUSY_BACKOFF_US);
		if (send_one_bit(server_pid, bit_value) == -1)
			return (-1);
	}
}

static int	send_byte_bits(pid_t server_pid, unsigned char byte, int *busy_flag)
{
	int	bit_index;
	int	bit_value;

	bit_index = 0;
	while (bit_index < 8)
	{
		bit_value = (byte >> bit_index) & 1;
		if (send_one_bit(server_pid, bit_value) == -1)
			return (-1);
		if (resend_until_ack(server_pid, bit_value, busy_flag) == -1)
			return (-1);
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

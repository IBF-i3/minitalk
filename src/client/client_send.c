/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:28 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/07 13:55:40 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

static int	send_byte_bits(pid_t server_pid, unsigned char byte)
{
	int	bit_index;
	int	bit_value;

	bit_index = 0;
	while (bit_index < 8)
	{
		bit_value = (byte >> bit_index) & 1;
		if (send_one_bit(server_pid, bit_value) == -1)
			return (-1);
		if (wait_ack_or_busy() == -1)
			return (-1);
		bit_index++;
	}
	return (0);
}

int	send_message(pid_t server_pid, const char *message)
{
	while (*message)
	{
		if (send_byte_bits(server_pid, (unsigned char)*message++) == -1)
			return (-1);
	}
	if (send_byte_bits(server_pid, '\0') == -1)
		return (-1);
	return (0);
}

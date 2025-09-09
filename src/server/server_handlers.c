/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:59 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/09 04:22:39 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	reset_server_state(t_server_state *state)
{
	state->active_sender_pid = 0;
	state->bit_index = 0;
	state->building_byte = 0;
	state->buffer_len = 0;
}

static void	init_server_state(t_server_state *state, pid_t sender_pid)
{
	state->active_sender_pid = sender_pid;
	state->bit_index = 0;
	state->building_byte = 0;
	state->buffer_len = 0;
}

static void	flush_buffer(t_server_state *state)
{
	if (state->buffer_len > 0)
		write(STDOUT_FILENO, state->buffer, state->buffer_len);
	state->buffer_len = 0;
}

/* append/flush data bytes; on '\0' flush remainder, newline, and reset */
static void	handle_full_byte(t_server_state *state)
{
	if (state->building_byte == '\0')
	{
		flush_buffer(state);
		write(STDOUT_FILENO, "\n", 1);
		state->active_sender_pid = 0;
		state->bit_index = 0;
		state->building_byte = 0;
		return ;
	}
	if (state->buffer_len == BUFFER_SIZE)
		flush_buffer(state);
	state->buffer[state->buffer_len++] = (char)state->building_byte;
	state->building_byte = 0;
	state->bit_index = 0;
}

/* one-client-at-a-time, ACK each bit, chunked output, newline at '\0' */
void	handle_client_signal(int signo, siginfo_t *info, void *context)
{
	static t_server_state	state;
	pid_t					sender_pid;

	(void)context;
	sender_pid = info->si_pid;
	if (state.active_sender_pid != 0 && kill(state.active_sender_pid, 0) == -1)
	{
		ft_putendl_fd(MSG_SERVER_CLEANUP, STDERR_FILENO);
		reset_server_state(&state);
	}
	if (state.active_sender_pid == 0)
		init_server_state(&state, sender_pid);
	if (sender_pid != state.active_sender_pid)
	{
		kill(sender_pid, SIGNAL_CONTROL_BUSY);
		return ;
	}
	if (signo == SIGNAL_DATA_BIT1)
		state.building_byte |= (1u << state.bit_index);
	state.bit_index++;
	kill(sender_pid, SIGNAL_CONTROL_ACK);
	if (state.bit_index == 8)
		handle_full_byte(&state);
}

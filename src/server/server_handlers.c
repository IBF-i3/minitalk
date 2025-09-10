/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:25:59 by ibenaven          #+#    #+#             */
/*   Updated: 2025/09/10 04:56:16 by ibenaven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

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
		if (state->waiting_pid != 0)
		{
			init_server_state(state, state->waiting_pid);
			state->waiting_pid = 0;
		}
		else
			reset_server_state(state);
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

	(void)context;
	if (state.active_sender_pid != 0 && kill(state.active_sender_pid, 0) == -1)
	{
		write(STDERR_FILENO, MSG_SERVER_CLEANUP,
			sizeof(MSG_SERVER_CLEANUP) - 1);
		reset_server_state(&state);
	}
	if (state.active_sender_pid == 0)
		init_server_state(&state, info->si_pid);
	if (info->si_pid != state.active_sender_pid)
	{
		kill(info->si_pid, SIGNAL_CONTROL_BUSY);
		if (state.waiting_pid == 0)
			state.waiting_pid = info->si_pid;
		return ;
	}
	if (signo == SIGNAL_DATA_BIT1)
		state.building_byte |= (1u << state.bit_index);
	state.bit_index++;
	kill(info->si_pid, SIGNAL_CONTROL_ACK);
	if (state.bit_index == 8)
		handle_full_byte(&state);
}

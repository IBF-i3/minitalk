# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibenaven <ibenaven@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/23 15:42:55 by ibenaven          #+#    #+#              #
#    Updated: 2025/09/10 09:32:54 by ibenaven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER	:= server
NAME_CLIENT	:= client

DIR_SERVER	:= src/server
DIR_CLIENT	:= src/client

SRC_SERVER	:= \
			server_main.c \
			server_handlers.c

SRC_CLIENT	:= \
			client_main.c \
			client_parser.c \
			client_signals.c \
			client_send.c

LIBFT	:= libft
LIBFT_A	:= $(LIBFT)/libft.a

INCLUDE := -Iinclude -I$(LIBFT)/include

COMPILER		:= cc
COMPILERFLAGS	?= -Wextra -Wall -Werror	 

SHELL := /bin/bash

ifeq ($(DEBUG), 1)
COMPILERFLAGS	+= -g
endif	 

VG		:= valgrind
VGFLAGS	:= \
		--leak-check=full \
		--show-leak-kinds=all \
		-s

OUTPUT_SERVER	:= src/server/output
OUTPUT_CLIENT	:= src/client/output
OBJS_SERVER		:= $(patsubst %.c, $(OUTPUT_SERVER)/%.o, $(SRC_SERVER))
OBJS_CLIENT		:= $(patsubst %.c, $(OUTPUT_CLIENT)/%.o, $(SRC_CLIENT))

$(OUTPUT_SERVER)/%.o: $(DIR_SERVER)/%.c 
	mkdir -p $(OUTPUT_SERVER)
	$(COMPILER) $(COMPILERFLAGS) $(INCLUDE) -c $< -o $@
 
$(OUTPUT_CLIENT)/%.o: $(DIR_CLIENT)/%.c 
	mkdir -p $(OUTPUT_CLIENT)
	$(COMPILER) $(COMPILERFLAGS) $(INCLUDE) -c $< -o $@


all: libft
	make $(NAME_SERVER)
	make $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT_A) 
	$(COMPILER) $(COMPILERFLAGS) $(OBJS_SERVER) $(LIBFT_A) -o $(NAME_SERVER) 

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT_A) 
	$(COMPILER) $(COMPILERFLAGS) $(OBJS_CLIENT) $(LIBFT_A) -o $(NAME_CLIENT) 

libft:
	make -C $(LIBFT) all

clean:
	make -C $(LIBFT) clean
	rm -rf $(OUTPUT_SERVER)
	rm -rf $(OUTPUT_CLIENT)

fclean: clean
	make -C $(LIBFT) fclean
	rm -f $(NAME_SERVER)
	rm -f $(NAME_CLIENT)

re: fclean all

leaks_server:
	make fclean && make DEBUG=1
	$(VG) $(VGFLAGS) ./$(NAME_SERVER)

leaks_client:
	@if [ -z "$(PID)" ] || [ -z "$(MSG)" ]; \
	then echo "Usage: make leaks_client PID=<server_pid> MSG='text'"; \
	exit 1; fi
	make fclean && make DEBUG=1
	$(VG) $(VGFLAGS) ./$(NAME_CLIENT) $(PID) "$(MSG)"

.PHONY: all libft clean fclean re leaks_server leaks_client

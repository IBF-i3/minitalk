# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibenaven <ibenaven@student.42madrid.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/13 17:15:56 by ibenaven          #+#    #+#              #
#    Updated: 2025/08/15 22:48:38 by ibenaven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

INCLUDE := -Iinclude

COMPILER = cc
CCFLAGS = -Wall -Wextra -Werror

AR = ar
ARFLAGS = -r -c -s

LIBFT_SRC = ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_calloc.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_atol.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_uitoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c

FT_PRINTF_SRC := ft_printf.c \
				 ft_print_text.c \
				 ft_print_nbr.c				

GNL_SRC := get_next_line.c

LIBFT_H = include/libft.h
FT_PRINTF_H = include/ft_printf.h
GNL_H = include/get_next_line.h

OUTPUT := src/output
LIBFT_OUTPUT := $(OUTPUT)/libft
FT_PRINTF_OUTPUT := $(OUTPUT)/ft_printf
GNL_OUTPUT := $(OUTPUT)/gnl

LIBFT_O = $(patsubst %.c, $(LIBFT_OUTPUT)/%.o, $(LIBFT_SRC))
FT_PRINTF_O = $(patsubst %.c, $(FT_PRINTF_OUTPUT)/%.o, $(FT_PRINTF_SRC))
GNL_O = $(patsubst %.c, $(GNL_OUTPUT)/%.o, $(GNL_SRC))

$(LIBFT_OUTPUT)/%.o: src/libft/%.c $(LIBFT_H)
	mkdir -p $(OUTPUT) $(LIBFT_OUTPUT)
	$(COMPILER) $(CCFLAGS) $(INCLUDE) -c $< -o $@

$(FT_PRINTF_OUTPUT)/%.o: src/ft_printf/%.c $(FT_PRINTF_H)
	mkdir -p $(OUTPUT) $(FT_PRINTF_OUTPUT)
	$(COMPILER) $(CCFLAGS) $(INCLUDE) -c $< -o $@

$(GNL_OUTPUT)/%.o: src/gnl/%.c $(GNL_H)
	mkdir -p $(OUTPUT) $(GNL_OUTPUT)
	$(COMPILER) $(CCFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(LIBFT_O) $(FT_PRINTF_O) $(GNL_O)
	$(AR) $(ARFLAGS) $(NAME) $(LIBFT_O) $(FT_PRINTF_O) $(GNL_O)

all: $(NAME)

clean:
	rm -rf $(OUTPUT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

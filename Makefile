# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yojin <yojin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 17:18:23 by yojin             #+#    #+#              #
#    Updated: 2024/05/20 19:03:33 by yojin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = 
LDIR = ./
FT_PRINTF = libftprintf.a
FT_PRINTF_DIR = ./ft_printf
HEADER = ./pipex.h
SRCS = pipex.c parse.c pipex_util.c debug.c
OBJS = $(SRCS:.c=.o)
NAME = pipex

all: $(NAME)

$(NAME): $(OBJS)
	make -j 8 -C $(FT_PRINTF_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -I$(LDIR) $(FT_PRINTF_DIR)/$(FT_PRINTF)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(LDIR)

re: fclean all

clean:
	make -C $(FT_PRINTF_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(FT_PRINTF_DIR) fclean
	rm -f $(NAME)

.PHONY: all re clean fclean

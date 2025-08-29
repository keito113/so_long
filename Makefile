# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keitabe <keitabe@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/29 09:18:03 by keitabe           #+#    #+#              #
#    Updated: 2025/08/29 12:28:33 by keitabe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = so_long

CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx.a

INCLUDES    = -I. -I$(LIBFT_DIR) -I$(MLX_DIR)

SRCS        = so_long.c map_parser.c map_fill.c map_utils.c map_validator.c validate_path.c graphics.c movement.c handle_key.c game_end.c game_end_utils.c enemy_move.c enemy_move_utils.c cleanup_graphics.c handle_error.c textures.c

OBJS        = so_long.o map_parser.o map_fill.o map_utils.o map_validator.o validate_path.o graphics.o movement.o handle_key.o game_end.o game_end_utils.o enemy_move.o enemy_move_utils.o cleanup_graphics.o handle_error.o textures.o


all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIBFT) $(MLX_LIB) -lXext -lX11 -lm

%.o: %.c so_long.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)
		@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
		@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 16:21:03 by franmart          #+#    #+#              #
#    Updated: 2023/03/18 14:29:09 by franmart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc
FLAGS = -Wall -Wextra -Werror -O2 #-g3
RM = rm -rf

MLX42 = lib/MLX42/libmlx42.a
MLX42_DIR = lib/MLX42

LIBFT = lib/libft/libft.a
LIBFT_DIR = lib/libft

INCLUDES = -ldl -lglfw -pthread -lm

SRC_DIR = src/
_SRC = 	map.c\
		colors.c\
		camera.c\
		geometry.c\
		map_utils.c\
		hooks.c\
		draw.c\
		bonus.c\
		draw_utils.c\
		error.c\
		main.c

SRC = $(addprefix $(SRC_DIR), $(_SRC))

OBJ = $(SRC:.c=.o)

${NAME}: ${OBJ}
	$(MAKE) all -C $(MLX42_DIR)
	$(MAKE) all -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(MLX42) $(LIBFT) $(INCLUDES)

%.o: %.c
	${CC} ${FLAGS} -c $^ -o $@

all: ${NAME}

clean:
		$(MAKE) clean -C $(MLX42_DIR)
		$(MAKE) clean -C $(LIBFT_DIR)
		${RM} ${OBJ}

fclean: clean
		$(MAKE) fclean -C $(MLX42_DIR)
		$(MAKE) fclean -C $(LIBFT_DIR)
		${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re

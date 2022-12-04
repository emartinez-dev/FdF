# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: franmart <franmart@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 16:21:03 by franmart          #+#    #+#              #
#    Updated: 2022/12/04 16:05:47 by franmart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc 
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

MLX42 = MLX42/libmlx42.a
MLX42_DIR = MLX42/

SRC = main.c

OBJ = $(SRC:.c=.o)

${NAME}: ${OBJ}
	$(MAKE) all -C $(MLX42_DIR)
	$(CC) $(MLX42) $(OBJ) -o $(NAME) -ldl -lglfw -pthread -lm -I MLX42/include 

%.o: %.c
	${CC} ${FLAGS} -c $^ -o $@

all: ${NAME}

clean:
		$(MAKE) clean -C $(MLX42_DIR)
		${RM} ${OBJ}

fclean: clean
		$(MAKE) fclean -C $(MLX42_DIR)
		${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re


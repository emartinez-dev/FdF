# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: franmart <franmart@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/11 16:21:03 by franmart          #+#    #+#              #
#    Updated: 2022/12/04 20:49:37 by franmart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc 
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

MLX42 = MLX42/libmlx42.a
MLX42_DIR = MLX42/

INCLUDES = -ldl -lglfw -pthread -lm 

SRC = main.c

OBJ = $(SRC:.c=.o)

${NAME}: ${OBJ}
	$(MAKE) all -C $(MLX42_DIR)
	$(CC) $(OBJ) -o $(NAME) $(MLX42) $(INCLUDES)

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


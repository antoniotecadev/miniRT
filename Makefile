# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ateca <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 16:26:02 by ateca             #+#    #+#              #
#    Updated: 2025/05/07 12:06:37 by ateca            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC = source/main.c \
		source/scene/read_scene.c \
		source/scene/ambient_light.c \
		source/scene/light.c \
		source/scene/camera.c \
		source/scene/sphere.c \
		source/scene/cylinder.c \
		source/scene/plane.c \
		source/scene/get_color.c \
		source/scene/get_position.c \
		source/vector/vec3_length.c \
		source/vector/vec3_normalize.c \
		source/util/object_utils.c \
		source/util/free_utils.c \
		source/util/tokens_utils.c 
OBJ = ${SRC:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft/include

LIBFT = ./libft/libft.a
LIBFTSRC = ./libft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) -lm
	
$(LIBFT):
	@make -C $(LIBFTSRC)

clean:
	rm -f $(OBJ)
	@make clean -C $(LIBFTSRC)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFTSRC)

re: fclean all

.PHONY: all clean fclean re

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
		source/util/object_utils.c \
		source/util/vec3_utils.c \
		source/util/vec3_utils_extra.c \
		source/util/free_utils.c \
		source/util/tokens_utils.c \
		source/render/render_scene.c \
		source/render/get_ray_direction.c \
		source/render/ray_trace.c \
		source/intersect/intersect_sphere.c \
		source/intersect/shade_sphere.c \
		source/win/events.c
OBJ = ${SRC:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = ./libft/libft.a
LIBFTSRC = ./libft

MLX = ./minilibx/libmlx.a
MLXSRC = ./minilibx

LIBRARIES = -L$(MLXSRC) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBRARIES) -o $(NAME) $(LIBFT) $(MLX)
	
$(MLX):
	@make -C $(MLXSRC)

$(LIBFT):
	@make -C $(LIBFTSRC)

clean:
	rm -f $(OBJ)
	@make clean -C $(LIBFTSRC)
	@make clean -C $(MLXSRC)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFTSRC)
	@make clean -C $(MLXSRC)

re: fclean all

.PHONY: all clean fclean re

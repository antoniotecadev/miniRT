# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ateca <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 16:26:02 by ateca             #+#    #+#              #
#    Updated: 2025/04/03 16:42:46 by ateca            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC = ./source/main.c
OBJ = ${SRC:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft/include

LIBFT = ./libft/libft.a
LIBFTSRC = ./libft

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)
	
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

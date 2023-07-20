# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmatas-p <jmatas-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 18:11:17 by jmatas-p          #+#    #+#              #
#    Updated: 2023/07/20 18:19:07 by jmatas-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC =   main.c utils.c
			
OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) compiled"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@echo "Project cleaned"

re: fclean all

.PHONY: all clean fclean re bonus
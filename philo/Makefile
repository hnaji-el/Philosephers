# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 10:01:14 by hnaji-el          #+#    #+#              #
#    Updated: 2021/11/19 01:23:50 by hnaji-el         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./srcs/main.c \
	   ./srcs/philo_utils.c \
	   ./srcs/parsing.c

INCLUDES = ./includes/philo.h

COMPILER = cc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS) $(INCLUDES)
	@$(COMPILER) $(FLAGS) -g -fsanitize=address $(SRCS) -o $(NAME) 

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

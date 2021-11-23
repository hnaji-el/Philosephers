# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/16 10:01:14 by hnaji-el          #+#    #+#              #
#    Updated: 2021/11/23 04:13:34 by hnaji-el         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = ./srcs/main.c \
	   ./srcs/create_threads.c \
	   ./srcs/create_lst.c \
	   ./srcs/philo_utils.c \
	   ./srcs/parsing.c \
	   ./srcs/circular_lst.c \
	   ./srcs/start_routine.c \
	   ./srcs/correct_usleep.c \
	   ./srcs/controller.c \
	   ./srcs/timer.c

INCLUDES = ./includes/philo.h

COMPILER = cc

FLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(SRCS) $(INCLUDES)
	@$(COMPILER) $(FLAGS) $(SRCS) -o $(NAME) 

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

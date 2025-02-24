# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 18:02:49 by yfradj            #+#    #+#              #
#    Updated: 2025/02/24 11:50:07 by yfradj           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -pthread -Wall -Werror -Wextra

WAY = srcs/

SRCS = \
	$(WAY)error.c \
	$(WAY)free_destroy.c \
	$(WAY)init.c \
	$(WAY)main.c \
	$(WAY)routine.c \
	$(WAY)routine2.c \
	$(WAY)utils.c \
	
OBJS = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	
clean:
	@rm -f $(OBJS)
	
fclean: clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all fclean clean bonus re

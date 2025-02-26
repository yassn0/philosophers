# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 18:02:49 by yfradj            #+#    #+#              #
#    Updated: 2025/02/26 12:20:25 by yfradj           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -pthread -Wall -Werror -Wextra
# -fsanitize=thread
WAY = srcs/

SRCS = \
	$(WAY)error.c \
	$(WAY)free_destroy.c \
	$(WAY)init.c \
	$(WAY)main.c \
	$(WAY)routine.c \
	$(WAY)monitor.c \
	$(WAY)utils.c \
	$(WAY)utils2.c \
	
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

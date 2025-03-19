# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 14:18:03 by tlupu             #+#    #+#              #
#    Updated: 2024/11/08 17:36:24 by tlupu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers
CC = gcc
CFLAGZ = -Wall -Wextra -Werror -lpthread
SRCS = 	main.c error_handling.c philo_starting.c utils.c forks.c\
		death_full_checks.c message.c routine.c simulation.c time.c \

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGZ) -g -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGZ) -o $(NAME) $(OBJS) 


clean:
	rm -f $(OBJS) 
	rm -f $(OBJSBON)

fclean: clean
	rm -f $(NAME) $(B_NAME)
	
re: fclean all
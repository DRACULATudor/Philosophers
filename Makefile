NAME = philo
CC = gcc -fsanitize=address
CFLAGZ = -Wall -Wextra -Werror -lpthread
SRCS = 	main.c utils.c routine.c forks_eating_updates.c\
		clock_death_full_check.c errors_and_starting.c\
		create_join_monitor.c death_full_check2.c clean.c\

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
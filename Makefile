NAME = philosophers
CC = gcc
CFLAGZ = -Wall -Wextra -Werror -pthread
SRCS = main.c utils.c

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
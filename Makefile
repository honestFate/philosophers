CC = gcc
INC = .
SRC = ./sources/
C		= gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = philosophers.h

NAME = philo

SRCS =	philosophers.c initialization.c living.c \
		utils.c philo_check.c free_at_exit.c

OBJS	= $(SRCS:%.c=%.o)

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) -I$(INC)

%.o: $(SRC)%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

clean:	
		rm -rf ${OBJS}

fclean:	clean
		rm -rf $(NAME)

re: clean all

.PHONY:	all clean fclean re
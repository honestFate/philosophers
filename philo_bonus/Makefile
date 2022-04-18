CC = gcc
INC = .
SRC = ./sources/
OBJ = ./obj/
C = gcc
CFLAGS = -g -Wall -Wextra -Werror
INCLUDES = philosophers.h

NAME = philo

SRCS =	philosophers.c initialization.c living.c \
		utils.c philo_check.c free_at_exit.c

OBJS = $(addprefix $(OBJ), $(SRCS:%.c=%.o))

all:	$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) -I$(INC)

$(OBJ)%.o: $(SRC)%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:	
	rm -rf ${OBJS}

fclean:	clean
	rm -rf $(NAME)

re: clean all

.PHONY:	all clean fclean re
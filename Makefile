CC = gcc
INC = .
SRC = ./sources/
INCLUDES = philosophers.h
CFLAGS = -Wall -Wextra -Werror

NAME = philosophers

SRCS =	$(SRC)philosophers.c $(SRC)initialization.c $(SRC)living.c \
		$(SRC)utils.c

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

%.o: 
	${CC} ${CFLAGS} -c -I${INC} $(@:%.o=%.c) -o $@

$(NAME): $(OBJS)
	${CC} ${CFLAGS} -I${INC} -o ${NAME} $?

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY : all clean fclean re
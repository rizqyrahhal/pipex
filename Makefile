NAME = pipex
FLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = 	pipex.c \
		childs.c \
		utils.c \
		error.c \



OBJS = $(SRCS:.c=.o)


$(NAME): $(OBJS)
		$(CC) $(FLAGS) -c $(SRCS)
		ar rc $(NAME) $(OBJS)

all:	$(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean
	make all


.PHONY: all clean fclean re

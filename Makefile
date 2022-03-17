NAME = pipex
FLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = 	Mandatory/pipex.c \
		Mandatory/childs.c \
		Mandatory/error.c \
		libft/ft_split.c \
		libft/ft_strjoin.c \
		libft/ft_strlen.c \
		libft/ft_strncmp.c \
		libft/ft_strnstr.c \


$(NAME):
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)
	@rm -f outfile

re: fclean
	@make all


.PHONY: all clean fclean re

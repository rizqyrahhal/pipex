NAME = pipex
FLAGS = -Wall -Werror -Wextra
CC = cc


SRCS = 	Mandatory/pipex.c \
		Mandatory/childs.c \
		Mandatory/error.c \

BONUS_SRCS =	bonus/pipex_bonus.c \
				bonus/error.c \
				bonus/child.c \
				bonus/files.c \
				bonus/here_doc.c \
				bonus/get_next_line.c \

LIBFT = libft/ft_split.c \
		libft/ft_strjoin.c \
		libft/ft_strlen.c \
		libft/ft_strncmp.c \
		libft/ft_strnstr.c \
		libft/ft_calloc.c \
		libft/ft_strchr.c \


$(NAME):
	@$(CC) $(FLAGS) $(SRCS) $(LIBFT) -o $(NAME)

all: $(NAME)

bonus:
	@$(CC) $(FLAGS) $(BONUS_SRCS) $(LIBFT) $(GNL) -o $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)
	@rm -f outfile .temporere infile ; touch infile

re: fclean
	@make all


.PHONY: all bonus clean fclean re

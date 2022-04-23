# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 17:40:58 by rarahhal          #+#    #+#              #
#    Updated: 2022/04/23 13:07:40 by rarahhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

OBJS = $(SRCS:.c=.o)
OBJS_L = $(LIBFT:.c=.o)
OBJS_B = $(BONUS_SRCS:.c=.o)

$(NAME): $(OBJS) $(OBJS_L)
	$(CC) $(FLAGS) $(OBJS) $(OBJS_L) -o $(NAME)

all: $(NAME)

bonus: $(OBJS_B) $(OBJS_L)
	$(CC) $(FLAGS) $(OBJS_B) $(OBJS_L) -o $(NAME)

clean:
	@rm -f bonus/*.o
	@rm -f libft/*.o
	@rm -f Mandatory/*.o

fclean: clean
	@rm -f $(NAME)
	@rm -f outfile

re: fclean
	@make all


.PHONY: all bonus clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 11:26:00 by rarahhal          #+#    #+#              #
#    Updated: 2022/03/15 13:53:04 by rarahhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
FLAGS = -Wall -Wextra -Werror
CC = cc

SRCS = pipex.c \
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

fclean:	clean
		rm -f $(NAME)

re: fclean
	make all

delet: 
		rm outfile.txt

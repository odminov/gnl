#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 18:29:03 by ahonchar          #+#    #+#              #
#    Updated: 2018/02/22 15:47:15 by ahonchar         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = gnl
SRC = main.c get_next_line.c
OBJ = main.o get_next_line.o
FLAGS = -Wextra -Wall -Werror

%.o:%.c
	gcc $(FLAGS) -c $^

All: $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ)  -L ./libft/ -lft 
clean:
	rm -rf *.o
	rm -rf *~
fclean: clean
	rm -rf $(NAME)
re: fclean All

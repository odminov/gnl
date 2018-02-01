#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 18:29:03 by ahonchar          #+#    #+#              #
#    Updated: 2018/01/25 18:33:15 by ahonchar         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = test
SRC = main.c
OBJ = main.o
FLAGS = -Wextra -Wall -Werror

$(NAme)

%.o:%.c
	gcc $(FLAGS) -c $^

All: $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) -L ~/done/libft/libft.a
clean:
	rm -rf *.o
	rm -rf *~
fclean: clean
	rm -rf test
re: fclean All

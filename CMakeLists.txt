cmake_minimum_required(VERSION 3.9)
project(some)

set(CMAKE_CXX_STANDARD 11)

include_directories(/Users/ahonchar/done/libft/)

add_executable(some
        main.c
        /Users/ahonchar/done/libft/ft_lstadd.c
        /Users/ahonchar/done/libft/ft_lstnew.c
        /Users/ahonchar/done/libft/ft_memcpy.c
        /Users/ahonchar/done/libft/ft_strlen.c
        /Users/ahonchar/done/libft/ft_strchr.c
        /Users/ahonchar/done/libft/ft_strjoin.c
        /Users/ahonchar/done/libft/ft_strnew.c
        /Users/ahonchar/done/libft/ft_memset.c
        /Users/ahonchar/done/libft/ft_strdup.c
        /Users/ahonchar/done/libft/ft_strcpy.c
        /Users/ahonchar/done/libft/ft_strncpy.c
        /Users/ahonchar/done/libft/ft_strclr.c
        /Users/ahonchar/test/get_next_line.c)

cmake_minimum_required(VERSION 3.9)
project(some)

set(CMAKE_CXX_STANDARD 11)

include_directories(/Users/ahonchar/done/libft/)

add_executable(some
        main.c
        /Users/ahonchar/done/libft/ft_lstadd.c
        /Users/ahonchar/done/libft/ft_lstnew.c
        /Users/ahonchar/done/libft/ft_memcpy.c
        /Users/ahonchar/done/libft/ft_strlen.c)

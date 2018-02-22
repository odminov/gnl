/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2018/02/02 00:06:48 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/libft.h"
//
#include <fcntl.h>
#include <stdio.h>

#define BUFF_SIZE 30

int read_from_buff(t_gnl *list, char **line)
{
    char    *nl;
    char    *temp;
    char    *temp2;

    temp = *line;
    //temp = NULL;
    if (!(nl = ft_strchr(list->buff, '\n')))
    {
        if (!(*line = ft_strjoin(*line, list->buff)))
            return (-1);
        free(temp);
        return (0);
    }
    else
    {
        *nl = '\0';
        nl++;
        if (!(*line = ft_strjoin(*line, list->buff)))
            return (-1);
        free(temp);
        if (!(temp2 = ft_strnew(BUFF_SIZE)))
            return (-1);
        ft_strncpy(temp2, nl, BUFF_SIZE);
        free(list->buff);
        list->buff = temp2;
    }
    return (1);
}

int     read_line(t_gnl *list, char **line)
{
    int     read_buff;

    if (list->read_compleate)
        return (list->read_compleate = 0);
    if (*line && **line)
        free(*line);
    *line = NULL;
    if (!(*line = ft_strnew(0)))
        return (-1);
    while (1)
    {
        if (*list->buff)
        {
            read_buff = read_from_buff(list, line);
            if (read_buff == 1 || read_buff == -1)
                return (read_buff);
            ft_strclr(list->buff);
        }
        if ((read(list->fd, list->buff, BUFF_SIZE)) == 0)
        {
            list->read_compleate = 1;
            return (1);
        }
    }
}

t_gnl   *new_list_elem(int fd, char *buff, t_gnl *list)
{
    t_gnl *temp;

    if (!list)
    {
        if (!(list = (t_gnl *)malloc(sizeof(list))))
            return (NULL);
    }
    else
    {
        if (!(temp = (t_gnl *)malloc(sizeof(temp))))
            return (NULL);
        temp->next = list;
        list = temp;
    }
    list->buff = buff;
    list->temp = NULL;
    list->fd = fd;
    list->read_compleate = 0;
    list->next = NULL;
    return (list);
}



int     get_next_line(const int fd, char **line)
{
    static t_gnl *open_files;
    t_gnl *temp;

    if (!line || fd < 0 || !BUFF_SIZE || (read(fd, NULL, 0) == -1))
        return (-1);
    if (!open_files)
    {
        if (!(open_files = new_list_elem(fd, ft_strnew(BUFF_SIZE), open_files)))
            return (-1);
    }
    else
    {
        temp = open_files;
        while (open_files)
        {
            if (open_files->fd == fd)
                return (read_line(open_files, line));
            open_files = open_files->next;
        }
        open_files = temp;
        if (!(open_files = new_list_elem(fd, ft_strnew(BUFF_SIZE), open_files)))
            return (-1);
    }
    return (read_line(open_files, line));
}

int     main(void)
{
    int     i;
    char    *out;
    int     fd;

    i = 0;
    fd = open("/users/ahonchar/test/file1", O_RDONLY);
    if (fd < 3)
        return (printf("invalid file, open = %d\n", fd));
    while (get_next_line(fd, &out) > 0)
    {
        printf("%s\n", out);
    }
    close(fd);
    free(out);
    //system("leaks -quiet gnl");
    return (0);
}

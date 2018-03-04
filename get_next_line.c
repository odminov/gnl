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
#include <stdio.h>//

static int my_exit(char **line)
{
    free(*line);
    *line = NULL;
    return (0);
}

static int read_from_buff(t_gnl *list, char **line)
{
    char    *nl;
    char    *temp;

    temp = *line;
    if (!(nl = ft_strchr(list->buff, '\n')))
    {
        if (!(*line = ft_strjoin(*line, list->buff)))
            return (-1);
        free(temp);
        return (0);
    }
    *nl = '\0';
    nl++;
    if (!(*line = ft_strjoin(*line, list->buff)))
        return (-1);
    free(temp);
    if (*nl)
    {
        temp = ft_strnew(ft_strlen(nl));
        ft_memmove(temp, nl, ft_strlen(nl));
        ft_memmove(list->buff, temp, BUFF_SIZE);
        free(temp);
    }
    return (1);
}

static int     read_line(t_gnl *list, char **line)
{
    int     ret;

    if (!(*line = ft_strnew(0)))
        return (-1);
    while (1)
    {
        if (*list->buff)
        {
            ret = read_from_buff(list, line);
            if (ret)
                return(ret);
            ft_strclr(list->buff);
        }
	    if (!(ret = read(list->fd, list->buff, BUFF_SIZE)))
        {
            if (**line)
                return (1);
            else
                return (my_exit(line));
        }
        list->buff[ret] = '\0';
    }
}

static t_gnl   *new_list_elem(int fd)
{
    t_gnl   *list;

    if (!(list = (t_gnl *)malloc(sizeof(list))))
        return (NULL);
    list->next = NULL;
    list->buff = ft_strnew(BUFF_SIZE);
    list->fd = fd;
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
        if (!(open_files = new_list_elem(fd)))
            return (-1);
    }
	temp = open_files;
    while ((temp->fd != fd) && temp->next)
        temp = temp->next;
    if ((temp->fd) != fd)
    {
        if (!(temp->next = new_list_elem(fd)))
            return (-1);
        temp = temp->next;
    }
    return (read_line(temp, line));
}

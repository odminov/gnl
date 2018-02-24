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

static int my_exit(t_gnl *list, char **line, int ret)
{
    if (list->read_compleate)
        list->read_compleate = 0;
    free(*line);
    *line = NULL;
    return (ret);
}

static int read_from_buff(t_gnl *list, char **line)
{
    char    *nl;
    char    *temp;
	char    *temp_buf;

    temp = *line;
    temp_buf = ft_strnew(BUFF_SIZE);
    temp_buf = ft_strncpy(temp_buf, list->buff, BUFF_SIZE);
    if (!(nl = ft_strchr(temp_buf, '\n')))
    {
        if (!(*line = ft_strjoin(*line, temp_buf)))
            return (-1);
        free(temp);
	    free(temp_buf);
        return (0);
    }
    else
    {
        *nl = '\0';
        nl++;
        if (!(*line = ft_strjoin(*line, temp_buf)))
            return (-1);
        free(temp);
        free(temp_buf);        
        ft_strncpy(list->buff, nl, BUFF_SIZE);
    }
    return (1);
}

static int     read_line(t_gnl *list, char **line)
{
    int     read_buff;
    int     ret;
	int     i;

    ret = i = 0;
    if (!list->buff)
        if (!(list->buff = ft_strnew(BUFF_SIZE)))
            return (-1);
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
            if (list->read_compleate)
                return (1);
        }     

	    if ((ret = read(list->fd, list->buff, BUFF_SIZE)) >= 0)
        {
            if (!ret && !*(list->buff))
                return (my_exit(list, line, 0));
            if (ret < BUFF_SIZE)
                list->read_compleate = 1;
        }
    }
}

static t_gnl   *new_list_elem(int fd, t_gnl *list)
{
    if (!(list = (t_gnl *)malloc(sizeof(list))))
        return (NULL);
    list->next = NULL;
    list->buff = NULL;
    list->fd = fd;
    list->read_compleate = 0;
    return (list);
}

int     get_next_line(const int fd, char **line)
{
	t_gnl   *glob;
    static t_gnl *open_files;
    t_gnl *temp;

    if (!line || fd < 0 || !BUFF_SIZE || (read(fd, NULL, 0) == -1))
        return (-1);
    if (!open_files)
    {
        if (!(open_files = new_list_elem(fd, open_files)))
            return (-1);
    }
	glob = open_files;
	temp = open_files;
    while ((temp->fd != fd) && temp->next)
        temp = temp->next;
    if ((temp->fd) != fd)
    {
        if (!(temp->next = new_list_elem(fd, temp)))
            return (-1);
        temp = temp->next;
    }
    return (read_line(temp, line));
}

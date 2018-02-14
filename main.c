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

#define BUFF_SIZE 10

static int read_from_buff(char *buff, char *out)
{
    char *nl;
    char *before_nl;
    char *temp;

    temp = NULL;
    if (!(nl = ft_strchr(buff, '\n')))
    {
        if (!(out = ft_strjoin(out, buff)))
            return (-1);
        return (0);
    }
    else {
        *nl = '\0';
        nl++;
        if (!(before_nl = ft_strdup(buff)))
            return (-1);
        if (!(out = ft_strjoin(out, before_nl)))
            return (-1);
        if (*nl)
        {
            if (!(temp = (char *)malloc(sizeof(temp) * ft_strlen(nl) + 1)))
                return (-1);
            ft_strcpy(buff, nl);
        }
        free(buff);
        buff = temp;
        free(before_nl);
    }
    return (1);
}

// static del_list_elem(list)
// {
//     t_gnl *temp;

//     temp = list;
//     while 
// }

int		read_line(t_gnl *list, char *out)
{
    char    *temp_buf;
    int     read_buff;

    if (list->read_compleate)
    {
       // del_list_elem(list);
        return (0);
    }
    if (*out)
        free(out);
    if (!(out = ft_strnew(0)))
        return (-1);
    while (1)
    {
        if (*list->buff)
        {
            read_buff = read_from_buff(list->buff, out);
            if (read_buff == 1)
                return (1);
            else if (read_buff == -1)
                return (-1);
            else
            {
                temp_buf = list->buff;
                list->buff = ft_strnew(BUFF_SIZE);
                free(temp_buf);
            }
        }
        if ((read(list->fd, list->buff, BUFF_SIZE)) < BUFF_SIZE)
        {
            if (read_from_buff(list->buff, out) < 0)
                return (-1);
            list->read_compleate = 1;
            return (1);
        }

    }
}

static t_gnl   *new_list_elem(int fd, char *buff, t_gnl *list)
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



int		get_next_line(const int fd, char **line)
{
	static t_gnl *open_files;
	t_gnl *temp;

	if (!(*line) || fd < 0 || !BUFF_SIZE || (read(fd, NULL, 0) == -1))
		return (-1);
    if (!open_files)
    {
        if (!(open_files = new_list_elem(fd, ft_strnew(BUFF_SIZE), open_files)))
            return (-1);
    }
    else
    {
        temp = open_files;
        while (temp)
        {
            if (temp->fd == fd)
                return (read_line(temp, *line));
            temp = temp->next;
        }
        if (!(open_files = new_list_elem(fd, ft_strnew(BUFF_SIZE), open_files)))
            return (-1);
    }
    return (read_line(open_files, *line));
}

int		main(void)
{
	int		i;
	char	*out;
	int		fd;

	i = 0;
	fd = open("./file1", O_RDONLY);
	if (fd < 3)
		return (printf("invalid file, open = %d\n", fd));
	while (get_next_line(fd, &out) > 0)
 		printf("%s\n", out);
	close(fd);
	free(out);
	system("leaks -quiet gnl");
	return (0);
}

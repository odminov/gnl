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

int		read_line(t_gnl *list, char *out)
{
    char    *temp;
    char    *temp_buf;

    if (*out)
        free(out);
    out = ft_strnew(0);
    while (1)
    {
        if (*list->buff)
        {
            if (!(temp = ft_strchr(list->buff, '\n')))
            {
                out = ft_strjoin(out, list->buff);
            }
            else {
                list->temp = ft_strdup(list->buff);
                *temp = '\0';
                temp++;
                if (*temp) {
                    if (!(list->buff = (char *)malloc(sizeof(list->buff) * BUFF_SIZE + 1)))
                        return (-1);
                    ft_strncpy(list->buff, temp, BUFF_SIZE);
                }
            }
        }
        read(list->fd, list->buff, BUFF_SIZE)
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
	fd = open("/Users/ahonchar/test/file1", O_RDONLY);
	if (fd < 3)
		return (printf("invalid file, open = %d\n", fd));
	while (get_next_line(fd, &out) > 0)
 		printf("%s\n", out);
	close(fd);
	free(out);
	system("leaks -quiet gnl");
	return (0);
}

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

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "/Users/ahonchar/done/libft/libft.h"

#define BUFF_SIZE 10

t_list	*search_in_list(t_list *list, int fd)
{
	while (list)
	{
		if (list->content_size == (size_t)fd)
			return (list);
		list = list->next;
	}
	return (NULL);	
}

int		read_line(t_list *list, char **line)
{
	char	*buf;
	char	*out;
	int		ret;

	out = NULL;
	if (list->content)
		read_from_list(list, line);
	else
	{
		buf = strnew(BUFF_SIZE);
		ret = read(list->content_size, buf, BUFF_SIZE);
		while (!ft_strchr(buf, '\n'))
		{
			if (!out)
				*out = ft_strnew(BUFF_SIZE);
			else
				

			ret = read(list->content_size, buf, BUFF_SIZE);
		}
	}
}

int		get_next_line(const int fd, char **line)
{
	static t_list *files;
	t_list *current;

	if (!line || fd < 0 || (read(fd, NULL, 0)) < 0)
		return (-1);
	if (!files)
	{
		files = lstnew(NULL, 0);
		files->content_size = fd;
	}
	else
	{
		current = search_in_list(files, fd);
		if (!current)
		{
			current = lstnew(NULL, 0);
			current->content_size = fd;
			lstadd(&files, current);
		}
		else
			return (read_line(current, line));
	}
	return (read_line(files, line));
}

//int		main(int ac, char **av)
//{
//	int		i;
//	char	*out;
//	char	*begin;
//	int		fd;
//
//	if (ac != 2)
//		return (printf("usage:\t%s filename\n", av[0]));
//	i = 0;
//	out = (char *)malloc(1000);
//	out[999] = '\0';
//	begin = out;
//	fd = open(av[1], O_RDONLY);
//	while (get_next_line(fd, &out) > 0)
//		printf("%s\n", out);
//	//get_next_line(fd, &out);
//	//printf("%s\n", begin);
//	return (0);
//}

int		main(void)
{
	int		i;
	char	*out;
	char	*begin;
	int		fd;

	i = 0;
	out = (char *)malloc(1000);
	out[999] = '\0';
	begin = out;
	fd = open("/Users/ahonchar/test/file1", O_RDONLY);
	if (fd < 3)
		return (printf("invalid file, open = %d\n", fd));
	while (get_next_line(fd, &out) > 0)
		printf("%s\n", out);
	//get_next_line(fd, &out);
	//printf("%s\n", begin);
	return (0);
}

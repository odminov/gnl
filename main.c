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

int		copy_from_list(char **line, t_list *list)
{
	char	*str;
	char	**begin_line;

	begin_line = line;
	while (list->content)
	{
		(**line)++ = list->content++;
		if (*(list->content) == '\n')
		{
			line = begin_line;
			list->content++;
			str = (char *)malloc(sizeof(str) * ft_strlen(list->content) + 1);
			ft_memcpy(str, list->content, ft_strlen(list_content) + 1);
			free(list->content);
			list->content = str;
			return (1);
		}
	}
	free(list->content);
	list->content = NULL;
	return (0);
}



int		read_line(t_list *list, char **line)
{
	int		i;
	int		ret;
	char	**begin;
	char	*buf;

	buf = (char *)malloc(sizeof(buf) * BUFF_SIZE + 1);
	buf[BUFF_SIZE] = '\0';
	begin = line;
	if (list->content)
		if(copy_from_list(line, list->content))
			return ();
	while ((ret = read(list->content_size, buff, BUFF_SIZE)) > 0)
	{
		while (list->content[i])
		{
			(**line)++ = list->content[i++];
			if (list->content[i] == '\n')
			{	

				break;
			}
		}
		if (list->content[i] == '\n' || (ret < BUFF_SIZE))
			break;
	}
	i++;
	line = begin;
}

int		get_next_line(const int fd, char **line)
{
	static t_list *files;
	t_list	*current;

	if (!files)
	{
		files = create_list(fd);
		return (read_line(files, line));
	}
	else
	{
		current = search_in_list(files, fd);
		if (!current)
			current = add_to_list(files, fd);
	}
	return (read_line(current, line));
}

int		main(int ac, char **av)
{
	int		i;
	char	*out;
	char	*begin;
	int		fd;

	if (ac != 2)
		return (printf("usage:\t%s filename\n", av[0]));
	i = 0;
	out = (char *)malloc(1000);
	out[999] = '\0';
	begin = out;
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &out) > 0)
		*out++ = '\n'; 
	//get_next_line(fd, &out);
	printf("%s\n", begin);
	return (0);
}

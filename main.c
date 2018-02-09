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

int		read_from_list(t_list *list, char **line)
{
	char	*for_free;
	char	*buf2;
	int		i;

	i = 0;
	for_free = list->content;
	while (*((char *)list->content))
	{
		if ((char)list->content++ == '\n')
			break;
		i++;
	}
	if (*((char *)list->content) == '\n')
	{
		list->content++;
		*line = ft_strnew(i);
		ft_memcpy(*line, for_free, i);
		buf2 = ft_strnew(ft_strlen(list->content));
		ft_memcpy(buf2, list->content, ft_strlen(list->content));
		free(for_free);
		list->content = buf2;
		return (1);
	}
	else
	{
		*line = ft_strnew(i);
		ft_memcpy(*line, for_free, i);
		free(for_free);
		list->content = NULL;
		return (0);
	}
}

void	write_end(t_list *list, char *buf, int i)
{
	int j;

	j = i;
	while (buf[j])
		j++;
	list->content = ft_strnew(j);
	j = 0;
	while (buf[++i])
		((char *)(list->content))[j++] = buf[i];
}

int		read_line(t_list *list, char **line)
{
	char	*read_buf;
	char	*out;
	char	*buf;
	char	*for_free;
	int		ret;
	int		i;

	out = NULL;
	if ((char *)list->content)
		if (read_from_list(list, line))
			return (1);
	read_buf = ft_strnew(BUFF_SIZE);
	ret = read(list->content_size, read_buf, BUFF_SIZE);
	while (!ft_strchr(read_buf, '\n'))
	{
		if (!(**line))
		{
			*line = ft_strnew(BUFF_SIZE);
			ft_memcpy(*line, read_buf, BUFF_SIZE);
		}
		else
		{
			for_free = *line;
			*line = ft_strjoin(*line, read_buf);
			free(for_free);
		}
		ret = read(list->content_size, read_buf, BUFF_SIZE);
	}
	i = 0;
	while(read_buf[i] != '\n')
		i++;
	if (read_buf[i + 1])
		write_end(list, read_buf, i);
	if (!(*line))
	{
		*line = ft_strnew(i);
		ft_memcpy(*line, read_buf, i);
	}
	else
	{
		buf = ft_strnew(i);
		ft_memcpy(buf, read_buf, i);
		for_free = *line;
		*line = ft_strjoin(*line, buf);
		free(for_free);
		free(buf);
	}
	free(read_buf);	
	if(ret < BUFF_SIZE)
		return (0);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_list *files;
	t_list *current;

	if (!line || fd < 0 || (read(fd, NULL, 0)) < 0)
		return (-1);
	if (!files)
	{
		files = ft_lstnew(NULL, 0);
		files->content_size = fd;
	}
	else
	{
		current = search_in_list(files, fd);
		if (!current)
		{
			current = ft_lstnew(NULL, 0);
			current->content_size = fd;
			ft_lstadd(&files, current);
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
	int		fd;

	i = 0;
	fd = open("/Users/ahonchar/test/file1", O_RDONLY);
	if (fd < 3)
		return (printf("invalid file, open = %d\n", fd));
	while (get_next_line(fd, &out) >= 0)
		printf("%s\n", out);
	close(fd);
	//get_next_line(fd, &out);
	//printf("%s\n", begin);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2018/01/25 17:03:10 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "/Users/ahonchar/done/libft/libft.h"

#define BUFF_SIZE 10



int		get_next_line(const int fd, char **line)
{
	t_list *file;

	file = search_in_list(list, fd)
	if (!file)
		file = create_list(fd);
	

}

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
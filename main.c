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

#define BUFF_SIZE 10



int		get_next_line(const int fd, char **line)
{
	char	*buff;
	int		size;
	int		i;
	int		new_line;
	//bool	line;

	buff = (char *)malloc(BUFF_SIZE + 1);
	size = read(fd, buff, BUFF_SIZE);
	buff[size] = '\0';
	if (!size)
		return (0);
	if (size == -1)
		return (-1);
	i = 0;
	new_line = 0;
	while (1)
	{
		while (buff[i] != '\n' && buff[i])
		{
			**line = buff[i];
			i++;
			(*line)++;
		}
		if (buff[i] == '\n')
		{
			free(buff);
			return (1);
		}
		i = 0;
		size = read(fd, buff, BUFF_SIZE);
		if (!size)
			return (0);
	}
	return (1);
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
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

int		get_next_line(const int fd, char **line)
{
	static char	*buff;
	char		*buff2;
	char		*temp;
	int			i;
	int			read_bytes;
	static int	read_compleate;

	if (read_compleate)
		return (0);
	if (!buff)
        if (!(buff = ft_strnew(BUFF_SIZE)))
            return (-1);
    if (**line != '\0')
    {
        if (**line)
            free(*line);
    }
    *line = ft_strnew(0);
    read_bytes = 0;
	while (1)
	{
		i = -1;
        if (buff[i + 1])
        {
            while (buff[++i])
                if (buff[i] == '\n')
                    break;
			buff2 = ft_strnew(i);
			ft_memcpy(buff2, buff, i);
			temp = *line;
			*line = ft_strjoin(*line, buff2);
			free(buff2);
			free(temp);
		}
		if (buff[i] == '\n')
		{
			temp = buff;
			while (*buff)
				if (*buff++ == '\n')
					break;
			buff2 = ft_strnew(ft_strlen(buff));
			ft_memcpy(buff2, buff, ft_strlen(buff));
			free(temp);
			buff = buff2;
			return (1);
		}
		if ((read_bytes > 0) && (read_bytes < BUFF_SIZE))
			read_compleate = 1;
		if (!(read_bytes = read(fd, buff, BUFF_SIZE)))
			return (-1);
	}
	return (-1);
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
	while (get_next_line(fd, &out) > 0)
 		printf("%s\n", out);
	close(fd);
	free(out);
	//get_next_line(fd, &out);
	//printf("%s\n", begin);
	system("leaks -quiet gnl");
	return (0);
}

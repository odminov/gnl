/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 15:31:14 by ahonchar          #+#    #+#             */
/*   Updated: 2018/02/13 16:09:09 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 15

int					get_next_line(int fd, char **line);

typedef struct		s_gnl
{
	char			*buff;
	int				fd;
	int				read_compleate;
	struct s_gnl	*next;
}					t_gnl;

#endif

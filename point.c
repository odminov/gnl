/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahonchar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 17:14:29 by ahonchar          #+#    #+#             */
/*   Updated: 2018/02/07 18:15:55 by ahonchar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void out(char **str)
{
	while (**str)
	{
		printf("%c", **str);
		(*str)++;
	}
}

int main(void)
{
	char *str;
	int i;
	int j;
	
	i = 0;
	j = 'A';
	str = (char *)malloc(sizeof(str) * 10 + 1);
	str[10] = '\0';
	while (j < 75)
	{
		str[i++] = j;
		j++;
	}
	printf("%p - adress before\n", str);
	out(&str);
	printf("\n");
	printf("%p - adress after\n", str);
	printf("%p - adress after\n", NULL);
	//free(str);
	return (0);
}

#include <fcntl.h>
#include <stdio.h>

#include "get_next_line.h"

int     main(void)
{
    int     i;
    char    *out;
    int     fd;
    int     fd2;
    int     fd3;

    i = 0;
    fd = open("/users/ahonchar/test1/file1", O_RDONLY);
    fd2 = open("/users/ahonchar/test1/file2", O_RDONLY);
    fd3 = open("/users/ahonchar/test1/file3", O_RDONLY);
    if (fd < 3)
        return (printf("invalid file, open = %d\n", fd));
    while ((i = get_next_line(fd2, &out)) > 0)
    {
        printf("%s\n", out);
        printf("%d\n", i);
        free(out);
    }
    printf("%d\n", i);
	while ((i = get_next_line(fd, &out)) > 0)
    {
        printf("%s\n", out);
        printf("%d\n", i);
        free(out);
    }
    printf("%d\n", i);
	while ((i = get_next_line(fd3, &out)) > 0)
    {
        printf("%s\n", out);
        printf("%d\n", i);
        free(out);
    }
    printf("%d\n", i);
	if ((i = get_next_line(fd, &out)) > 0)
    {
        printf("%s\n", out);
        printf("%d\n", i);
        free(out);
    }
    printf("%d\n", i);
	// if (get_next_line(fd, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd2, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd3, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd2, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd3, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd2, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd3, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd2, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
	// if (get_next_line(fd3, &out) == 1)
	// {
	// 	printf("%s\n", out);
	// 	free(out);
	// }
    close(fd3);
    close(fd2);
    close(fd);
    system("leaks -quiet gnl");
    return (0);
}

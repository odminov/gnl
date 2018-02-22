#include <fcntl.h>
#include <stdio.h>

#include "get_next_line.h"

int     main(void)
{
    int     i;
    char    *out;
    int     fd;

    i = 0;
    fd = open("/users/ahonchar/test/file1", O_RDONLY);
    if (fd < 3)
        return (printf("invalid file, open = %d\n", fd));
    while (get_next_line(fd, &out) > 0)
    {
        printf("%s\n", out);
    }
    close(fd);
    free(out);
    system("leaks -quiet gnl");
    return (0);
}

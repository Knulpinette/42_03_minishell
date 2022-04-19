#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Conclusion from this small experiment:
 * - closing the same fd twice returns -1 the second time
 *   but that's ok, I just won't catch the error
 */

int main(void)
{
    int fd;
    int res;

    fd = open("test.txt", O_RDWR | O_CREAT, 00755);
    write(fd, "hello\n", 6);
    res = close(fd);
    printf("%d\n", res);
    res = close(fd);
    printf("%d\n", res);
    return (0);
}
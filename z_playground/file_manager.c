#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Conclusion from first small experiment:
 * - closing the same fd twice returns -1 the second time
 *   but that's ok, I just won't catch the error
 *
 * Conclusion from second experiment:
 * - closing and then unlinking, or unlinking and then closing:
 *   both work without problems
 * - definitely need to close after unlinking
 */

int main(void)
{
	int fd;
	int fd2;
	int res;

	fd = open("test.txt", O_RDWR | O_CREAT, 00755);
	write(fd, "hello\n", 6);
	res = unlink("test.txt");
	printf("%d\n", res);
	res = close(fd);
	printf("%d\n", res);
	fd2 = open("test2.txt", O_RDWR | O_CREAT, 00755);
	printf("second fd: %d\n", fd2);
	return (0);
}
#include <stdio.h>
#include <unistd.h>

int		main(int argc, char **argv)
{
	printf("getcwd %s\n", getcwd(NULL, 0));
	return (0);
}

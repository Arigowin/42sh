#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		main (int argc, char **argv)
{
	char	*path;
	
	path = NULL;
	(void)argc;
	printf("getcwd     = %s\n", getcwd(path, 40));
	printf("getenv pwd = %s\n", getenv("PWD"));
	printf("argv[1] = %s\n", argv[1]);
	chdir(argv[1]);
	printf("apres chdir getcwd     = %s\n", getcwd(path, 40));
	printf("apres chdir getenv pwd = %s\n", getenv("PWD"));
	return (0);
}

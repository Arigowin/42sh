#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int		main (void)
{
	char	*path;
	
	path = NULL;
	printf("getcwd     = %s\n", getcwd(path, 40));
	printf("getenv pwd = %s\n", getenv("PWD"));
	return (0);
}

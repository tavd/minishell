#include <stdio.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	printf("argc:%i\nargv:", argc);
	while (i < argc)
		printf("%s", argv[++i]);
}

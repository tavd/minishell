#include <stdio.h>
#include <stdint.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	printf("argc:%i\nargv:", argc);
	while (i < argc)
		printf("%s", argv[++i]);
	printf("\n%zu", SIZE_MAX);
}

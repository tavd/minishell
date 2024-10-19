#include <stdio.h>
#include <stdint.h>

#include <unistd.h>

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	printf("argc:%i\nargv:", argc);
	while (i < argc)
		printf("%s", argv[++i]);
	printf("\n%zu", SIZE_MAX);

	long arg_max = sysconf(_SC_ARG_MAX);
	printf("\nargmax = %li", arg_max);

}

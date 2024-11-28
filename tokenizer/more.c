
#define NDEBUG
#include <assert.h>

#include <string.h>
#include <stdio.h>

int main()
{
	int	x = 13;
	char	*a = "wi";
	char	b[5] = "witf";
	int	c[3] = {2, 34, 12};


	printf("%i\n", strncmp(b, a, 4));
	printf("%i", sizeof(c));
	
	assert(("wtf", x < 10));
}

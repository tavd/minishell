
#define NDEBUG
#include <assert.h>

#include <string.h>
#include <stdio.h>
#include <stdbool.h>


bool	deref(int *i)
{
	*i = 2;
}

int main()
{
	int	x = 13;
	char	*a = "wi";
	char	b[5] = "witf";
	int	c[3] = {2, 34, 12};


	printf("%i\n", strncmp(b, a, 4));
	printf("%i", sizeof(c));
	
	assert(("wtf", x < 10));
	int	hi;
	deref((int *)0);
}

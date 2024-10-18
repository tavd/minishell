/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:54:52 by mzwart            #+#    #+#             */
/*   Updated: 2024/02/27 16:14:49 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static void	vec_initialize(t_vector *vec, size_t size)
{
	vec->size = size;
	vec->used = 0;
	vec->content = malloc(size);
	if (!vec->content)
		return ;
	ft_memset(vec->content, 0, size);
}

static void	vec_insert(t_vector *vec, const char *string, size_t len)
{
	char	*old_array;
	char	*new_array;
	size_t	growth_factor;

	if (vec->content != NULL && vec->used + len >= vec->size)
	{
		growth_factor = 2;
		while (vec->used + len >= vec->size * growth_factor)
			++growth_factor;
		vec->size *= growth_factor;
		old_array = vec->content;
		vec->content = NULL;
		new_array = malloc(vec->size);
		if (!new_array)
			return (free(old_array));
		ft_memcpy(new_array, old_array, vec->used);
		ft_memset(new_array + vec->used, 0, vec->size - vec->used);
		free(old_array);
		vec->content = new_array;
	}
	while (vec->content != NULL && len--)
	{
		vec->content[vec->used++] = *(char *)string;
		++string;
	}
}

// 'x' + 1 creates 121 spaces in the array to index the function pointers
// using the ascii value's of the conversion specifiers up to 120 so 'x'
void	insert_specifier_arg(t_vector *buf, char specifier, va_list va_arg_ptr)
{
	const t_va_function	methods['x' + 1] = {
	['d'] = decimal, ['%'] = echo_percent, ['c'] = chars,
	['i'] = decimal, ['X'] = capital_hex, ['s'] = string,
	['u'] = unsigned_decimal, ['x'] = hex, ['p'] = void_ptr
	};
	t_va_function		used_fn;
	char				*arg;
	size_t				arg_len;

	arg = NULL;
	used_fn = methods[(uint8_t)specifier];
	if (used_fn != NULL && specifier <= 'x')
		arg = used_fn(va_arg_ptr);
	if (!arg || specifier > 'x')
	{
		free(buf->content);
		buf->content = NULL;
		return ;
	}
	arg_len = ft_strlen(arg);
	if (used_fn == chars && arg[0] == '\0')
		arg_len = 1;
	vec_insert(buf, arg, arg_len);
	if (specifier != 's' && specifier != '%')
		free(arg);
}

int	ft_printf(const char *format, ...)
{
	va_list		va_arg_ptr;
	ssize_t		write_ret;
	t_vector	buffer;

	if (!format)
		return (-1);
	vec_initialize(&buffer, VEC_SIZE);
	va_start(va_arg_ptr, format);
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			insert_specifier_arg(&buffer, *format, va_arg_ptr);
		}
		else
			vec_insert(&buffer, format, 1);
		if (buffer.content == NULL)
			return (-1);
		++format;
	}
	va_end(va_arg_ptr);
	write_ret = write(1, buffer.content, buffer.used);
	free(buffer.content);
	return (write_ret);
}

// int main()
// {
// 	int	ret;
	// int	realrt;
	//ret = ft_printf("hello %u", p); printf("\n");
	// ret = ft_printf("%c", 'a');
	// printf("\n");
// realrt = printf("%c%c %p %p",0, 0, (void *)ULONG_MAX, (void *)-ULONG_MAX);
	// printf("\nmy:%i printf:%i\n", ret, realrt);
	// // ret = ft_printf(" %p %p",(void *)LONG_MIN, (void *)LONG_MAX);
	// printf("\n");
	// realrt = printf(" %p %p",(void *)LONG_MIN, (void *)LONG_MAX);
	// printf("\nmy:%i printf:%i", ret, realrt);

	//ft_printf("hello world!%s kldfj", "hi");
	//printf("hello%sblal", NULL);
	//printf("\n%i a%",3); //wtf is this behaviour
	//printf("\n%i aalksdjasdk",3); //wtf is this behaviour
// }

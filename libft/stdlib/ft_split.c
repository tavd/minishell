/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:21:58 by mzwart            #+#    #+#             */
/*   Updated: 2023/11/20 18:05:57 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"

static char	*ft_strndup(const char *str, size_t str_len)
{
	char	*cpy;

	cpy = (char *)malloc(str_len + 1);
	if (cpy == NULL)
		return (NULL);
	ft_memcpy(cpy, str, str_len);
	cpy[str_len] = '\0';
	return (cpy);
}

static size_t	word_counter(char *str, char delimiter)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (*str)
	{
		while (*str == delimiter)
			str++;
		if (*str != '\0')
			count++;
		while (*str && *str != delimiter)
			str++;
	}
	return (count);
}

static void	*free_words(char **array, size_t words_in_array)
{
	while (words_in_array--)
		free(array[words_in_array]);
	free(array);
	return (NULL);
}

char	**ft_split(char const *str, char delimiter)
{
	const size_t	word_count = word_counter((char *)str, delimiter);
	char			**array;
	size_t			word_index;
	char			*start_word;

	array = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	word_index = 0;
	while (word_index < word_count)
	{
		while (*str == (unsigned char)delimiter)
			str++;
		start_word = (char *)str;
		while (*str != '\0' && *str != (unsigned char)delimiter)
			str++;
		array[word_index] = ft_strndup(start_word, str - start_word);
		if (!array[word_index])
			return (free_words(array, word_index));
		word_index++;
	}
	array[word_index] = NULL;
	return (array);
}

/*
int main ()
{
	char *s = NULL;
	char d = 0;
	char **array;

	size_t c= word_counter(s, d);
	printf("%zu\n", c);
	array = ft_split(s, d);
	if (!array)
		return 0;

	if (!array[0])
		printf("%s", "ok\n");
	size_t i = 0;
	while (i <= c)
	{
		printf(":%s:\n", array[i]);
		i++;
	}
	free_words(array, c);

	return 0;
}
*/

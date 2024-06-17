/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: irsander <irsander@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 10:03:17 by irissanders   #+#    #+#                 */
/*   Updated: 2023/10/15 13:40:22 by irissanders   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if ((s[i] == c && s[i +1] != c) || s[i +1] == '\0')
			counter++;
		i++;
	}
	return (counter);
}

int	word_length(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*ft_free(char **ptr_to_arrays)
{
	int	i;

	i = 0;
	while (ptr_to_arrays[i])
		free(ptr_to_arrays[i++]);
	free(ptr_to_arrays);
	return (NULL);
}

static int	init(char const *s, char c, char ***ptr_to_arrays)
{
	int	amount_of_words;

	if (!s)
		return (1);
	amount_of_words = word_count(s, c);
	*ptr_to_arrays = malloc((amount_of_words + 1) * sizeof(char *));
	if (!*ptr_to_arrays)
		return (1);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		word_len;
	char	**ptr_to_arrays;
	int		i;
	int		j;

	if (init(s, c, &ptr_to_arrays) == 1)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		word_len = word_length(&s[i], c);
		ptr_to_arrays[j] = malloc((word_len +1) * sizeof(char));
		if (!ptr_to_arrays[j])
			return (ft_free(ptr_to_arrays));
		ft_strlcpy(ptr_to_arrays[j++], &s[i], word_len +1);
		i = word_len + i;
	}
	ptr_to_arrays[j] = NULL;
	return (ptr_to_arrays);
}

// int	main(void)
// {
// 	char *s = "hallo hoe gaat het";
// 	char **result;
// 	int i;

// 	result = ft_split(s, ' ');
// 	i = 0;
// 	while(result[i])
// 	{
// 		printf("%s\n", result[i]);
// 		i++;
// 	}
// }

// char **ft_split(char const *s, char c)
// {
// 	int	amount_of_words;
// 	int word_len;
// 	char **ptr_to_arrays;
// 	int	i;
// 	int j;

// 	if (!s)
// 		return (NULL);
// 	// 1. count words
//     amount_of_words = word_count(s, c);
// 	ptr_to_arrays = malloc((amount_of_words +1) * sizeof(char *));
// 	if (!ptr_to_arrays)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		// 2. increment the index until s[index] == c
// 		while (s[i] == c)
// 			i++;
// 		if (!s[i])
// 			break ;
// 		// 2. find word length until c
// 		word_len = word_length(&s[i], c);
// 		ptr_to_arrays[j] = malloc((word_len +1) * sizeof(char));
// 		if (!ptr_to_arrays[j])
// 			ft_free(ptr_to_arrays);
// 		// 3. put the words into the allocated memory
// 		ft_strlcpy(ptr_to_arrays[j], &s[i], word_len+1);
// 		i = word_len + i;
// 		j++;
// 	}
// 	// 4. return array of strings
// 	ptr_to_arrays[j] = NULL;
// 	return (ptr_to_arrays);
// }
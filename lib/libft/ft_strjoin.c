/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: irsander <irsander@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 19:09:17 by irissanders   #+#    #+#                 */
/*   Updated: 2023/10/15 12:13:30 by irissanders   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	s3 = malloc((i + j + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, i + 1);
	ft_strlcpy(s3 + i, s2, j + 1);
	return (s3);
}

// int	main(void)
// {
// 	char *s1 = "hello";
// 	char *s2 = "goodbye";

// 	printf("%s", ft_strjoin(s1, s2));
// }
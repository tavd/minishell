/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: irsander <irsander@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 08:19:04 by irissanders   #+#    #+#                 */
/*   Updated: 2023/10/15 12:22:48 by irissanders   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > 0 && ft_strrchr(set, s1[end]))
		end--;
	return (ft_substr(s1, start, end - start +1));
}

// int main(void)
// {
//     char s1[] = "hellogoodbyehelloh";
//     char *set = "ho";

//     printf("%s\n", ft_strtrim(s1, set));
// }
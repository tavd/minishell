/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:22:19 by mzwart            #+#    #+#             */
/*   Updated: 2024/10/31 10:28:33 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include <stddef.h>

size_t		ft_strlen(const char *str);
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
void		*ft_memchr(const void *str, int c, size_t n);

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_memcmp(const void *block1, const void *block2, size_t n);

void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);

size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);

char		*ft_substr(const char *str, unsigned int start, size_t len);
char		*ft_strnstr(const char *big, const char *little, size_t len);

char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(const char *s1, const char *set);

void		ft_striteri(char *str, void (*f)(unsigned int i, char *c));
char		*ft_strmapi(const char *str, char (*f)(unsigned int i, char c));

char		*ft_strdup(const char *str);

void		*ft_memset(void *block, int c, size_t n);
void		ft_bzero(void *block, size_t n);

#endif

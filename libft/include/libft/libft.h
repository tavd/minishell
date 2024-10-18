/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzwart <mzwart@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:33:14 by mzwart            #+#    #+#             */
/*   Updated: 2024/08/08 16:10:07 by mzwart           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <string.h>
# include <stddef.h>
# include <stdint.h>
# include <errno.h>
# include <limits.h>

# include "bool.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new_node);
void		ft_lstadd_back(t_list **lst, t_list *new_node);
int			ft_lstsize(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*f)(void *content));
void		ft_lstiter(t_list *lst, void (*f)(void *content));
t_list		*ft_lstmap(t_list *l, void *(*f)(void *ct), void(*d)(void *ct));

// ctype
int			ft_tolower(int c);
int			ft_toupper(int c);

int			ft_memcmp(const void *block1, const void *block2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

// mem stuff
void		*ft_memchr(const void *str, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *block, int c, size_t n);
void		*ft_bzero(void *block, size_t n);

// string functions
char		*ft_strchr(const char *str, int c);
char		*ft_strrchr(const char *str, int c);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *str);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_substr(const char *str, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strtrim(const char *s1, const char *set);
char		**ft_split(const char *str, char delimiter);
char		*ft_strmapi(const char *str, char (*f)(unsigned int i, char c));
void		ft_striteri(char *str, void (*f)(unsigned int i, char *c));

// # ft_stdlib.h
int			ft_atoi(const char *str);
char		*ft_itoa(int number);
double		ft_atof(const char *str);
void		*ft_calloc(size_t num_elems, size_t elem_size);

// file desciptor functions
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *str, int fd);
void		ft_putendl_fd(char *str, int fd);
void		ft_putnbr_fd(int n, int fd);
#endif

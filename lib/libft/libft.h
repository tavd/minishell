/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:36:34 by irsander          #+#    #+#             */
/*   Updated: 2023/11/07 15:30:10 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>

// list are nodes in linked list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/// @brief checks if a character is an alphabet (a-z and A-Z) or not
/// @param c the character to be checked
/// @return 1 if character is an alphabeticle character, 0 if not
int		ft_isalpha(int c);

/// @brief Checks if character is a digit (0-9) or not.
/// @param c the character to be checked
/// @return 1 if character is digit, 0 if not
int		ft_isdigit(int c);

/// @brief checks if isalpha or isdigit is true.
/// @param c the character to be checked
/// @return 1 if true, 0 if false
int		ft_isalnum(int c);

/// @brief checks for an ascii character
/// @param c the character to be checked
/// @return 1 if character is an ascii character, 0 if it is not.
int		ft_isascii(int c);

/// @brief checks for any printable character, including space.
/// @param c the character to be checked
/// @return 1 if character is printable, 0 if not.
int		ft_isprint(int c);

/// @brief counts the length of the string s.
/// @param s the string whose length is to be counted.
/// @return the number of characters in the string before the terminating 
/// @return NUL character.
size_t	ft_strlen(const char *s);

/// @brief copies the character 'c' (converted to unsigned char) to the 
/// @brief first 'len' characters of the string pointed to, by the argument
/// @brief 'str'
/// @param str pointer to the block of memory to fill
/// @param c the value to be set
/// @param n the number of bytes to be set to the value
/// @return pointer to the memory area 's'.
void	*ft_memset(void *s, int c, size_t n);

/// @brief writes null bytes of size 'n' in the string 's'
/// @param s the string which has to be filled with null bytes.
/// @param n the number of bytes to be filled with null values.
void	ft_bzero(void *s, size_t n);

/// @brief copies 'n' characters from memory area src to memory area dest
/// @param dest the pointer to the destination array where the content
/// is to be copied, type -casted to a pointer of type void*.
/// @param src the pointer to the source of data to be copied,
/// type-casted to a pointer of type void*.
/// @param n the number of bytes to be copied from src
/// @return pointer to destination
void	*ft_memcpy(void *dest, const void *src, size_t n);

/// @brief copies 'n' characters from 'src' to 'dest', but for overlapping
/// memory blocks, memmove copies in reverse which is a safer approach
/// than memcpy
/// @param dest pointer to the destination array where the content is to
/// be copied, type-casted to a pointer of type *void.
/// @param src pointer to the source of data to be copied, type-casted to
/// a pointer of type *void.
/// @param n the number of bytes to be copied from src
/// @return pointer to destination
void	*ft_memmove(void *dest, const void *src, size_t n);

/// @brief copies characters from src to dest, but it doesnt exceed the
/// maximum size of dest, ensures that dest always ends with a null terminator 
/// and is a valid C string. If destsize is zero, the destination buffer is 
/// too small to copy anything so it returns the length of the source string
/// (ft_strlen(src)). This is a safety check to avoid trying to copy into
/// a buffer that cannot hold any data. destsize - 1, ensures that we don't
/// go beyond the maximum allowed size in the destination buffer.
/// @param dest destination buffer where the string will be copied to.
/// @param src source string from which data will be copied.
/// @param destsize is the maximum number of characters that can be copied
/// to dest without causing problems.
/// @return length of src 
size_t	ft_strlcpy(char *dest, const char *src, size_t destsize);

/// @brief concatenates the source string ‘src’ to the end of the destination
/// string ‘dest’ while ensuring that the total length of the concatenated
/// string does not exceed a specified maximum size ‘destsize’.
/// @param dest pointer to a character array (string) where the function
/// will concatenate the 'src' string.
/// @param src pointer to a constant character array (string) that contains
/// the characters to be added to the end of the dest string.
/// @param destsize maximum size or capacity of the dest string. It specifies
/// how many characters can be safely added to dest before it reaches its limit.
/// @return If the destination string is already at or exceeds this size, it
/// returns the sum of destsize and the length of the source string. Otherwise,
/// it performs the concatenation, and returns the total length of the combined
/// string.
size_t	ft_strlcat(char *dest, const char *src, size_t destsize);

/// @brief converts a lower-case letter to the corresponding upper-case letter
/// @param c represents the ASCII value of a character to be converted to
/// uppercase.
/// @return If the argument is a lower-case letter, it returns the corresponding
/// upper-case letter. Otherwise, the argument is returned unchanged.
int		ft_toupper(int c);

/// @brief converts a upper-case letter to the corresponding lower-case letter
/// @param c represents the ASCII value of a character to be converted to
/// lowercase.
/// @return If the argument is an upper-case letter, it returns the
///  corresponding lower-case letter. Otherwise, the argument is returned
/// unchanged.
int		ft_tolower(int c);

/// @brief  searches for a specific character c within the given string s.
/// @param s a pointer to a constant character string, which is the string
/// to search within.
/// @param c an integer representing a character, which is the character
/// to search for within the string s.
/// @return If it finds the character, it returns a pointer to the location
/// of that character in the string. If the character is not found or the
/// end of the string is reached, it returns NULL to indicate that c was not
/// present in the string.
char	*ft_strchr(const char *s, int c);

/// @brief searches for the last occurrence of a character c in the given
/// string s
/// @param s a pointer to a constant character string, which is the string
/// to search within.
/// @param c an integer representing a character, which is the character
/// to search for within the string s.
/// @return If it finds the character, it returns a pointer to the location
/// of that character in the string. If the character is not found or the
/// end of the string is reached, it returns NULL to indicate that c was 
/// not present in the string.
char	*ft_strrchr(const char *s, int c);

/// @brief compares strings s1 and s2, compares not more than 'n'
/// characters. characters that appear after a '\0' character are not compared
/// @param s1 the first string to be compared
/// @param s2 the second string to be compared
/// @param n the maximum number of characters to be compared
/// @return if Return value < 0 then it indicates str1 is less than str2 -
/// if Return value > 0 then it indicates str2 is less than str1 -
/// if Return value = 0 then it indicates str1 is equal to str2
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/// @brief locates the first occurrence of 'c' (converted to an unsigned char)
/// in string s.
/// @param s pointer to the block of memory that has to be searched
/// @param c value to be passed as an int, but the function performs a byte
/// per byte search using the unsigned char conversion of this value
/// @param n number of bytes to be searched
/// @return pointer to the matching byte or NULL if the character does not
/// occur in the given memory area.
void	*ft_memchr(const void *s, int c, size_t n);

/// @brief compares the first n bytes of memory area s1 and memory area s2
/// @param s1 pointer to a block of memory
/// @param s2 pointer to a block of memory
/// @param n the number of bytes to be compared
/// @return zero if the two strings are identical, otherwise it returns
/// the difference between the first two differing bytes.
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/// @brief 
/// @param haystack 
/// @param needle 
/// @param len 
/// @return 
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/// @brief converts the string argument 's' to an integer
/// @param s the string representation of an integral number
/// @return returns the converted integral number as an int value
int		ft_atoi(const char *s);

/// @brief allocates memory and returns a pointer to it. calloc sets
/// the allocated memory to zero
/// @param count number of elements to be allocated
/// @param size size of the elements
/// @return pointer to the allocated memory, or NULL if malloc fails
void	*ft_calloc(size_t count, size_t size);

/// @brief allocates sufficient memory and copies s1 
/// @param s1 the string to be copied
/// @return the copied string s2
char	*ft_strdup(const char *s1);

/// @brief allocates with malloc and returns a substring from the string 's'
/// @param s the string to make the substring out of
/// @param start the starting index of the substring in string s
/// @param len the maximum length of the substring
/// @return the substring
char	*ft_substr(char const *s, unsigned int start, size_t len);

/// @brief allocates with malloc and returns a new string, which is the result
/// of the concatenation of s1 and s2
/// @param s1 the first string
/// @param s2 the string to be put after the first string
/// @return the result of the concatenation of s1 and s2
char	*ft_strjoin(char const *s1, char const *s2);

/// @brief allocates with malloc and cuts the characters specified in set
/// from the start and end of string s1
/// @param s1 the string to be trimmed
/// @param set the reference set of characters to trim
/// @return a copy of s1, with the characters specified in 'set' removed from
/// the beginning and the end of the string
char	*ft_strtrim(char const *s1, char const *set);

/// @brief applies the function 'f' to each character of the string 's',
/// and passing its index as first argument to create a new string resulting
/// from successive applications of 'f'
/// @param s the string on which to iterate
/// @param f the function to apply to each character
/// @return the string created from the successive applications of 'f'
/// or NULL if the allocation fails
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/// @brief applies the function 'f' on each character of the string passed as 
/// an argument, passing its index as first argument
/// @param s the string on which to iterate
/// @param f the function to apply to each character
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

/// @brief outputs the character 'c' to the given file descriptor
/// @param c the character to output
/// @param fd the file descriptor on which to write
void	ft_putchar_fd(char c, int fd);

/// @brief outputs the string 's' to the given file descriptor followed by
/// a newline
/// @param s the string to output
/// @param fd the file descriptor on which to write
void	ft_putendl_fd(char *s, int fd);

/// @brief outputs the integer 'n' to the given file descriptor
/// @param n the integer to output
/// @param fd the file descriptor on which to write
void	ft_putnbr_fd(int n, int fd);

/// @brief outputs the string 's' to the given file descriptor
/// @param s the string to output
/// @param fd the file descriptor on which to write
void	ft_putstr_fd(char *s, int fd);

/// @brief Allocates with malloc and returns an array
///of strings obtained by splitting ’s’ using the
///character ’c’ as a delimiter.  The array must end
///with a NULL pointer.
/// @param s the string to be split
/// @param c the delimiter character
/// @return The array of new strings resulting from the split.
/// NULL if the allocation fails.
char	**ft_split(char const *s, char c);

/// @brief Allocates with malloc and returns a string
/// representing the integer received as an argument.
/// Negative numbers must be handled
/// @param n the integer to convert
/// @return The string representing the integer.
/// NULL if the allocation fails
char	*ft_itoa(int n);

/// @brief creates a new node in a linked list
/// @param content the content to create the node with
/// @return the new node
t_list	*ft_lstnew(void *content);

/// @brief 
/// @param lst The address of a pointer to the first link of
/// a list (head)
/// @param new The address of a pointer to the node to be
/// added to the list.
void	ft_lstadd_front(t_list **lst, t_list *new);

/// @brief counts the number of nodes in a list
/// @param lst the beginning of the list
/// @return the length of the list
int		ft_lstsize(t_list *lst);

/// @brief returns the last node of the list
/// @param lst the beginning of the list
/// @return last node of the list
t_list	*ft_lstlast(t_list *lst);

/// @brief adds the node 'new' at the end of the list
/// @param lst the address of a pointer to the first link 
/// of a list
/// @param new the address of a pointer to the node to be
/// added to the list
void	ft_lstadd_back(t_list **lst, t_list *new);

/// @brief takes as a parameter a node and frees the memory of
/// the node's content using the function 'del' given as a 
/// parameter and free the node. The memory of 'next' must 
/// not be freed.
/// @param lst the node to free
/// @param del the address of the function used to delete
/// the content
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/// @brief deletes and frees the given node and every successor
/// of that node, using the function 'del' and free.
/// finally, the pointer to the list must be set to NULL.
/// @param lst the address of a pointer to a node
/// @param del the address of the function used to delete
/// the content of the node
void	ft_lstclear(t_list **lst, void (*del)(void*));

/// @brief iterates the list 'lst' and applies the function
/// 'f' on the content of each node
/// @param lst the address of a pointer to a node
/// @param f the address of the function used to iterate on 
/// the list
void	ft_lstiter(t_list *lst, void (*f)(void *));

/// @brief iterates the list 'lst' and applies the function
/// 'f' on the content of each node. Creates a new list
/// resulting of the successive applications of the function
/// 'f'. The 'del' function is used to delete the content of 
/// a node if needed
/// @param lst the address of a pointer to a node
/// @param f the address of the function used to iterate on
/// the list
/// @param del the address of the function used to delete
/// the content of a node if needed
/// @return the new list / NULL if the allocation fails
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
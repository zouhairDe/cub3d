/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouddach <zouddach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:52:25 by zouddach          #+#    #+#             */
/*   Updated: 2023/11/08 14:02:51 by zouddach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* ====== INCLUDES ====== */

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

/* ====== END INCLUDES ====== */

/* ====== INTS ====== */

int		ft_isalpha(int arg);
int		ft_isalnum(int arg);
int		ft_isdigit(int arg);
int		ft_isascii(int arg);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isprint(int arg);
int		ft_atoi(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_memcmp( const char *ptr1, const void *ptr2, size_t num );

/* ====== END INTS ====== */

/* ====== SIZE_T ====== */

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);

/* ====== END SIZE_T ====== */

/* ====== VOID ====== */

void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
void	*ft_calloc(size_t num, size_t size);
void	ft_putchar_fd(char c, int fd);
void	*ft_memchr(const void *str, int c, size_t n);
void	ft_bzero(void *str, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* ====== END VOID ====== */

/* ====== CHARS ====== */

char	*ft_strchr(const char *str, int arg);
char	**ft_split(char *str, char c);
char	*ft_strdup(const char *str);
char	*ft_itoa(int n);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_memcpy(void *dest, const void *src, size_t length);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* ====== END CHARS ====== */

/*------------ BONUS -------------*/

/*======== typdef =========*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/*======== END typdef =========*/

/*======== t_list =========*/

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);

/*======== END t_list =========*/

/*======== INTS =========*/

int		ft_lstsize(t_list *lst);

/*======== END INTS =========*/

/*======== VOID =========*/

void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));

/*======== END VOID =========*/

/*---------- END BONUS ----------*/

#endif
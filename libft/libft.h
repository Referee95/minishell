/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 11:00:41 by nel-mous          #+#    #+#             */
/*   Updated: 2023/07/08 22:38:17 by nel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*data;
	struct s_list	*next;

}	t_list;
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *dst, char *src);
int		ft_strcmp(const char *S1, const char *S2);
int		ft_strncmp(const char *S1, const char *S2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *a);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
t_list	*ft_lstnew(char	*content);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
char	*ft_strncpy(char *dst, char *src, unsigned int n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strcpy(char *dst, char *src);
int		ft_isalnum(int c);
int		ft_isalpha(int ch);
int		ft_isdigit(int c);
void	ft_lstclear(t_list **lst, void (*del)(void*));
char	*ft_strjoinfree(char *s1, char *s2, int flag);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(int n);

#endif
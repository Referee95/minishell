# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 11:06:17 by nel-mous          #+#    #+#              #
#    Updated: 2023/07/08 22:26:24 by nel-mous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=  	ft_strlen.c ft_strcmp.c ft_strncmp.c ft_strchr.c ft_strdup.c ft_substr.c \
			ft_lstnew.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstsize.c ft_strcat.c \
			ft_strncpy.c ft_strcpy.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_strjoin.c ft_split.c \
			ft_strtrim.c ft_lstclear.c ft_atoi.c ft_putstr_fd.c ft_itoa.c

OBJS	=$(SRCS:.c=.o)

NAME	=libft.a 

CC	=gcc

CFLAGS	=-Wall -Werror -Wextra 

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
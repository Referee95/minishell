# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nel-mous <nel-mous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 09:08:36 by nel-mous          #+#    #+#              #
#    Updated: 2023/07/13 15:37:13 by nel-mous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS 	=	main.c lexer.c lexer_utils.c  analyzer.c analyzer_utils.c parser.c \
 			parser_utils.c heredoc.c environment.c expander.c expander_utils.c free_functions.c \
			ft_free.c heredoc_expansion.c builtins.c builtins_utils.c builtins_utils2.c \
 			ft_echo.c export.c get_path.c expand_redirections.c pipe.c pipe2.c setup_redirection.c \
			executer.c executer_utils.c signals.c
			

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

NAME = minishell

CC = cc 

CFlAGS = -Wall -Wextra -Werror -I/Users/nel-mous/Downloads/Homebrew-brew-e986264/opt/readline/include/

%.o: %.c minishell.h
	$(CC) $(CFlAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFlAGS) -lreadline -L/Users/nel-mous/Downloads/Homebrew-brew-e986264/opt/readline/lib  $(OBJS) $(LIBFT) -o $@

$(LIBFT):
	make -sC libft all

clean:
	make -sC libft fclean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
